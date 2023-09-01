import pathlib
import re
import subprocess
import unittest

class TestLab0(unittest.TestCase):

    PATH = pathlib.Path('/proc/count')

    def _make():
        result = subprocess.run(['make'], capture_output=True, text=True)
        return result

    def _insmod():
        result = subprocess.run(['sudo', 'insmod', 'proc_count.ko'],
                                capture_output=True, text=True)
        return result

    def _rmmod():
        result = subprocess.run(['sudo', 'rmmod', 'proc_count'],
                                capture_output=True, text=True)
        return result

    def _make_clean():
        result = subprocess.run(['make', 'clean'],
                                capture_output=True, text=True)
        return result

    @classmethod
    def setUpClass(cls):
        cls.make = cls._make().returncode == 0
        cls.insmod = cls._insmod().returncode == 0

    @classmethod
    def tearDownClass(cls):
        cls._rmmod()
        cls._make_clean()

    def test_exists(self):
        self.assertTrue(self.make, msg='make failed')
        self.assertTrue(self.insmod, msg='insmod failed')

        self.assertTrue(self.PATH.exists(),
                        msg=f'{self.PATH} does not exist with module')
        TestLab0._rmmod()

        self.assertFalse(self.PATH.exists(),
                         msg=f'{self.PATH} exists without module')
        TestLab0._insmod()

    def test_format(self):
        self.assertTrue(self.make, msg='make failed')
        self.assertTrue(self.insmod, msg='insmod failed')

        with open(self.PATH, 'r') as f:
            m = re.match(r'^\d+\n$', f.read(), flags=re.ASCII)
            self.assertIsNotNone(
                m,
                msg='there should only be digits followed by a newline'
            )

    def test_count(self):
        self.assertTrue(self.make, msg='make failed')
        self.assertTrue(self.insmod, msg='insmod failed')

        result = subprocess.run('ps aux | wc -l',
                                capture_output=True, shell=True, text=True)
        with open(self.PATH, 'r') as f:
            self.assertEqual(int(result.stdout), int(f.read()) + 4,
                             msg='number of processes did not match')
