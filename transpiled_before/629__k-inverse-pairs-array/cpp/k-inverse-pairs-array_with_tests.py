# Time:  O(n * k)
# Space: O(k)

# knapsack dp, combinatorics, sliding window, two pointers
class Solution(object):
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        dp = [1]
        for i in xrange(n):
            new_dp = [0]*min(len(dp)+((i+1)-1), k+1)
            for j in xrange(len(new_dp)):
                new_dp[j] = dp[j] if j < len(dp) else 0
                if j-1 >= 0:
                    new_dp[j] = (new_dp[j]+new_dp[j-1])%MOD
                if j-(i+1) >= 0:
                    new_dp[j] = (new_dp[j]-dp[j-(i+1)])%MOD
            dp = new_dp
        return dp[k] if k < len(dp) else 0


# Time:  O(n * k)
# Space: O(k)
# knapsack dp, combinatorics, sliding window, two pointers
class Solution2(object):
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        dp = [0]*(k+1)
        dp[0] = 1
        for i in xrange(n):
            new_dp = [0]*len(dp)
            for j in xrange(len(dp)):
                new_dp[j] = dp[j]
                if j-1 >= 0:
                    new_dp[j] = (new_dp[j]+new_dp[j-1])%MOD
                if j-(i+1) >= 0:
                    new_dp[j] = (new_dp[j]-dp[j-(i+1)])%MOD
            dp = new_dp
        return dp[-1]


# Time:  O(n * k)
# Space: O(k)
# knapsack dp, combinatorics, sliding window, two pointers
class Solution3(object):
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        dp = [0]*(k+1)
        dp[0] = 1
        for i in xrange(n):
            new_dp = [0]*len(dp)
            curr = 0
            for j in xrange(len(dp)):
                curr = (curr+dp[j])%MOD
                if j-(i+1) >= 0:
                    curr = (curr-dp[j-(i+1)])%MOD
                new_dp[j] = curr
            dp = new_dp
        return dp[-1]


# Time:  O(n^2 * k)
# Space: O(k)
# knapsack dp, combinatorics
class Solution_TLE(object):
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        dp = [0]*(k+1)
        dp[0] = 1
        for i in xrange(n):
            dp = [reduce(lambda total, k: (total+dp[j-k])%MOD, xrange(min(i+1, j+1)), 0) for j in xrange(len(dp))]
        return dp[-1]%MOD


class Solution_ConstructPermutation(object):
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        dp = [[] for _ in xrange(k+1)]
        dp[0].append([])
        for i in xrange(n):
            dp = [[[x+int(x >= i-k) for x in p]+[i-k] for k in xrange(min(i+1, j+1)) for p in dp[j-k]] for j in xrange(len(dp))]
        assert(all(sum(int(p[j] > p[i]) for i in xrange(n) for j in xrange(i)) == len(dp)-1) for p in dp[-1])
        return len(dp[-1])%MOD


class Solution_ConstructPermutation2(object):
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        dp = [[] for _ in xrange(k+1)]
        dp[0].append([])
        for i in xrange(n):
            dp = [[p[:len(p)-k]+[i]+p[len(p)-k:] for k in xrange(min(i+1, j+1)) for p in dp[j-k]] for j in xrange(len(dp))]
        assert(all(sum(int(p[j] > p[i]) for i in xrange(n) for j in xrange(i)) == len(dp)-1) for p in dp[-1])
        return len(dp[-1])%MOD


if __name__ == "__main__":
    # Define 10 diverse test inputs (n, k)
    tests = [
        (1, 0),    # minimal case
        (2, 1),    # small, single inversion
        (3, 0),    # zero inversions
        (3, 4),    # k > max inversions -> should return 0
        (4, 5),    # near max for n=4 (max=6)
        (5, 10),   # exactly max for n=5
        (10, 12),  # moderate
        (20, 50),  # larger moderate
        (100, 0),  # large n, zero inversions
        (200, 100) # larger n, moderate k
    ]

    sol = Solution()
    checksum = 0

    import time
    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for i in xrange(len(tests)):
            n = tests[i][0]
            k = tests[i][1]
            result = sol.kInversePairs(n, k)
            checksum += result

    end = time.time()
    elapsed_us = int(round((end - start) * 1e6))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us