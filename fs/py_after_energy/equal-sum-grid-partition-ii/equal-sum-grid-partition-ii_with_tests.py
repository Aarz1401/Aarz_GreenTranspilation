
# Time:  O(m * n)
# Space: O(m * n)

# array, hash table
class Solution(object):
    def canPartitionGrid(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        def check(range1, range2, get):
            curr = 0
            lookup = set()
            begin = -1
            for i in range1:
                if begin == -1:
                    begin = i
                for j in range2:
                    curr += get(i, j)
                    lookup.add(get(i, j))
                diff = curr-(total-curr)
                if diff == 0:
                    return True
                if i != begin and j != 0:
                    if diff in lookup:
                        return True
                elif i == begin:
                    if diff in [get(begin, 0), get(begin, j)]:
                        return True
                else:
                    if diff in [get(begin, 0), (get(i, 0))]:
                        return True
            return False
    
        total = sum(sum(row) for row in grid)
        return check(xrange(len(grid)), xrange(len(grid[0])), lambda i, j: grid[i][j]) or \
               check(reversed(xrange(len(grid))), xrange(len(grid[0])), lambda i, j: grid[i][j]) or \
               check(xrange(len(grid[0])), xrange(len(grid)), lambda i, j: grid[j][i]) or \
               check(reversed(xrange(len(grid[0]))), xrange(len(grid)), lambda i, j: grid[j][i])

if __name__ == "__main__":
    import time

    tests = []

    # 1) 1x1 grid
    tests.append([[5]])

    # 2) 1x5 grid
    tests.append([[1, 2, 3, 4, 5]])

    # 3) 5x1 grid
    tests.append([[1], [2], [3], [4], [5]])

    # 4) 2x3 grid
    tests.append([[3, 1, 2],
                  [4, 6, 5]])

    # 5) 3x3 all zeros
    tests.append([[0, 0, 0],
                  [0, 0, 0],
                  [0, 0, 0]])

    # 6) 4x4 mixed positive values
    tests.append([[10, 20, 30, 40],
                  [5, 15, 25, 35],
                  [7, 14, 21, 28],
                  [1, 2, 3, 4]])

    # 7) 3x4 with negatives and positives
    tests.append([[-1, 2, -3, 4],
                  [5, -6, 7, -8],
                  [9, -10, 11, -12]])

    # 8) 6x6 sequential values
    g = [[0 for _ in range(6)] for _ in range(6)]
    val = 1
    for i in range(6):
        for j in range(6):
            g[i][j] = val
            val += 1
    tests.append(g)

    # 9) 8x3 patterned values
    g = [[0 for _ in range(3)] for _ in range(8)]
    for i in range(8):
        for j in range(3):
            g[i][j] = (i + 1) * (j + 2) - (i % 3) + (j % 2)
    tests.append(g)

    # 10) 10x10 with modular pattern including negatives
    g = [[0 for _ in range(10)] for _ in range(10)]
    for i in range(10):
        for j in range(10):
            g[i][j] = ((i * i + j * j + i * j) % 100) - 50
    tests.append(g)

    sol = Solution()

    start = time.time()

    checksum = 0

    iterations = 1000
    for it in range(iterations):
        for t in range(len(tests)):
            checksum += sol.canPartitionGrid(tests[t])

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us
