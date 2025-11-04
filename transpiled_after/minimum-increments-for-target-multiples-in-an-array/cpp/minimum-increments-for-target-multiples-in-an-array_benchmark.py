# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(logr * m * 2^m + n * 3^m)
# Space: O(2^m)

# bitmasks, number theory, dp, submask enumeration
class Solution(object):
    def minimumIncrements(self, nums, target):
        """
        :type nums: List[int]
        :type target: List[int]
        :rtype: int
        """
        INF = float("inf")
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        def lcm(a, b):
            return a//gcd(a, b)*b

        n = len(nums)
        m = len(target)
        lcms = [0]*(1<<m)
        for mask in xrange(1<<m):
            l = 1
            for i in xrange(m):
                if mask&(1<<i):
                    l = lcm(l, target[i])
            lcms[mask] = l
        dp = [INF]*(1<<m)
        dp[0] = 0
        for x in nums:
            for mask in reversed(xrange(1<<m)):
                if dp[mask] == INF:
                    continue
                # submask enumeration:
                # => sum(nCr(n, k) * 2^k for k in xrange(n+1)) = (1 + 2)^n = 3^n
                # => Time: O(3^n), see https://cp-algorithms.com/algebra/all-submasks.html
                submask = new_mask = (((1<<m)-1)-mask)
                while submask:
                    l = lcms[submask]
                    if l == 0:
                        inc = 0
                    else:
                        rem = x % l
                        inc = 0 if rem == 0 else l - rem
                    dp[mask|submask] = min(dp[mask|submask], dp[mask]+inc)
                    submask = (submask-1)&new_mask
        return dp[-1]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([5], [2]),
        ([0], [1, 1]),
        ([1, 2], [3]),
        ([7], []),
        ([4, 8], [4]),
        ([9], [6, 10]),
        ([1], [0]),
        ([1000000000], [2000000000, 1999999999]),
        ([5], [5, 0]),
        ([2], [4, 6, 8]),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.minimumIncrements(*test)
        else:
            sol.minimumIncrements(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.minimumIncrements(*test)
            else:
                result = sol.minimumIncrements(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
