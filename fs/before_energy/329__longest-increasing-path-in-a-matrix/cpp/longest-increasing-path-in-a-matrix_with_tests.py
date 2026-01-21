# Time:  O(m * n)
# Space: O(m * n)

# topological sort solution
class Solution(object):
    def longestIncreasingPath(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

        if not matrix:
            return 0
        
        in_degree = [[0]*len(matrix[0]) for _ in xrange(len(matrix))]
        for i in xrange(len(matrix)):
            for j in xrange(len(matrix[0])):
                for di, dj in directions:
                    ni, nj = i+di, j+dj
                    if not (0 <= ni < len(matrix) and
                            0 <= nj < len(matrix[0]) and
                            matrix[ni][nj] > matrix[i][j]):
                        continue
                    in_degree[i][j] += 1
        q = []
        for i in xrange(len(matrix)):
            for j in xrange(len(matrix[0])):
                if not in_degree[i][j]:
                    q.append((i, j))
        result = 0
        while q:
            new_q = []
            for i, j in q:
                for di, dj in directions:
                    ni, nj = i+di, j+dj
                    if not (0 <= ni < len(matrix) and
                            0 <= nj < len(matrix[0]) and
                            matrix[i][j] > matrix[ni][nj]):
                        continue
                    in_degree[ni][nj] -= 1
                    if not in_degree[ni][nj]:
                        new_q.append((ni, nj))
            q = new_q
            result += 1         
        return result


# Time:  O(m * n)
# Space: O(m * n)
# dfs + memoization solution
class Solution2(object):
    def longestIncreasingPath(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

        def longestpath(matrix, i, j, max_lengths):
            if max_lengths[i][j]:
                return max_lengths[i][j]
            max_depth = 0
            for di, dj in directions:
                x, y = i+di, j+dj
                if 0 <= x < len(matrix) and 0 <= y < len(matrix[0]) and \
                   matrix[x][y] < matrix[i][j]:
                    max_depth = max(max_depth, longestpath(matrix, x, y, max_lengths))
            max_lengths[i][j] = max_depth + 1
            return max_lengths[i][j]

        if not matrix:
            return 0
        result = 0
        max_lengths = [[0 for _ in xrange(len(matrix[0]))] for _ in xrange(len(matrix))]
        for i in xrange(len(matrix)):
            for j in xrange(len(matrix[0])):
                result = max(result, longestpath(matrix, i, j, max_lengths))
        return result

if __name__ == "__main__":
    import time

    test_cases = []
    test_cases.append([])
    test_cases.append([[]])
    test_cases.append([[42]])
    test_cases.append([[1, 2, 3, 4, 5]])
    test_cases.append([[1], [2], [3], [4], [5]])
    test_cases.append([[9, 9, 4], [6, 6, 8], [2, 1, 1]])
    test_cases.append([[9, 8, 7], [6, 5, 4], [3, 2, 1]])
    test_cases.append([[7, 7, 7], [7, 7, 7], [7, 7, 7]])
    test_cases.append([
        [10, 9, 4, 5],
        [11, 8, 7, 6],
        [12, 13, 14, 15],
        [1, 2, 3, 16]
    ])
    test_cases.append([
        [7, 2, 3, 4, 5],
        [36, 35, 34, 33, 6],
        [37, 42, 43, 32, 7],
        [38, 41, 44, 31, 8],
        [39, 40, 45, 30, 9]
    ])

    sol = Solution()
    checksum = 0L

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for matrix in test_cases:
            r = sol.longestIncreasingPath(matrix)
            checksum += r
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))
    print "Checksum: {}".format(checksum)
    print "Elapsed time (microseconds): {}".format(elapsed_us)