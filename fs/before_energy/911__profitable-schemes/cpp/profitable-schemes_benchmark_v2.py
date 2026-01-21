# Time:  O(n * p * g)
# Space: O(p * g)

import itertools


class Solution(object):
    def profitableSchemes(self, G, P, group, profit):
        """
        :type G: int
        :type P: int
        :type group: List[int]
        :type profit: List[int]
        :rtype: int
        """
        dp = [[0 for _ in xrange(G+1)] for _ in xrange(P+1)]
        dp[0][0] = 1
        for p, g in itertools.izip(profit, group):
            for i in reversed(xrange(P+1)):
                for j in reversed(xrange(G-g+1)):
                    dp[min(i+p, P)][j+g] += dp[i][j]
        return sum(dp[P]) % (10**9 + 7)


if __name__ == "__main__":
    tests = [
        {'n': 1, 'minProfit': 0, 'group': [1], 'profit': [1]},
        {'n': 5, 'minProfit': 3, 'group': [2, 2], 'profit': [2, 3]},
        {'n': 10, 'minProfit': 10, 'group': [2, 3, 5, 4], 'profit': [6, 7, 8, 2]},
        {'n': 5, 'minProfit': 1, 'group': [1, 2, 3], 'profit': [0, 1, 2]},
        {'n': 8, 'minProfit': 6, 'group': [2, 2, 2, 2], 'profit': [1, 2, 3, 4]},
        {'n': 10, 'minProfit': 15, 'group': [2, 2, 2, 2, 2], 'profit': [1, 2, 1, 3, 3]},
        {'n': 100, 'minProfit': 100, 'group': [5] * 20, 'profit': [5] * 20},
        {'n': 64, 'minProfit': 32, 'group': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16], 'profit': [1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4]},
        {'n': 3, 'minProfit': 3, 'group': [1, 1, 1], 'profit': [1, 1, 1]},
        {'n': 50, 'minProfit': 0, 'group': [5] * 10, 'profit': [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]},
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for t in tests:
            g = list(t['group'])
            p = list(t['profit'])
            r = sol.profitableSchemes(t['n'], t['minProfit'], g, p)
        #sink = checksum

    # print sink