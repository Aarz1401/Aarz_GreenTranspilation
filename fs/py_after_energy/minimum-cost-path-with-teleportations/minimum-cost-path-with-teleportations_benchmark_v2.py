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


if __name__ == "__main__":
    tests = [
        ([[0]], 0),
        ([[1, 2], [3, 4]], 0),
        ([[1, 100, 1], [1, 100, 1], [1, 1, 1]], 1),
        ([[5, 1, 3, 2], [4, 2, 1, 9], [8, 1, 1, 1]], 2),
        ([[7, 7, 7], [7, 5, 7], [7, 7, 7], [1, 1, 1]], 3),
        ([[1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 1], [5, 6, 7, 1, 2]], 5),
        ([[9, 8, 7, 6, 5], [1, 2, 3, 4, 5]], 10),
        ([[0, 2, 1, 0, 3, 1], [4, 0, 2, 1, 0, 2], [1, 3, 0, 2, 2, 0], [2, 1, 2, 0, 1, 3], [0, 2, 1, 3, 0, 1], [1, 0, 2, 1, 2, 0]], 0),
        ([[3, 1, 4, 1, 5]], 2),
        ([[2], [7], [1], [8], [2]], 2)
    ]

    sol = Solution()
    sink = 0
    iterations = 1000
    for _ in range(iterations):
        #checksum = 0
        for tc in tests:
            r = sol.minCost(tc[0], tc[1])
        # sink = checksum
    # print sink