#!/usr/bin/env python3
import hashlib
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PREPROCESSOR = ROOT / 'content/tex/preprocessor.py'
HASH_SCRIPT = ROOT / 'content/contest/hash.sh'


class HashTest(unittest.TestCase):
    def test_cpp_digits_and_conditional_macros_are_quiet(self):
        source = '#ifdef DEBUG\n#define bug(x) x\n#else\n#define bug(x) void(0)\n#endif\nauto n = 1\'000;\n'
        result = subprocess.run(['sh', str(HASH_SCRIPT)], input=source,
                                text=True, capture_output=True, check=True)
        self.assertEqual(result.stderr, '')
        self.assertEqual(result.stdout.strip(), hashlib.md5(
            b"#ifdefDEBUG#definebug(x)x#else#definebug(x)void(0)#endifauton=1'000;"
        ).hexdigest()[:6])

    def test_hash_reads_stdin_without_main_cpp(self):
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run(
                ['sh', str(HASH_SCRIPT)], input='int x;\n', text=True,
                capture_output=True, cwd=directory)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.strip(), hashlib.md5(b'intx;').hexdigest()[:6])
        self.assertEqual(result.stderr, '')

    def test_missing_file_does_not_produce_checksum(self):
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run(
                ['sh', str(HASH_SCRIPT), 'missing.cpp'], text=True,
                capture_output=True, cwd=directory)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, '')

    def test_explicit_file_matches_stdin_despite_unrelated_main(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'main.cpp').write_text('int wrong;\n')
            (root / 'chosen file.cpp').write_text('int x;\n')
            for arguments in [[], ['chosen file.cpp']]:
                with self.subTest(arguments=arguments):
                    result = subprocess.run(
                        ['sh', str(HASH_SCRIPT), *arguments], input='int x;\n',
                        text=True, capture_output=True, cwd=root, check=True)
                    self.assertEqual(result.stdout.strip(), '3ecdec')
                    self.assertEqual(result.stderr, '')

    def test_whitespace_and_comments_do_not_change_checksum(self):
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run(
                ['sh', str(HASH_SCRIPT)], input='// note\n int /* note */ x ;\n',
                text=True, capture_output=True, cwd=directory, check=True)
        self.assertEqual(result.stdout.strip(), '3ecdec')


class PreprocessorTest(unittest.TestCase):
    def render(self, metadata, language='py', code='int answer(){ return 42; }'):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'build').mkdir()
            (root / 'content').symlink_to(ROOT / 'content', target_is_directory=True)
            source = '/**\n' + metadata + '\n */\n' + code + '\n'
            result = subprocess.run(
                [sys.executable, str(PREPROCESSOR), '-l', language, '-c', 'Example.h'],
                input=source, text=True, capture_output=True, cwd=root, check=True)
            return result.stdout

    def test_checksum_failure_is_reported_to_latex(self):
        output = self.render(' * Description: Example.', 'cpp', '/* unfinished')
        self.assertIn('\\kactlerror', output)
        self.assertIn('Checksum generation failed.', output)
        self.assertNotIn('\\rightcaption', output)

    def test_description_without_author_keeps_code(self):
        output = self.render(' * Description: Example template.')
        self.assertNotIn('\\kactlerror', output)
        self.assertIn('int answer(){ return 42; }', output)

    def test_extra_fields_are_visible(self):
        output = self.render(
            ' * Author: Example\n * Description: Example template.\n'
            ' * Requires: Some_header.h\n'
            ' * Duality: Primal and dual optima agree.\n'
            ' * Oracle: build(I) prepares I; add(e) checks independence.')
        self.assertNotIn('\\kactlerror', output)
        self.assertIn('\\textbf{Requires:}', output)
        self.assertIn('Some\\_header.h', output)
        self.assertIn('\\textbf{Duality:}', output)
        self.assertIn('Primal and dual optima agree.', output)
        self.assertIn('\\textbf{Oracle:}', output)
        self.assertIn('add(e) checks independence.', output)

    def test_unknown_fields_still_fail(self):
        output = self.render(' * Description: Example.\n * Descripton: Typo.')
        self.assertIn('Unknown command: Descripton.', output)

    def test_description_is_still_required(self):
        output = self.render(' * Author: Example')
        self.assertIn('Missing command: Description.', output)

    @unittest.skipUnless(shutil.which('pdflatex'), 'pdflatex is required')
    def test_order_statistic_tree_builds_as_latex(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'build').mkdir()
            (root / 'content').symlink_to(ROOT / 'content', target_is_directory=True)
            (root / 'example.tex').write_text(
                '\\documentclass{extreport}\n\\usepackage{kactlpkg}\n'
                '\\university{Test}{Test}{}\n'
                '\\kactlcontentdir{content/data-structures}\n'
                '\\begin{document}\n\\begin{multicols*}{3}\n'
                '\\kactlimport{OrderStatisticTree.h}\n'
                '\\end{multicols*}\n\\end{document}\n')
            result = subprocess.run(
                ['pdflatex', '-interaction=nonstopmode', '-halt-on-error',
                 '-shell-escape', '-output-directory=build', 'example.tex'],
                text=True, capture_output=True, cwd=root,
                env={**os.environ, 'TEXINPUTS': '.:' + str(ROOT / 'content/tex') + ':'})
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertTrue((root / 'build/example.pdf').is_file())


if __name__ == '__main__':
    unittest.main()
