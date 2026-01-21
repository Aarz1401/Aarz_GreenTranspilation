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
    import time

    # Define 10 diverse test inputs
    tests = []

    # 1) 1x1 grid, k=0
    grid1 = [[0]]
    tests.append((grid1, 0))

    # 2) 2x2 grid, k=0
    grid2 = [[1, 2], [3, 4]]
    tests.append((grid2, 0))

    # 3) 3x3 grid with repeating values, k=1
    grid3 = [
        [5, 1, 5],
        [1, 5, 1],
        [5, 1, 5]
    ]
    tests.append((grid3, 1))

    # 4) 5x5 patterned grid, k=2
    grid4 = [[0 for _ in xrange(5)] for _ in xrange(5)]
    for r in xrange(5):
        for c in xrange(5):
            grid4[r][c] = (r * 7 + c * 3) % 10
    tests.append((grid4, 2))

    # 5) 10x10 gradient grid, k=3
    grid5 = [[0 for _ in xrange(10)] for _ in xrange(10)]
    for r in xrange(10):
        for c in xrange(10):
            grid5[r][c] = (r + c) % 10
    tests.append((grid5, 3))

    # 6) 8x12 rectangular grid, k=4
    grid6 = [[0 for _ in xrange(12)] for _ in xrange(8)]
    for r in xrange(8):
        for c in xrange(12):
            grid6[r][c] = (r * 3 + c * 2) % 7
    tests.append((grid6, 4))

    # 7) 12x8 grid with 0 and 100 values, k=5
    grid7 = [[0 for _ in xrange(8)] for _ in xrange(12)]
    for r in xrange(12):
        for c in xrange(8):
            grid7[r][c] = 100 if ((r * r + c) % 2) else 0
    tests.append((grid7, 5))

    # 8) 15x15 all zeros, k=10
    grid8 = [[0 for _ in xrange(15)] for _ in xrange(15)]
    tests.append((grid8, 10))

    # 9) 4x4 all same value, k=6
    grid9 = [[2 for _ in xrange(4)] for _ in xrange(4)]
    tests.append((grid9, 6))

    # 10) 20x20 patterned small values, k=8
    grid10 = [[0 for _ in xrange(20)] for _ in xrange(20)]
    for r in xrange(20):
        for c in xrange(20):
            grid10[r][c] = (r * 17 + c * 23 + 5) % 5
    tests.append((grid10, 8))

    solver = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for i in xrange(len(tests)):
            grid, k = tests[i]
            checksum += solver.minCost(grid, k)
    end = time.time()

    elapsed = int((end - start) * 1000000)

    print "Checksum: " + str(checksum)
    print "Elapsed time (microseconds): " + str(elapsed)