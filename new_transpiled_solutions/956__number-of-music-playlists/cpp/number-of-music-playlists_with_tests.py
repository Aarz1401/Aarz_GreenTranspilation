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
    import time

    # Test cases preserved exactly as in C++
    tests = [
        (1, 1, 0),    # minimal case
        (2, 3, 0),    # small, K=0
        (3, 3, 1),    # L==N, K>0
        (3, 2, 0),    # L<N -> 0
        (4, 10, 2),   # moderate
        (7, 12, 5),   # K close to N
        (10, 10, 0),  # L==N, K=0
        (10, 20, 2),  # larger L
        (20, 50, 5),  # larger N and L
        (50, 100, 10) # heavier case
    ]

    sol = Solution()

    start = time.time()

    checksum = 0L
    iterations = 1000
    for iter in xrange(iterations):
        for N, L, K in tests:
            checksum += long(sol.numMusicPlaylists(N, L, K))

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (us): %d" % elapsed_us