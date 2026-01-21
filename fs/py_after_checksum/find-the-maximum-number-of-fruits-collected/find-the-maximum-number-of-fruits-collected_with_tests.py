
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
    import time

    # Construct origTests
    origTests = []

    # Test 1: n=1
    origTests.append([[5]])

    # Test 2: n=2
    origTests.append([
        [1, 2],
        [3, 4]
    ])

    # Test 3: n=3
    origTests.append([
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ])

    # Test 4: n=4 all zeros
    n = 4
    t = [[0 for _ in range(n)] for _ in range(n)]
    origTests.append(t)

    # Test 5: n=5 diverse digits
    origTests.append([
        [3, 1, 4, 1, 5],
        [9, 2, 6, 5, 3],
        [5, 8, 9, 7, 9],
        [3, 2, 3, 8, 4],
        [6, 2, 6, 4, 3]
    ])

    # Test 6: n=6 mixed negatives and positives
    origTests.append([
        [0,  -1,  2,  -3,  4,  -5],
        [6,  -7,  8,  -9, 10, -11],
        [12, -13, 14, -15, 16, -17],
        [18, -19, 20, -21, 22, -23],
        [24, -25, 26, -27, 28, -29],
        [30, -31, 32, -33, 34, -35]
    ])

    # Test 7: n=7 programmatic moderate values
    n = 7
    t = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            t[i][j] = ((i + 1) * (j + 1) * 7) % 1000
    origTests.append(t)

    # Test 8: n=8 chessboard pattern
    n = 8
    t = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            t[i][j] = 100 if ((i + j) % 2 == 0) else 1
    origTests.append(t)

    # Test 9: n=9 diagonal-heavy matrix
    n = 9
    t = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            t[i][j] = 50 if (i == j) else abs(i - j)
    origTests.append(t)

    # Test 10: n=10 LCG-filled matrix (deterministic)
    def lcg_next(state_box):
        state_box[0] = (state_box[0] * 1103515245 + 12345) & 0xFFFFFFFF
        return state_box[0]

    state_box = [123456789]
    n = 10
    t = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            t[i][j] = (lcg_next(state_box) >> 16) % 1000
    origTests.append(t)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for k in xrange(len(origTests)):
            fruits = [row[:] for row in origTests[k]]
            try:
                res = sol.maxCollectedFruits(fruits)
            except Exception:
                res = 0
            checksum += res

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: " + str(checksum)
    print "Elapsed time (ms): " + str(elapsed_ms)
