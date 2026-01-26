
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
    tests = [
        # 1) 1x1 healthy
        [[0]],
        # 2) 1x1 infected
        [[1]],
        # 3) 2x2 single infection
        [
            [1,0],
            [0,0]
        ],
        # 4) 3x3 all infected
        [
            [1,1,1],
            [1,1,1],
            [1,1,1]
        ],
        # 5) 3x4 scattered infections
        [
            [1,0,0,1],
            [0,0,0,0],
            [1,0,1,0]
        ],
        # 6) 5x5 ring with center infection
        [
            [1,1,1,1,1],
            [1,0,0,0,1],
            [1,0,1,0,1],
            [1,0,0,0,1],
            [1,1,1,1,1]
        ],
        # 7) 5x5 mixed pattern
        [
            [0,1,0,0,1],
            [1,1,0,1,0],
            [0,0,1,0,0],
            [1,0,0,1,1],
            [0,1,0,0,0]
        ],
        # 8) 4x7 varied layout
        [
            [0,0,1,0,0,1,0],
            [1,0,1,0,0,0,0],
            [0,0,0,1,1,0,1],
            [1,1,0,0,0,0,0]
        ],
        # 9) 8x8 moderate density
        [
            [0,1,0,0,1,0,0,1],
            [1,0,1,0,0,1,0,0],
            [0,0,0,1,0,0,1,0],
            [1,0,0,0,1,0,0,1],
            [0,1,0,0,0,1,0,0],
            [0,0,1,0,0,0,1,0],
            [1,0,0,1,0,0,0,1],
            [0,0,1,0,1,0,0,0]
        ],
        # 10) 6x6 checkerboard starting with infected
        [
            [1,0,1,0,1,0],
            [0,1,0,1,0,1],
            [1,0,1,0,1,0],
            [0,1,0,1,0,1],
            [1,0,1,0,1,0],
            [0,1,0,1,0,1]
        ]
    ]

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for t in tests:
            grid = [row[:] for row in t]
            s = Solution()
            res = s.containVirus(grid)
            #checksum += res
        #sink = checksum
