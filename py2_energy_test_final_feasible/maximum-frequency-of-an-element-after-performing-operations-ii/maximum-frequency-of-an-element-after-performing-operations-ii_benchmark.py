# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn)
# Space: O(n)

import collections


# sort, freq table, two pointers, sliding window
class Solution(object):
    def maxFrequency(self, nums, k, numOperations):
        """
        :type nums: List[int]
        :type k: int
        :type numOperations: int
        :rtype: int
        """
        nums.sort()
        result = 0
        left, right = 0, -1
        cnt = collections.defaultdict(int)
        for i in xrange(len(nums)):
            while right+1 < len(nums) and nums[right+1]-nums[i] <= k:
                cnt[nums[right+1]] += 1 
                right += 1
            while nums[i]-nums[left] > k:
                cnt[nums[left]] -= 1
                left += 1
            result = max(result, cnt[nums[i]]+min((right-left+1)-cnt[nums[i]], numOperations))
        left = 0
        for right in xrange(len(nums)):
            while nums[left]+k < nums[right]-k:
                left += 1
            result = max(result, min(right-left+1, numOperations))
        return result
    

# Time:  O(nlogn)
# Space: O(n)
import collections


# sort, freq table, difference array, line sweep
class Solution2(object):
    def maxFrequency(self, nums, k, numOperations):
        """
        :type nums: List[int]
        :type k: int
        :type numOperations: int
        :rtype: int
        """
        cnt = collections.defaultdict(int)  # defaultdict is much faster than Counter
        for x in nums:
            cnt[x] += 1
        diff = collections.defaultdict(int)
        for x in nums:
            diff[x] += 0
            diff[x-k] += 1
            diff[x+k+1] -= 1
        result = curr = 0
        for x, c in sorted(diff.iteritems()):
            curr += c
            result = max(result, cnt[x]+min(curr-cnt[x], numOperations))
        return result

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([], 5, 3),
        ([42], 0, 0),
        ([5, 5, 5, 5, 5], 0, 10),
        ([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 2, 3),
        ([-15, -10, -5, 0, 5, 10, 15], 5, 4),
        ([1, 100, 200, 300, 400], 1000, 2),
        ([1, 1, 2, 2, 3, 3, 3, 4], 0, 2),
        ([1, 3, 5, 7, 9, 11, 13, 15, 17, 19], 1, 100),
        ([2147483547, 2147483644, 2147483645, 2147483646, 2147483647], 2, 3),
        ([((j * 37) % 100) - 50 for j in xrange(100)], 10, 20),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxFrequency(*test)
        else:
            sol.maxFrequency(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxFrequency(*test)
            else:
                result = sol.maxFrequency(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
