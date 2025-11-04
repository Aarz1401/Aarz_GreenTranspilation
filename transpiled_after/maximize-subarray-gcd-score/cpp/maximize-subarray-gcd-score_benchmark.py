# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn * logr), r = max(nums)
# Space: O(n + logr)

# number theory, suffix-gcd states, dp, binary search
class Solution(object):
    def maxGCDScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a
    
        lookup = [0]*len(nums)
        for i in xrange(len(nums)):
            while nums[i]&1 == 0:
                nums[i] >>= 1
                lookup[i] += 1
        lookup2 = [[] for _ in xrange(max(lookup)+1)]
        for i, e in enumerate(lookup):
            lookup2[e].append(i)
        result = 0
        dp = {}
        for i, x in enumerate(nums):
            new_dp = {}
            new_dp[x, lookup[i]] = [i]*2
            for (g, e), v in dp.iteritems():  # |g * e| = O(logr)
                ng = gcd(g, x)
                ne = min(e, lookup[i])
                if (ng, ne) not in new_dp:
                    new_dp[ng, ne] = [float("inf")]*2
                new_dp[ng, ne][0] = min(new_dp[ng, ne][0], v[0])
                left = bisect_left(lookup2[ne], v[0])  # Time: O(logn)
                right = bisect_right(lookup2[ne], i)-1  # Time: O(logn)
                new_dp[ng, ne][1] = min(new_dp[ng, ne][1], v[0] if right-left+1 <= k else lookup2[ne][right-k]+1)
            dp = new_dp
            for (g, e), v in dp.iteritems():  # |g * e| = O(logr)
                result = max(result, g*(i-v[0]+1)<<e, g*(i-v[1]+1)<<(e+1))
        return result


# Time:  O(n^2 + n * logr), r = max(nums)
# Space: O(1)
# number theory, brute force
class Solution2(object):
    def maxGCDScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        def lower_bit(x):
            return x&-x

        result = 0
        for i in xrange(len(nums)):
            mn = float("inf")
            g = cnt = 0
            for j in xrange(i, len(nums)):
                g = gcd(g, nums[j])
                bit = lower_bit(nums[j])
                if bit < mn:
                    mn = bit
                    cnt = 0
                if bit == mn:
                    cnt += 1
                result = max(result, g*(j-i+1)*(2 if cnt <= k else 1))
                if g*(len(nums)-i)*2 <= result:
                    break
        return result


# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([1], 0),
        ([1048576], 0),
        ([12, 40], 0),
        ([6, 15, 10, 3, 14], 1),
        ([3, 5, 7, 11, 13, 17], 0),
        ([18, 18, 18, 18], 2),
        ([2, 4, 8, 16, 32, 64], 1),
        ([1000000007, 1000000007, 1000000007], 10),
        ([45, 75, 105, 210, 420], 3),
        ([24, 36, 48, 60, 72, 84, 96, 108], 2),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            args = list(test)
            if isinstance(args[0], list):
                args[0] = args[0][:]
            sol.maxGCDScore(*args)
        else:
            if isinstance(test, list):
                sol.maxGCDScore(test[:])
            else:
                sol.maxGCDScore(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                args = list(test)
                if isinstance(args[0], list):
                    args[0] = args[0][:]
                result = sol.maxGCDScore(*args)
            else:
                if isinstance(test, list):
                    result = sol.maxGCDScore(test[:])
                else:
                    result = sol.maxGCDScore(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()