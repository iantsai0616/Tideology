#!/usr/bin/env python3
import subprocess
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[2] / 'content/contest/s.sh'


class StressScriptTest(unittest.TestCase):
    def test_compile_failure_does_not_run_stale_program(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'gen.cpp').write_text('this is not valid C++;')
            (root / 'gen').write_text('#!/bin/sh\ntouch stale-ran\n')
            (root / 'gen').chmod(0o755)
            result = subprocess.run(['bash', str(SCRIPT)], cwd=root,
                                    text=True, capture_output=True, timeout=10)
            self.assertNotEqual(result.returncode, 0)
            self.assertFalse((root / 'stale-ran').exists())
            self.assertEqual(result.stdout, '')

    def test_runtime_failure_stops_immediately(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name in ['gen', 'good', 'bad']:
                (root / (name + '.cpp')).write_text('int main(){ return 9; }')
            result = subprocess.run(['bash', str(SCRIPT)], cwd=root,
                                    text=True, capture_output=True, timeout=10)
            self.assertEqual(result.returncode, 9)
            self.assertFalse((root / 'out1').exists())
            self.assertEqual(result.stdout, '')

    def test_equal_cases_continue_without_progress_output(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'gen.cpp').write_text(
                '#include <cstdio>\nint main(){ int n = 0; FILE *f = fopen("count", "r");'
                'if(f){ fscanf(f, "%d", &n); fclose(f); } if(n == 3) return 13;'
                'f = fopen("count", "w"); fprintf(f, "%d", n + 1); fclose(f); puts("7"); }')
            for name in ['good', 'bad']:
                (root / (name + '.cpp')).write_text(
                    '#include <cstdio>\nint main(){ int x; scanf("%d", &x); printf("%d\\n", x); }')
            result = subprocess.run(['bash', str(SCRIPT)], cwd=root,
                                    text=True, capture_output=True, timeout=10)
            self.assertEqual(result.returncode, 13)
            self.assertEqual((root / 'count').read_text(), '3')
            self.assertEqual(result.stdout, '')
            self.assertEqual(result.stderr, '')

    def test_compiles_and_prints_only_difference(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'gen.cpp').write_text('#include <cstdio>\nint main(){ puts("7"); }')
            (root / 'good.cpp').write_text(
                '#include <cstdio>\nint main(){ int x; scanf("%d", &x); printf("%d\\n", x); }')
            (root / 'bad.cpp').write_text(
                '#include <cstdio>\nint main(){ int x; scanf("%d", &x); printf("%d\\n", x + 1); }')
            result = subprocess.run(['bash', str(SCRIPT)], cwd=root,
                                    text=True, capture_output=True, timeout=10)
            self.assertEqual(result.stderr, '')
            self.assertEqual(result.stdout, '1c1\n< 7\n---\n> 8\n')
            self.assertEqual((root / 'in').read_text(), '7\n')
            for name in ['gen', 'good', 'bad']:
                self.assertTrue((root / name).is_file())


if __name__ == '__main__':
    unittest.main()
