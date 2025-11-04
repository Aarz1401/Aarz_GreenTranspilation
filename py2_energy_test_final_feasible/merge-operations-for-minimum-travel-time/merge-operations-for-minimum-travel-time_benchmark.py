# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O((n - k) * k^3)
# Space: O(k^2)

import collections


# prefix sum, dp
class Solution(object):
    def minTravelTime(self, l, n, k, position, time):
        """
        :type l: int
        :type n: int
        :type k: int
        :type position: List[int]
        :type time: List[int]
        :rtype: int
        """
        prefix = [0]*(n+1)
        for i in xrange(n):
            prefix[i+1] = prefix[i]+time[i]
        dp = collections.defaultdict(lambda: collections.defaultdict(lambda: float("inf")))
        dp[0][time[0]] = 0
        for cnt in xrange(2, (n-k)+1):
            new_dp = collections.defaultdict(lambda: collections.defaultdict(lambda: float("inf")))
            for i in xrange(cnt-1, (cnt-1)+(k+1)):
                for j in xrange(cnt-2, i):
                    for t, c in dp[j].iteritems():
                        new_dp[i][prefix[i+1]-prefix[j+1]] = min(new_dp[i][prefix[i+1]-prefix[j+1]], (position[i]-position[j])*t+c)
            dp = new_dp
        return min(dp[n-1].itervalues())

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (10, 1, 0, [0], [5]),
        (100, 2, 0, [0, 10], [2, 3]),
        (20, 3, 1, [0, 5, 14], [3, 1, 4]),
        (9, 4, 2, [0, 2, 4, 8], [1, 0, 2, 1]),
        (16, 5, 2, [1, 3, 6, 10, 15], [0, 2, 2, 0, 3]),
        (15, 6, 3, [0, 1, 3, 6, 10, 15], [5, 4, 3, 2, 1, 0]),
        (40, 7, 2, [2, 5, 9, 14, 20, 27, 35], [1, 1, 2, 3, 5, 8, 13]),
        (45, 8, 3, [0, 3, 7, 12, 18, 25, 33, 42], [2, 2, 2, 2, 2, 2, 2, 2]),
        (35, 9, 4, [0, 4, 5, 9, 10, 15, 21, 22, 30], [1, 0, 1, 0, 1, 0, 1, 0, 1]),
        (100, 10, 5, [0, 10, 20, 21, 35, 36, 52, 70, 71, 90], [9, 7, 5, 3, 1, 2, 4, 6, 8, 10]),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.minTravelTime(*test)
        else:
            sol.minTravelTime(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.minTravelTime(*test)
            else:
                result = sol.minTravelTime(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()