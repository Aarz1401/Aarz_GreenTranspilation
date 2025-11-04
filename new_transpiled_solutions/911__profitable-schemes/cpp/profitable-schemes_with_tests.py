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
    from time import time

    # List of test cases: (n, minProfit, group, profit)
    tests = []
    tests.append((1, 1, [1], [1]))
    tests.append((5, 3, [2, 2], [2, 3]))
    tests.append((10, 5, [2, 3, 5], [6, 7, 8]))
    tests.append((3, 0, [1, 1, 1], [0, 0, 0]))
    tests.append((0, 0, [], []))
    tests.append((1, 2, [2], [2]))
    tests.append((5, 10, [2, 2, 1], [5, 5, 1]))
    tests.append((8, 7, [2, 3, 5, 1, 4], [2, 2, 3, 1, 6]))
    tests.append((50, 20, [5, 7, 10, 3, 6, 2, 8, 4, 9, 1], [6, 7, 8, 3, 5, 1, 9, 2, 10, 0]))
    tests.append((12, 15, [3, 5, 3, 3, 2, 6, 7], [2, 10, 1, 1, 3, 8, 9]))

    sol = Solution()
    checksum = 0

    start = time()
    iterations = 1000
    for _ in xrange(iterations):
        for t in tests:
            n, minProfit, group, profit = t
            checksum += int(sol.profitableSchemes(n, minProfit, group, profit))
    end = time()

    elapsed_ns = int(round((end - start) * 1e9))

    print 'Checksum: {}'.format(checksum)
    print 'Elapsed time (ns): {}'.format(elapsed_ns)