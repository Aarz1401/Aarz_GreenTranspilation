# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n * 2^n)
# Space: O(2^n)

# dp, bitmasks
class Solution(object):
    def maxProfit(self, n, edges, score):
        """
        :type n: int
        :type edges: List[List[int]]
        :type score: List[int]
        :rtype: int
        """
        def popcount(x):
            return bin(x).count('1')

        adj = [0]*n
        for i, j in edges:
            adj[j] |= 1<<i
        dp = [-1]*(1<<n)
        dp[0] = 0 
        for mask in xrange(1<<n):
            if dp[mask] == -1:
                continue
            l = popcount(mask)+1
            for i in xrange(n):
                if mask&(1<<i):
                    continue
                if (mask & adj[i]) == adj[i]: 
                    dp[mask|(1<<i)] = max(dp[mask|(1<<i)], dp[mask]+l*score[i])
        return dp[-1]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (1, [], [7]),
        (2, [(0, 1)], [1, 2]),
        (3, [(0, 1), (0, 2)], [-5, 3, 4]),
        (3, [], [5, -1, 2]),
        (4, [(0, 1), (1, 2), (2, 3)], [3, 1, 4, 2]),
        (4, [(0, 1), (0, 2), (1, 3), (2, 3)], [2, 5, -1, 4]),
        (4, [(0, 1), (2, 3)], [1, 2, 3, 4]),
        (4, [(0, 1), (0, 2), (0, 3), (1, 2), (1, 3), (2, 3)], [-1, -2, -3, -4]),
        (4, [(1, 2), (1, 3)], [0, 0, 10, -10]),
        (4, [(0, 2), (1, 2), (1, 3)], [100, -100, 50, 0]),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxProfit(*test)
        else:
            sol.maxProfit(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxProfit(*test)
            else:
                result = sol.maxProfit(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()