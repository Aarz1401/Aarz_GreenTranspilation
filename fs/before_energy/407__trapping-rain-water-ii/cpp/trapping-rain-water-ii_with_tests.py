# Time:  O(m * n * log(m + n)) ~ O(m * n * log(m * n))
# Space: O(m * n)

from heapq import heappush, heappop

class Solution(object):
    def trapRainWater(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        m = len(heightMap)
        if not m:
            return 0
        n = len(heightMap[0])
        if not n:
            return 0

        is_visited = [[False for i in xrange(n)] for j in xrange(m)]

        heap = []
        for i in xrange(m):
            heappush(heap, [heightMap[i][0], i, 0])
            is_visited[i][0] = True
            heappush(heap, [heightMap[i][n-1], i, n-1])
            is_visited[i][n-1] = True
        for j in xrange(1, n-1):
            heappush(heap, [heightMap[0][j], 0, j])
            is_visited[0][j] = True
            heappush(heap, [heightMap[m-1][j], m-1, j])
            is_visited[m-1][j] = True

        trap = 0
        while heap:
            height, i, j = heappop(heap)
            for (dx, dy) in [(1,0), (-1,0), (0,1), (0,-1)]:
                x, y = i+dx, j+dy
                if 0 <= x < m and 0 <= y < n and not is_visited[x][y]:
                    trap += max(0, height - heightMap[x][y])
                    heappush(heap, [max(height, heightMap[x][y]), x, y])
                    is_visited[x][y] = True

        return trap

if __name__ == "__main__":
    import time
    import random

    # Define 10 diverse test inputs
    t1 = []  # empty

    t2 = [
        [5]
    ]

    t3 = [
        [3, 1, 2, 4, 0, 1, 3]  # single row
    ]

    t4 = [
        [3],
        [0],
        [2],
        [0],
        [4]  # single column
    ]

    t5 = [
        [5, 5, 5],
        [5, 1, 5],
        [5, 5, 5]  # bowl with center low
    ]

    t6 = [
        [3, 3, 3, 3],
        [3, 1, 2, 3],
        [3, 2, 1, 3],
        [3, 3, 3, 3]  # interior valley
    ]

    t7 = [
        [5, 5, 5, 5, 5],
        [5, 1, 1, 1, 5],
        [0, 0, 0, 0, 0],  # boundary path to zero allows drainage
        [5, 1, 1, 1, 5],
        [5, 5, 5, 5, 5]
    ]

    # Random 10x10 with fixed seed
    t8 = [[0] * 10 for _ in range(10)]
    _rng = random.Random(123456789)
    for i in range(10):
        for j in range(10):
            t8[i][j] = _rng.randint(0, 9)

    # Gradient 30x30: higher at borders, lower inside
    m, n = 30, 30
    t9 = [[0] * n for _ in range(m)]
    for i in range(m):
        for j in range(n):
            d = min(min(i, m - 1 - i), min(j, n - 1 - j))
            h = 9 - d
            if h < 0:
                h = 0
            t9[i][j] = h

    # Flat 20x20 all same height
    t10 = [[7] * 20 for _ in range(20)]

    tests = []
    tests.append(t1)
    tests.append(t2)
    tests.append(t3)
    tests.append(t4)
    tests.append(t5)
    tests.append(t6)
    tests.append(t7)
    tests.append(t8)
    tests.append(t9)
    tests.append(t10)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in range(iterations):
        for i in range(len(tests)):
            checksum += sol.trapRainWater(tests[i])
            checksum ^= (checksum << 1) ^ long(i + 31)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print 'Checksum:', checksum
    print 'Elapsed time (microseconds):', elapsed_us