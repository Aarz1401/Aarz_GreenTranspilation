# Time:  O(n^2)
# Space: O(n)

import math

# Cantor ordering solution
class Solution(object):
    def getPermutation(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        seq, k, fact = "", k - 1, math.factorial(n - 1)
        perm = [i for i in xrange(1, n + 1)]
        for i in reversed(xrange(n)):
            curr = perm[k / fact]
            seq += str(curr)
            perm.remove(curr)
            if i > 0:
                k %= fact
                fact /= i
        return seq

if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs (n, k)
    tests = [
        (1, 1),
        (2, 1),
        (2, 2),
        (3, 1),
        (3, 6),       # max for n=3
        (4, 9),       # mid for n=4
        (5, 120),     # max for n=5
        (6, 400),     # within range for n=6 (<=720)
        (7, 5040),    # max for n=7
        (9, 362880)   # max for n=9
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for t in xrange(len(tests)):
            n, k = tests[t]
            res = sol.getPermutation(n, k)
            for ch in res:
                checksum = ((checksum * 1315423911) ^ ord(ch)) & 0xFFFFFFFFFFFFFFFF

    end = time.time()
    elapsed_us = int(round((end - start) * 1e6))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us