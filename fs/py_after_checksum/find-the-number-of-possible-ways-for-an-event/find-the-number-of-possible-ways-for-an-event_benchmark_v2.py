# Time:  precompute: O(max_n^2 + max_y * min(max_n, max_x))
#        runtime:    O(min(n, x))
# Space: O(max_n^2 + max_y * min(max_n, max_x))

MOD = 10**9+7
MAX_N = MAX_X = MAX_Y = 1000
R = min(MAX_N, MAX_X)
NCR = [[0]*(MAX_N+1) for _ in xrange(MAX_N+1)]
DP = [[0]*(MAX_N+1) for _ in xrange(MAX_N+1)]
NCR[0][0] = DP[0][0] = 1
for i in xrange(1, MAX_N+1):
    NCR[i][0] = 1
    for j in xrange(1, i+1):
        NCR[i][j] = (NCR[i-1][j]+NCR[i-1][j-1])%MOD
        DP[i][j] = (DP[i-1][j]*j+DP[i-1][j-1]*j)%MOD
POW = [[1]*(R+1) for _ in xrange(MAX_Y+1)]
for i in xrange(1, MAX_Y+1):
    for j in xrange(1, R+1):
        POW[i][j] = (POW[i][j-1]*i)%MOD

# dp, combinatorics
class Solution(object):
    def numberOfWays(self, n, x, y):
        """
        :type n: int
        :type x: int
        :type y: int
        :rtype: int
        """
        return reduce(lambda accu, x: (accu+x)%MOD, (NCR[x][i]*DP[n][i]*POW[y][i] for i in xrange(1, min(n, x)+1)), 0)

if __name__ == "__main__":
    class InputCase(object):
        def __init__(self, n, x, y):
            self.n = n
            self.x = x
            self.y = y

    tests = [
        InputCase(0, 0, 0),
        InputCase(1, 1, 1),
        InputCase(2, 3, 5),
        InputCase(10, 10, 0),
        InputCase(50, 20, 7),
        InputCase(200, 500, 1000),
        InputCase(1000, 1000, 1000),
        InputCase(999, 1000, 2),
        InputCase(100, 1, 999),
        InputCase(345, 678, 123)
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for tc in tests:
            checksum += sol.numberOfWays(tc.n, tc.x, tc.y)
        sink += checksum
    print(sink)

    # print sink