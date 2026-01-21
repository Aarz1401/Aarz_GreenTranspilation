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
        diff = defaultdict(int)
        for x in nums:
            diff[x] += 0
            diff[x-k] += 1
            diff[x+k+1] -= 1
        result = curr = 0
        for x, c in sorted(diff.iteritems()):
            curr += c
            result = max(result, cnt[x]+min(curr-cnt[x], numOperations))
        return result


if __name__ == "__main__":
    from collections import namedtuple

    TestCase = namedtuple('TestCase', ['nums', 'k', 'ops'])

    tests = [
        TestCase([5, 5, 5, 5], 0, 0),
        TestCase([1, 2, 3, 4, 5], 0, 2),
        TestCase([1, 1, 2, 2, 3, 3], 1, 2),
        TestCase([10, 20, 30, 40, 50], 100, 1),
        TestCase([-5, -3, -1, 0, 2, 4], 2, 3),
        TestCase([7], 0, 100),
        TestCase([1, 1, 1, 2, 2, 4, 4, 4, 4, 5, 6, 6, 6, 7, 7, 8], 0, 1000),
        TestCase([1000000000, -1000000000, 0, 999999999, -999999999], 2000000000, 2),
        TestCase([1, 2, 2, 2, 5, 5, 8, 9, 10], 3, 2),
        TestCase([0, 1, 3, 6, 10, 15, 21, 28, 36, 45], 4, 5),
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for tc in tests:
            nums = list(tc.nums)
            checksum += sol.maxFrequency(nums, tc.k, tc.ops)
        sink += checksum
    print(sink)

    # print sink