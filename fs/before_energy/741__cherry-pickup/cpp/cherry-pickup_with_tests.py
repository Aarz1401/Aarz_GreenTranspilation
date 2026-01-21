# Time:  O(n^3)
# Space: O(n^2)

class Solution(object):
    def cherryPickup(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        # dp holds the max # of cherries two k-length paths can pickup.
        # The two k-length paths arrive at (i, k - i) and (j, k - j),
        # respectively.
        n = len(grid)
        dp = [[-1 for _ in xrange(n)] for _ in xrange(n)]
        dp[0][0] = grid[0][0]
        max_len = 2 * (n-1)
        directions = [(0, 0), (-1, 0), (0, -1), (-1, -1)]
        for k in xrange(1, max_len+1):
            for i in reversed(xrange(max(0, k-n+1), min(k+1, n))):  # 0 <= i < n, 0 <= k-i < n
                for j in reversed(xrange(i, min(k+1, n))):          # i <= j < n, 0 <= k-j < n
                    if grid[i][k-i] == -1 or grid[j][k-j] == -1:
                        dp[i][j] = -1
                        continue
                    cnt = grid[i][k-i]
                    if i != j:
                        cnt += grid[j][k-j]
                    max_cnt = -1
                    for direction in directions:
                        ii, jj = i+direction[0], j+direction[1]
                        if ii >= 0 and jj >= 0 and dp[ii][jj] >= 0:
                            max_cnt = max(max_cnt, dp[ii][jj]+cnt)
                    dp[i][j] = max_cnt
        return max(dp[n-1][n-1], 0)


if __name__ == "__main__":
    from timeit import default_timer as timer

    tests = []

    tests.append([
        [5]
    ])

    tests.append([
        [1, 2],
        [3, 4]
    ])

    tests.append([
        [0, 1, -1],
        [1, 0, -1],
        [1, 1,  1]
    ])

    tests.append([
        [1, -1, 1],
        [-1, -1, 1],
        [1,  1, 1]
    ])

    tests.append([
        [1, 0, 0, 1],
        [1, -1, -1, 1],
        [1, 1,  1, 1],
        [0, -1, 1, 10]
    ])

    tests.append([
        [1, 2, 3, 4, 5],
        [1, -1, -1, -1, 1],
        [1, -1, 10, -1, 1],
        [1, -1, -1, -1, 1],
        [5, 4, 3, 2, 1]
    ])

    tests.append([
        [0, 1, 0, 1, 0, 1],
        [1, -1, 1, -1, 1, 0],
        [0, 1, 0, 1, 0, 1],
        [1, -1, 1, -1, 1, 0],
        [0, 1, 0, 1, 0, 1],
        [1, 0, 1, 0, 1, 0]
    ])

    tests.append([
        [1, 0, 0, 0, 0, 0, 1],
        [0, -1, -1, -1, -1, 0, 0],
        [0, -1, 5,  5,  -1, 0, 0],
        [0, -1, 5,  5,  -1, 0, 0],
        [0, -1, -1, -1, -1, 0, 0],
        [0, 0,  0,  0,  0,  0, 0],
        [1, 0,  0,  0,  0,  0, 1]
    ])

    tests.append([
        [1, 1, 1, 1, 1, 1, 1, 1],
        [1, -1, -1, -1, -1, -1, -1, 1],
        [1, -1, 2,  2,  2,  2,  -1, 1],
        [1, -1, 2,  -1, -1, 2,  -1, 1],
        [1, -1, 2,  -1, -1, 2,  -1, 1],
        [1, -1, 2,  2,  2,  2,  -1, 1],
        [1, -1, -1, -1, -1, -1, -1, 1],
        [1, 1, 1, 1, 1, 1, 1, 1]
    ])

    tests.append([
        [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
        [1, -1, 1, -1, 1, -1, 1, -1, 1, 2],
        [2, 1, 2, 1, 2, 1, 2, 1, 2, 3],
        [3, -1, 3, -1, 3, -1, 3, -1, 3, 4],
        [4, 3, 4, 3, 4, 3, 4, 3, 4, 5],
        [5, -1, 5, -1, 5, -1, 5, -1, 5, 6],
        [6, 5, 6, 5, 6, 5, 6, 5, 6, 7],
        [7, -1, 7, -1, 7, -1, 7, -1, 7, 8],
        [8, 7, 8, 7, 8, 7, 8, 7, 8, 9],
        [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
    ])

    sol = Solution()
    checksum = 0

    start = timer()
    iterations = 1000
    for it in xrange(iterations):
        for t in tests:
            grid = [row[:] for row in t]
            checksum += sol.cherryPickup(grid)
    end = timer()

    elapsed_us = int(round((end - start) * 1000000.0))
    print 'Checksum:', checksum
    print 'Elapsed time (microseconds):', elapsed_us