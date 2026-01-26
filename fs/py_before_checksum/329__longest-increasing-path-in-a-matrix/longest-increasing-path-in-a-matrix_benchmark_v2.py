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
    tests = [
        [[42]],
        [[7, 7, 7], [7, 7, 7]],
        [[1, 2, 3, 4, 5]],
        [[1], [2], [3], [4], [5]],
        [[9, 9, 4], [6, 6, 8], [2, 1, 1]],
        [[3, 4, 5], [3, 2, 6], [2, 2, 1]],
        [[1, 2, 3, 4], [12, 13, 14, 5], [11, 16, 15, 6], [10, 9, 8, 7]],
        [[1, 2, 3], [2, 3, 4], [3, 4, 5]],
        [[-1, -2, -3], [-2, -3, -4], [-3, -4, -5]],
        [[1, 2, 1, 2], [2, 1, 2, 1], [1, 2, 1, 2], [2, 1, 2, 1]]
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in xrange(len(tests)):
            checksum += sol.longestIncreasingPath(tests[t])
        sink += checksum
    print(sink)
    # print sink