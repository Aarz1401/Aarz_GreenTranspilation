# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(rlogr + qlogr), r = max(nums)
# Space: O(r)

import collections
import bisect


# number theory, freq table, prefix sum, binary search
class Solution(object):
    def gcdValues(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        if not nums:
            return [0]*len(queries)
        cnt1 = collections.Counter(nums)
        cnt2 = [0]*(max(nums)+1)
        for g in reversed(xrange(1, len(cnt2))):
            c = sum(cnt1[ng] for ng in xrange(g, len(cnt2), g))
            cnt2[g] = c*(c-1)//2-sum(cnt2[ng] for ng in xrange(g+g, len(cnt2), g))
        prefix = [0]*(len(cnt2)+1)
        for i in xrange(len(prefix)-1):
            prefix[i+1] = prefix[i]+cnt2[i]
        return [bisect.bisect_right(prefix, q)-1 for q in queries]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # Case 1: Empty nums
        ([], [0, 1, 2, 3, 4]),
        # Case 3: Repeated number small array
        ([5, 5, 5], [0, 1, 2]),
        # Case 5: All primes
        ([2, 3, 5, 7, 11, 13], [0, 1, 5, 10, 14]),
        # Case 7: Sequence 1..30
        ([i for i in xrange(1, 31)], [0, 10, 50, 100, 200, 300, 400]),
        # Case 9: Mixed small numbers under 50
        ([1, 12, 6, 18, 24, 36, 30, 42, 48, 20, 25, 15, 35, 14, 28, 21, 7, 27, 9, 3], [0, 5, 10, 20, 30, 40, 50]),

        # Case 2: Single element (long long queries)
        ([10], [0L, 1L, 2L]),
        # Case 4: Mixed duplicates small range (long long queries)
        ([2, 4, 6, 8, 10, 12], [0L, 3L, 5L, 8L, 10L]),
        # Case 6: Many identical values (long long queries)
        ([7] * 20, [0L, 50L, 100L, 150L, 189L]),
        # Case 8: Moderate high values but bounded r (long long queries)
        ([12, 24, 36, 48], [0L, 1L, 2L, 3L, 5L]),
        # Case 10: Many ones plus others (long long queries)
        ([1] * 15 + [2, 3, 4, 5, 6, 7, 8, 9, 10], [0L, 20L, 50L, 100L, 150L, 200L]),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.gcdValues(*test)
        else:
            sol.gcdValues(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.gcdValues(*test)
            else:
                result = sol.gcdValues(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
