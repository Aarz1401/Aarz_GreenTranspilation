# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        [
            [0, 2, 0, 2, 1],
            [2, 0, 2, 1, 0],
            [0, 2, 1, 0, 2],
            [2, 1, 0, 2, 0],
            [1, 0, 2, 0, 2]
        ]
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.lenOfVDiagonal(*test)
        else:
            sol.lenOfVDiagonal(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.lenOfVDiagonal(*test)
            else:
                result = sol.lenOfVDiagonal(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()