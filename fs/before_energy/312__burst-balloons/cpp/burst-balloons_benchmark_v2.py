# Time:  O(n^3)
# Space: O(n^2)


class Solution(object):
    def maxCoins(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        coins = [1] + [i for i in nums if i > 0] + [1]
        n = len(coins)
        max_coins = [[0 for _ in xrange(n)] for _ in xrange(n)]

        for k in xrange(2, n):
            for left in xrange(n - k):
                right = left + k
                for i in xrange(left + 1, right):
                    max_coins[left][right] = \
                        max(max_coins[left][right],
                            coins[left] * coins[i] * coins[right] +
                            max_coins[left][i] +
                            max_coins[i][right])

        return max_coins[0][-1]


if __name__ == "__main__":
    tests = [
        [3, 1, 5, 8],
        [1],
        [9, 76, 64, 21],
        [1, 5],
        [7, 0, 2, 0, 9],
        [8, 2, 6, 8, 1, 4],
        [2, 2, 2, 2, 2, 2, 2, 2],
        [100, 1, 100, 1, 100],
        [2, 4, 3, 5, 1, 2],
        [1, 0, 3, 0, 5, 0, 8, 0, 13, 0, 21]
    ]

    sink = 0
    iterations = 1000
    for _ in range(iterations):
        #checksum = 0
        sol = Solution()
        for t in tests:
            r = sol.maxCoins(list(t))
        #sink = checksum