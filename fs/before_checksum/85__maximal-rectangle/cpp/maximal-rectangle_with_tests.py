# Time:  O(n^2)
# Space: O(n)

class Solution(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        def largestRectangleArea(heights):
            stk, result, i = [-1], 0, 0
            for i in xrange(len(heights)+1):
                while stk[-1] != -1 and (i == len(heights) or heights[stk[-1]] >= heights[i]):
                    result = max(result, heights[stk.pop()]*((i-1)-stk[-1]))
                stk.append(i) 
            return result

        if not matrix:
            return 0
        result = 0
        heights = [0]*len(matrix[0])
        for i in xrange(len(matrix)):
            for j in xrange(len(matrix[0])):
                heights[j] = heights[j] + 1 if matrix[i][j] == '1' else 0
            result = max(result, largestRectangleArea(heights))
        return result


# Time:  O(n^2)
# Space: O(n)
# DP solution.
class Solution2(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix:
            return 0

        result = 0
        m = len(matrix)
        n = len(matrix[0])
        L = [0 for _ in xrange(n)]
        H = [0 for _ in xrange(n)]
        R = [n for _ in xrange(n)]

        for i in xrange(m):
            left = 0
            for j in xrange(n):
                if matrix[i][j] == '1':
                    L[j] = max(L[j], left)
                    H[j] += 1
                else:
                    L[j] = 0
                    H[j] = 0
                    R[j] = n
                    left = j + 1

            right = n
            for j in reversed(xrange(n)):
                if matrix[i][j] == '1':
                    R[j] = min(R[j], right)
                    result = max(result, H[j] * (R[j] - L[j]))
                else:
                    right = j

        return result


if __name__ == "__main__":
    import time

    def makeMatrix(lines):
        return [list(row) for row in lines]

    # Prepare 10 diverse test inputs
    testCases = []

    # 1) Empty matrix
    testCases.append([])

    # 2) Matrix with zero columns
    testCases.append(makeMatrix(["", "", ""]))

    # 3) Single cell '0'
    testCases.append(makeMatrix(["0"]))

    # 4) Single cell '1'
    testCases.append(makeMatrix(["1"]))

    # 5) Single row mixed
    testCases.append(makeMatrix(["1011010011001110"]))

    # 6) Single column mixed
    testCases.append(makeMatrix(["1","0","1","1","1","1","0","1"]))

    # 7) All zeros 5x5
    testCases.append(makeMatrix(["00000","00000","00000","00000","00000"]))

    # 8) All ones 5x7
    testCases.append(makeMatrix(["1111111","1111111","1111111","1111111","1111111"]))

    # 9) Checkerboard 6x6 starting with '1'
    lines = []
    for i in range(6):
        row = []
        for j in range(6):
            row.append('1' if ((i + j) % 2 == 0) else '0')
        lines.append(''.join(row))
    testCases.append(makeMatrix(lines))

    # 10) Mixed example
    testCases.append(makeMatrix(["10100","10111","11111","10010"]))

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for i in xrange(len(testCases)):
            checksum += sol.maximalRectangle(testCases[i])

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us