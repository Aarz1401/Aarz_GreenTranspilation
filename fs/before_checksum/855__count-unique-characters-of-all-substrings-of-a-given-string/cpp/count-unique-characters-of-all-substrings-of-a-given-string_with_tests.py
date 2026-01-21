# Time:  O(n)
# Space: O(1)

import string


class Solution(object):
    def uniqueLetterString(self, S):
        """
        :type S: str
        :rtype: int
        """
        M = 10**9 + 7
        index = {c: [-1, -1] for c in string.ascii_uppercase}
        result = 0
        for i, c in enumerate(S):
            k, j = index[c]
            result = (result + (i-j) * (j-k)) % M
            index[c] = [j, i]
        for c in index:
            k, j = index[c]
            result = (result + (len(S)-j) * (j-k)) % M
        return result


if __name__ == "__main__":
    import time

    # Prepare 10 diverse uppercase test inputs
    tests = []
    tests.append("")                            # 1. Empty string
    tests.append("A")                           # 2. Single character
    tests.append("AAAAAAA")                     # 3. All same character
    tests.append("ABC")                         # 4. All unique, short
    tests.append("ABCA")                        # 5. Repeat with gap
    tests.append("ABABABAB")                    # 6. Alternating pattern
    tests.append("LEETCODE")                    # 7. Typical mixed repeats
    tests.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ")  # 8. All 26 unique

    # 9. Long patterned string cycling A..Z
    t9_chars = []
    for i in xrange(4096):
        t9_chars.append(chr(ord('A') + (i % 26)))
    t9 = "".join(t9_chars)
    tests.append(t9)

    # 10. Long blocks of repeated characters
    t10 = 'A' * 1000 + 'B' * 1000 + 'C' * 1000 + 'D' * 1000
    tests.append(t10)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for s in tests:
            checksum += int(sol.uniqueLetterString(s))

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms