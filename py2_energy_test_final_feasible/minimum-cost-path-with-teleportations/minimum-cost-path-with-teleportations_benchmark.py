# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(k * (m * n + r))
# Space: O(m * n + r)

# dp, prefix sum
class Solution(object):
    def minCost(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        m = len(grid)
        n = len(grid[0])
        dp = [[float("inf")]*n for _ in xrange(m)]
        dp[-1][-1] = 0
        mx = max(max(row) for row in grid)
        prefix = [float("inf")]*(mx+1)
        for i in xrange(k+1):
            for r in reversed(xrange(m)):
                for c in reversed(xrange(n)):
                    if r+1 < m:
                        if dp[r+1][c]+grid[r+1][c] < dp[r][c]:
                            dp[r][c] = dp[r+1][c]+grid[r+1][c]
                    if c+1 < n:
                        if dp[r][c+1]+grid[r][c+1] < dp[r][c]:
                            dp[r][c] = dp[r][c+1]+grid[r][c+1]
                    if prefix[grid[r][c]] < dp[r][c]:
                        dp[r][c] = prefix[grid[r][c]]
            for r in xrange(m):
                for c in xrange(n):
                    if dp[r][c] < prefix[grid[r][c]]:
                        prefix[grid[r][c]] = dp[r][c]
            for i in xrange(mx):
                if prefix[i] < prefix[i+1]:
                    prefix[i+1] = prefix[i]
        return dp[0][0]


# Time:  O(k * (m * n + r))
# Space: O(m * n + r)
# dp, prefix sum
class Solution2(object):
    def minCost(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        dp = [[float("inf")]*len(grid[0]) for _ in xrange(len(grid))]
        dp[-1][-1] = 0
        mx = max(max(row) for row in grid)
        prefix = [float("inf")]*(mx+1)
        for i in xrange(k+1):
            for r in reversed(xrange(len(grid))):
                for c in reversed(xrange(len(grid[0]))):
                    if r+1 < len(grid):
                        dp[r][c] = min(dp[r][c], dp[r+1][c]+grid[r+1][c])
                    if c+1 < len(grid[0]):
                        dp[r][c] = min(dp[r][c], dp[r][c+1]+grid[r][c+1])
                    dp[r][c] = min(dp[r][c], prefix[grid[r][c]])
            for r in xrange(len(grid)):
                for c in xrange(len(grid[0])):
                    prefix[grid[r][c]] = min(prefix[grid[r][c]], dp[r][c])
            for i in xrange(len(prefix)-1):
                prefix[i+1] = min(prefix[i+1], prefix[i])
        return dp[0][0]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (
            [[0]],
            0
        ),
        (
            [[1, 2, 3, 4, 5]],
            0
        ),
        (
            [[5], [4], [3], [2], [1]],
            0
        ),
        (
            [[1, 100, 1],
             [1, 100, 1],
             [1, 1, 1]],
            1
        ),
        (
            [[0, 0, 0, 0],
             [0, 5, 5, 0],
             [0, 5, 5, 0],
             [0, 0, 0, 0]],
            2
        ),
        (
            [[7, 2, 9],
             [1, 3, 4]],
            1
        ),
        (
            [[8, 1],
             [6, 2],
             [4, 3]],
            2
        ),
        (
            [[9, 8, 7, 6, 5],
             [1, 1, 1, 1, 1],
             [5, 6, 7, 8, 9],
             [2, 2, 2, 2, 2],
             [9, 9, 9, 9, 9]],
            3
        ),
        (
            [[3, 1, 4, 1],
             [5, 9, 2, 6]],
            1
        ),
        (
            [[0, 1, 0, 1, 0, 1, 0, 1, 0, 1]],
            4
        ),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.minCost(*test)
        else:
            sol.minCost(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.minCost(*test)
            else:
                result = sol.minCost(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()