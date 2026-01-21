# Time:  O(n^2)
# Space: O(1)

# dp
class Solution(object):
    def maxCollectedFruits(self, fruits):
        """
        :type fruits: List[List[int]]
        :rtype: int
        """
        n = len(fruits)
        for i in xrange(n):
            for j in xrange(i+1, n-(i+1)):
                fruits[i][j] = 0
        for i in xrange(1, n-1):
            for j in xrange(i+1, n):
                fruits[i][j] += max(fruits[i-1][j-1], fruits[i-1][j], fruits[i-1][j+1] if j+1 < n else 0)
        for j in xrange(n):
            for i in xrange(j+1, n-(j+1)):
                fruits[i][j] = 0
        for j in xrange(1, n-1):
            for i in xrange(j+1, n):
                fruits[i][j] += max(fruits[i-1][j-1], fruits[i][j-1], fruits[i+1][j-1] if i+1 < n else 0)
        return sum(fruits[i][i] for i in xrange(n))+fruits[-2][-1]+fruits[-1][-2]
    
if __name__ == "__main__":
    tests = [
        [[7]],
        [[1, 2], [3, 4]],
        [[2, 0, 1], [5, 3, 4], [6, 7, 8]],
        [[0, 2, 3, 1], [4, 0, 6, 2], [7, 8, 0, 3], [1, 5, 9, 0]],
        [[1, 2, 3, 4, 5], [5, 4, 3, 2, 1], [0, 1, 0, 1, 0], [9, 8, 7, 6, 5], [2, 2, 2, 2, 2]],
        [[1, 0, 2, 0, 3, 0], [0, 4, 0, 5, 0, 6], [7, 0, 8, 0, 9, 0], [0, 1, 0, 2, 0, 3], [4, 0, 5, 0, 6, 0], [0, 7, 0, 8, 0, 9]],
        [[9, 1, 2, 3, 4, 5, 6], [6, 5, 4, 3, 2, 1, 0], [1, 3, 5, 7, 9, 2, 4], [2, 4, 6, 8, 1, 3, 5], [5, 3, 1, 0, 2, 4, 6], [7, 5, 3, 1, 9, 8, 7], [0, 2, 4, 6, 8, 1, 3]],
        [[0, 0, 1, 0, 1, 0, 1, 0], [1, 2, 0, 2, 0, 2, 0, 2], [3, 0, 3, 0, 3, 0, 3, 0], [0, 4, 0, 4, 0, 4, 0, 4], [5, 0, 5, 0, 5, 0, 5, 0], [0, 6, 0, 6, 0, 6, 0, 6], [7, 0, 7, 0, 7, 0, 7, 0], [0, 8, 0, 8, 0, 8, 0, 8]],
        [[1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 3, 5, 7, 11, 13, 17, 19, 23], [0, 1, 0, 1, 0, 1, 0, 1, 0], [9, 8, 7, 6, 5, 4, 3, 2, 1], [1, 2, 3, 4, 5, 6, 7, 8, 9], [9, 0, 8, 0, 7, 0, 6, 0, 5], [5, 4, 3, 2, 1, 0, 1, 2, 3], [3, 1, 4, 1, 5, 9, 2, 6, 5], [8, 7, 6, 5, 4, 3, 2, 1, 0]],
        [[10, 9, 8, 7, 6, 5, 4, 3, 2, 1], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [0, 1, 2, 3, 4, 5, 6, 7, 8, 9], [9, 8, 7, 6, 5, 4, 3, 2, 1, 0], [0, 2, 4, 6, 8, 10, 12, 14, 16, 18], [18, 16, 14, 12, 10, 8, 6, 4, 2, 0], [5, 5, 5, 5, 5, 5, 5, 5, 5, 5], [3, 1, 4, 1, 5, 9, 2, 6, 5, 3], [2, 7, 1, 8, 2, 8, 1, 8, 2, 8], [9, 3, 7, 9, 3, 7, 9, 3, 7, 9]]
    ]

    sol = Solution()
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            _input = [row[:] for row in t]
            checksum += sol.maxCollectedFruits(_input)
        sink += checksum
    print(sink)