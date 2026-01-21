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
    tests = [
        (1, 1),
        (2, 1),
        (2, 2),
        (3, 5),
        (4, 9),
        (5, 42),
        (6, 400),
        (7, 2500),
        (8, 40320),
        (9, 362880)
    ]

    sol = Solution()
    iterations = 1
    sink = 0
    for iter in range(iterations):
        checksum = 0
        for t in tests:
            res = sol.getPermutation(t[0], t[1])
            checksum += ord(res[0])
            checksum += len(res)
        sink += checksum
    print(sink)