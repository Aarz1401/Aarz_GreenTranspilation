# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n * k * l), l = limits
# Space: O(n * k * l)

import collections


# dp
class Solution(object):
    def maxProduct(self, nums, k, limit):
        """
        :type nums: List[int]
        :type k: int
        :type limit: int
        :rtype: int
        """
        total = sum(nums)
        if k > total or k < -total:  # optimized to speed up
            return -1
        dp = collections.defaultdict(set)
        for x in nums:
            new_dp = collections.defaultdict(set, {k:set(v) for k, v in dp.iteritems()})
            new_dp[(1, x)].add(min(x, limit+1))
            for (p, total), products in dp.iteritems():
                new_state = (p^1, total+(x if p == 0 else -x))
                for v in products:
                    new_dp[new_state].add(min(v*x, limit+1))
            dp = new_dp
        result = -1
        for (p, total), products in dp.iteritems():
            if total != k:
                continue
            for v in products:
                if v <= limit:
                    result = max(result, v)
        return result

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([1], 1, 10),                # For {1}
        ([2, 3], -1, 10),            # For {2,3}
        ([-2, 4, -1], 4, 100),       # For {-2,4,-1}
        ([0, 5, 6], 0, 100),         # For {0,5,6}
        ([10, 9, 8], 1, 20),         # For {10,9,8}
        ([1, 2, 3], 100, 100),       # For {1,2,3}
        ([2, 5], -3, 100),           # For {2,5}
        ([1, 1, 1, 1], 0, 10),       # For {1,1,1,1}
        ([0, 1], 0, 0),              # For {0,1}
        ([7, -3, 2], 7, 5),          # For {7,-3,2}
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxProduct(*test)
        else:
            sol.maxProduct(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxProduct(*test)
            else:
                result = sol.maxProduct(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()