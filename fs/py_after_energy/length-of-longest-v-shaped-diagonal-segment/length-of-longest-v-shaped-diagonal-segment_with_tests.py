# Time:  O(n * m)
# Space: O(n * m)

# dp
class Solution(object):
    def lenOfVDiagonal(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n, m = len(grid), len(grid[0])
        result = 0
        down_right = [[1]*m for _ in xrange(n)]
        down_left = [[1]*m for _ in xrange(n)]
        for i in xrange(n):
            for j in xrange(m):
                x = grid[i][j]
                if x == 1:
                    result = 1
                    continue
                if i-1 >= 0 and j-1 >= 0 and grid[i-1][j-1] == 2-x:
                    down_right[i][j] = down_right[i-1][j-1]+1
                if i-1 >= 0 and j+1 < m and grid[i-1][j+1] == 2-x:
                    down_left[i][j] = down_left[i-1][j+1]+1
        up_right = [[1]*m for _ in xrange(n)]
        up_left = [[1]*m for _ in xrange(n)]
        for i in reversed(xrange(n)):
            for j in xrange(m):
                x = grid[i][j]
                if x == 1:
                    continue
                if i+1 < n and j-1 >= 0 and grid[i+1][j-1] == 2-x:
                    up_right[i][j] = up_right[i+1][j-1]+1
                if i+1 < n and j+1 < m and grid[i+1][j+1] == 2-x:
                    up_left[i][j] = up_left[i+1][j+1]+1
        for i in xrange(n):
            for j in xrange(m):
                x = grid[i][j]
                if x == 1:
                    continue
                if (down_right[i][j]%2*2 == 0 and x == 0) or (down_right[i][j]%2 == 1 and x == 2):
                    ni = i-down_right[i][j]
                    nj = j-down_right[i][j]
                    if 0 <= ni < n and 0 <= nj < m and grid[ni][nj] == 1:
                        result = max(result, down_right[i][j]+up_right[i][j])  # >
                if (down_left[i][j]%2 == 0 and x == 0) or (down_left[i][j]%2 == 1 and x == 2):
                    ni = i-down_left[i][j]
                    nj = j+down_left[i][j]
                    if 0 <= ni< n and 0 <= nj < m and grid[ni][nj] == 1:
                        result = max(result, down_left[i][j]+down_right[i][j])  # v
                if (up_left[i][j]%2 == 0 and x == 0) or (up_left[i][j]%2 == 1 and x == 2):
                    ni = i+up_left[i][j]
                    nj = j+up_left[i][j]
                    if 0 <= ni < n and 0 <= nj < m and grid[ni][nj] == 1:
                        result = max(result, up_left[i][j]+down_left[i][j])  # <
                if (up_right[i][j]%2 == 0 and x == 0) or (up_right[i][j]%2 == 1 and x == 2):
                    ni = i+up_right[i][j]
                    nj = j-up_right[i][j]
                    if 0 <= ni < n and 0 <= nj < m and grid[ni][nj] == 1:
                        result = max(result, up_right[i][j]+up_left[i][j])  # ^
        return result


# Time:  O(n * m)
# Space: O(n * m)
# memoization
class Solution2(object):
    def lenOfVDiagonal(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        def memoization(i, j, x, d, k):
            if not (0 <= i < n and 0 <= j < m):
                return 0
            if grid[i][j] != x:
                return 0
            if lookup[k][x][d][i][j] == 0:
                ni, nj = i+directions[d][0], j+directions[d][1]
                nx = 0 if x == 2 else 2
                result = memoization(ni, nj, nx, d, k)+1
                if k != 1:
                    nd = (d+1)%4
                    result = max(result, memoization(ni, nj, nx, nd, k+1)+1)
                lookup[k][x][d][i][j] = result
            return lookup[k][x][d][i][j]

        n, m = len(grid), len(grid[0])
        directions = ((1, 1), (1, -1), (-1, -1), (-1, 1))
        lookup = [[[[[0]*m for _ in xrange(n)] for _ in xrange(4)] for _ in xrange(3)] for _ in xrange(2)]  # be careful with the order, going from smaller dimensions to larger dimensions
        result = 0
        for i in xrange(n):
            for j in xrange(m):
                if grid[i][j] == 1:
                    for d in xrange(4):
                        result = max(result, memoization(i, j, 1, d, 0))
        return result


if __name__ == "__main__":
    import time
    import random

    def makeCheckerboard(r, c, k=None):
        g = [[0 for _ in range(c)] for __ in range(r)]
        for i in range(r):
            for j in range(c):
                g[i][j] = 0 if ((i + j) % 2 == 0) else 2
        return g

    def makeRandomGrid(r, c, seed, p):
        rnd = random.Random(seed)
        g = [[0 for _ in range(c)] for __ in range(r)]
        for i in range(r):
            for j in range(c):
                if rnd.random() < p:
                    g[i][j] = 1
                else:
                    g[i][j] = 0 if ((i + j) % 2 == 0) else 2
        return g

    # Define 10 diverse test inputs
    tests = []
    # 1) 1x1 all ones
    tests.append([[1]])
    # 2) Small manual mixed grid
    tests.append([[1, 0, 2], [2, 1, 0]])
    # 3) 3x5 checkerboard with some 1s
    g = makeCheckerboard(3, 5, 3)
    g[0][2] = 1
    g[2][2] = 1
    tests.append(g)
    # 4) 5x5 random
    tests.append(makeRandomGrid(5, 5, 42, 0.2))
    # 5) 10x10 random
    tests.append(makeRandomGrid(10, 10, 123, 0.1))
    # 6) 7x9 checkerboard with diagonal ones
    g = makeCheckerboard(7, 9)
    for i in range(min(7, 9)):
        g[i][i] = 1
    tests.append(g)
    # 7) 20x20 stripes with periodic ones
    g = [[0 for _ in range(20)] for __ in range(20)]
    for i in range(20):
        for j in range(20):
            if ((i + j) % 7) == 0:
                g[i][j] = 1
            else:
                g[i][j] = 0 if ((i + j) % 2 == 0) else 2
    tests.append(g)
    # 8) 15x15 with center cross of ones
    g = [[0 for _ in range(15)] for __ in range(15)]
    for i in range(15):
        for j in range(15):
            g[i][j] = 0 if ((i + j) % 2 == 0) else 2
    c = 7
    for i in range(15):
        g[i][c] = 1
        g[c][i] = 1
    tests.append(g)
    # 9) 1x10 row alternating with ones at both ends
    g = [[0 for _ in range(10)]]
    for j in range(10):
        g[0][j] = 0 if (j % 2 == 0) else 2
    g[0][0] = 1
    g[0][9] = 1
    tests.append(g)
    # 10) 30x30 random dense
    tests.append(makeRandomGrid(30, 30, 987, 0.12))

    sol = Solution()
    checksum = 0

    t0 = time.time()
    iterations = 1000
    for iter in range(iterations):
        for t in range(len(tests)):
            checksum += sol.lenOfVDiagonal(tests[t])
            checksum ^= (t << (iter % 7))
    t1 = time.time()

    elapsed = int((t1 - t0) * 1000000.0)
    print "Checksum: {}".format(checksum)
    print "Elapsed time (us): {}".format(elapsed)