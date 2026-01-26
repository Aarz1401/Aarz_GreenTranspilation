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
    tests = [
        [[1, 4, 3], [3, 1, 5], [2, 2, 2]],
        [[3, 3, 3], [3, 3, 3], [3, 3, 3]],
        [[1, 0, 2, 1, 0]],
        [[5, 5, 5, 5, 5],
         [5, 1, 2, 1, 5],
         [5, 2, 1, 2, 5],
         [5, 1, 2, 1, 5],
         [5, 5, 5, 5, 5]],
        [[1, 2, 3, 4],
         [2, 3, 4, 5],
         [3, 4, 5, 6],
         [4, 5, 6, 7]],
        [[3, 3, 3],
         [3, 1, 3]],
        [[5, 5, 5, 5],
         [5, 1, 4, 5],
         [5, 5, 5, 5]],
        [[8, 8, 8, 8, 8, 8],
         [8, 2, 3, 4, 3, 8],
         [8, 3, 1, 2, 4, 8],
         [8, 4, 2, 1, 3, 8],
         [8, 3, 4, 3, 2, 8],
         [8, 8, 8, 8, 8, 8]],
        [[2, 2, 2],
         [2, 0, 2],
         [2, 2, 2]],
        [[9, 9, 9, 9, 9],
         [9, 1, 8, 1, 9],
         [9, 9, 9, 9, 9]]
    ]

    sol = Solution()
    iterations = 1
    sink = 0
    for iter in xrange(iterations):
        checksum = 0
        for i in xrange(len(tests)):
            checksum += sol.trapRainWater(tests[i])
        sink += checksum
    print(sink)