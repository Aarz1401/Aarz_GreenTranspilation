# Time:  O(n * l)
# Space: O(l)

class Solution(object):
    def numMusicPlaylists(self, N, L, K):
        """
        :type N: int
        :type L: int
        :type K: int
        :rtype: int
        """
        M = 10**9+7
        dp = [[0 for _ in xrange(1+L)] for _ in xrange(2)]
        dp[0][0] = dp[1][1] = 1
        for n in xrange(1, N+1):
            dp[n % 2][n] = (dp[(n-1) % 2][n-1] * n) % M
            for l in xrange(n+1, L+1):
                dp[n % 2][l] = ((dp[n % 2][l-1] * max(n-K, 0)) % M + \
                                (dp[(n-1) % 2][l-1] * n) % M) % M
        return dp[N % 2][L]


if __name__ == "__main__":
    tests = [
        (1, 1, 0),
        (2, 2, 1),
        (2, 3, 0),
        (3, 3, 2),
        (3, 4, 1),
        (3, 5, 1),
        (4, 4, 3),
        (4, 6, 2),
        (5, 7, 0),
        (6, 8, 1)
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for i in xrange(iterations):
        #checksum = 0
        for t in tests:
            r = sol.numMusicPlaylists(t[0], t[1], t[2])
        #sink = checksum

    # print sink