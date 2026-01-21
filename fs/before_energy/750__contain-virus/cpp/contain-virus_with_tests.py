# Time:  O((m * n)^(4/3)), days = O((m * n)^(1/3))
# Space: O(m * n)

class Solution(object):
    def containVirus(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]

        def dfs(grid, r, c, lookup, regions, frontiers, perimeters):
            if (r, c) in lookup:
                return
            lookup.add((r, c))
            regions[-1].add((r, c))
            for d in directions:
                nr, nc = r+d[0], c+d[1]
                if not (0 <= nr < len(grid) and \
                        0 <= nc < len(grid[r])):
                    continue
                if grid[nr][nc] == 1:
                    dfs(grid, nr, nc, lookup, regions, frontiers, perimeters)
                elif grid[nr][nc] == 0:
                    frontiers[-1].add((nr, nc))
                    perimeters[-1] += 1

        result = 0
        while True:
            lookup, regions, frontiers, perimeters = set(), [], [], []
            for r, row in enumerate(grid):
                for c, val in enumerate(row):
                    if val == 1 and (r, c) not in lookup:
                        regions.append(set())
                        frontiers.append(set())
                        perimeters.append(0)
                        dfs(grid, r, c, lookup, regions, frontiers, perimeters)

            if not regions: break

            triage_idx = frontiers.index(max(frontiers, key = len))
            for i, region in enumerate(regions):
                if i == triage_idx:
                    result += perimeters[i]
                    for r, c in region:
                        grid[r][c] = -1
                    continue
                for r, c in region:
                    for d in directions:
                        nr, nc = r+d[0], c+d[1]
                        if not (0 <= nr < len(grid) and \
                                0 <= nc < len(grid[r])):
                            continue
                        if grid[nr][nc] == 0:
                            grid[nr][nc] = 1

        return result


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs (grids)
    tests = []

    # 1) Single infection in center of 5x5
    g = [[0 for _ in xrange(5)] for __ in xrange(5)]
    g[2][2] = 1
    tests.append(g)

    # 2) Four corners infected in 5x5
    g = [[0 for _ in xrange(5)] for __ in xrange(5)]
    g[0][0] = 1
    g[0][4] = 1
    g[4][0] = 1
    g[4][4] = 1
    tests.append(g)

    # 3) 6x6 checkerboard starting with 1
    g = [[0 for _ in xrange(6)] for __ in xrange(6)]
    for r in xrange(6):
        for c in xrange(6):
            g[r][c] = 1 if ((r + c) % 2 == 0) else 0
    tests.append(g)

    # 4) 4x4 all zeros
    g = [[0 for _ in xrange(4)] for __ in xrange(4)]
    tests.append(g)

    # 5) 4x4 all ones
    g = [[1 for _ in xrange(4)] for __ in xrange(4)]
    tests.append(g)

    # 6) 15x15 deterministic pseudo-random pattern
    g = [[0 for _ in xrange(15)] for __ in xrange(15)]
    for r in xrange(15):
        for c in xrange(15):
            g[r][c] = 1 if (((r * 31 + c * 17) % 7) == 0) else 0
    tests.append(g)

    # 7) 3x10 with middle row infected line
    g = [[0 for _ in xrange(10)] for __ in xrange(3)]
    for c in xrange(10):
        g[1][c] = 1
    tests.append(g)

    # 8) 10x3 with middle column infected line
    g = [[0 for _ in xrange(3)] for __ in xrange(10)]
    for r in xrange(10):
        g[r][1] = 1
    tests.append(g)

    # 9) 7x7 with 3x3 block in center
    g = [[0 for _ in xrange(7)] for __ in xrange(7)]
    for r in xrange(2, 5):
        for c in xrange(2, 5):
            g[r][c] = 1
    tests.append(g)

    # 10) 10x10 with two 3x3 blocks and some noise
    g = [[0 for _ in xrange(10)] for __ in xrange(10)]
    for r in xrange(1, 4):
        for c in xrange(1, 4):
            g[r][c] = 1
    for r in xrange(6, 9):
        for c in xrange(6, 9):
            g[r][c] = 1
    g[0][9] = 1
    g[9][0] = 1
    g[4][5] = 1
    tests.append(g)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            grid = [row[:] for row in tests[i]]  # copy since function mutates
            res = sol.containVirus(grid)
            checksum += res

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us