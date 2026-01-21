# Time:  O(n^2)
# Space: O(n * d)

import collections


class Solution(object):
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        result = 0
        dp = [collections.defaultdict(int) for i in xrange(len(A))]
        for i in xrange(1, len(A)):
            for j in xrange(i):
                diff = A[i]-A[j]
                dp[i][diff] += 1
                if diff in dp[j]:
                    dp[i][diff] += dp[j][diff]
                    result += dp[j][diff]
        return result

if __name__ == "__main__":
    tests = [
        [1, 2, 3],
        [2, 4, 6, 8, 10],
        [7, 7, 7, 7, 7],
        [1, 1, 2, 2, 3, 3],
        [1, 3, 5, 7, 9, 11, 13],
        [1, 5, 9, 2, 6, 10, 3, 7, 11],
        [0, -1, -2, -3, -4],
        [1, 2, 4, 8, 16, 32],
        [1000000000, -1000000000, 0, -1000000000, 1000000000],
        [1, 4, 7, 10, 13, 2, 5, 8, 11, 14, 17, 20]
    ]

    sink = 0
    sol = Solution()

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for A in tests:
            r = sol.numberOfArithmeticSlices(A)
        #sink = checksum