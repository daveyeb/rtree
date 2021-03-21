Skip to content
careercup
/
CtCI-6th-Edition-Python
Cracking the Coding Interview 6th Ed. Python Solutions

 2.9k stars  1.2k forks
Code
Issues
Pull requests
3
Actions
Security
More
CtCI-6th-Edition-Python/Chapter1/1_Is Unique/IsUnique.py /
@1st
1st Optimize file CheckPermutation.py to be more Pythonic.
…
 History
 1 contributor
36 lines (28 sloc)  847 Bytes
  
# O(N)
import unittest


def unique(string):
    # Assuming character set is ASCII (128 characters)
    if len(string) > 128:
        return False

    char_set = [False for _ in range(128)]
    for char in string:
        val = ord(char)
        if char_set[val]:
            # Char already found in string
            return False
        char_set[val] = True

    return True


class Test(unittest.TestCase):
    dataT = [('abcd'), ('s4fad'), ('')]
    dataF = [('23ds2'), ('hb 627jh=j ()')]

    def test_unique(self):
        # true check
        for test_string in self.dataT:
            actual = unique(test_string)
            self.assertTrue(actual)
        # false check
        for test_string in self.dataF:
            actual = unique(test_string)
            self.assertFalse(actual)

if __name__ == "__main__":
    unittest.main()

