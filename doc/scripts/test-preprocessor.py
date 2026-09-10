#!/usr/bin/env python3
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

PREPROCESSOR = Path(__file__).resolve().parents[2] / 'content/tex/preprocessor.py'


class PreprocessorTest(unittest.TestCase):
    def render(self, metadata):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'build').mkdir()
            source = '/**\n' + metadata + '\n */\nint answer(){ return 42; }\n'
            result = subprocess.run(
                [sys.executable, str(PREPROCESSOR), '-l', 'py', '-c', 'Example.h'],
                input=source, text=True, capture_output=True, cwd=root, check=True)
            return result.stdout

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


if __name__ == '__main__':
    unittest.main()
