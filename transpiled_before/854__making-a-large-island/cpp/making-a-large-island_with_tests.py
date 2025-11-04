# Time:  O(n^2)
# Space: O(n^2)


class Solution(object):
    def largestIsland(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

        def dfs(r, c, index, grid):
            if not (0 <= r < len(grid) and
                    0 <= c < len(grid[0]) and
                    grid[r][c] == 1):
                return 0
            result = 1
            grid[r][c] = index
            for d in directions:
                result += dfs(r+d[0], c+d[1], index, grid)
            return result

        area = {}
        index = 2
        for r in xrange(len(grid)):
            for c in xrange(len(grid[r])):
                if grid[r][c] == 1:
                    area[index] = dfs(r, c, index, grid)
                    index += 1

        result = max(area.values() or [0])
        for r in xrange(len(grid)):
            for c in xrange(len(grid[r])):
                if grid[r][c] == 0:
                    seen = set()
                    for d in directions:
                        nr, nc = r+d[0], c+d[1]
                        if not (0 <= nr < len(grid) and
                                0 <= nc < len(grid[0]) and
                                grid[nr][nc] > 1):
                            continue
                        seen.add(grid[nr][nc])
                    result = max(result, 1 + sum(area[i] for i in seen))
        return result


if __name__ == "__main__":
    # Prepare 10 diverse test grids
    tests = []

    # 1) Empty grid
    tests.append([])

    # 2) 1x1 zero
    tests.append([[0]])

    # 3) 1x1 one
    tests.append([[1]])

    # 4) 3x3 all zeros
    tests.append([
        [0,0,0],
        [0,0,0],
        [0,0,0]
    ])

    # 5) 3x3 all ones
    tests.append([
        [1,1,1],
        [1,1,1],
        [1,1,1]
    ])

    # 6) 4x4 checkerboard
    tests.append([
        [0,1,0,1],
        [1,0,1,0],
        [0,1,0,1],
        [1,0,1,0]
    ])

    # 7) 3x3 center zero (connects all when flipped)
    tests.append([
        [1,1,1],
        [1,0,1],
        [1,1,1]
    ])

    # 8) 5x5 island with holes (donut shape)
    tests.append([
        [1,1,1,1,1],
        [1,0,0,0,1],
        [1,0,1,0,1],
        [1,0,0,0,1],
        [1,1,1,1,1]
    ])

    # 9) 30x30 patterned grid
    big = [[0]*30 for _ in xrange(30)]
    for i in xrange(30):
        for j in xrange(30):
            big[i][j] = 1 if ((i * j + i + j) % 3 == 0) else 0
    tests.append(big)

    # 10) 2x5 irregular pattern
    tests.append([
        [1,1,0,1,0],
        [0,1,1,0,1]
    ])

    sol = Solution()
    checksum = 0

    import time
    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for t in xrange(len(tests)):
            grid = [row[:] for row in tests[t]]  # copy since algorithm mutates the grid
            res = sol.largestIsland(grid)
            checksum += res + t + iter

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us