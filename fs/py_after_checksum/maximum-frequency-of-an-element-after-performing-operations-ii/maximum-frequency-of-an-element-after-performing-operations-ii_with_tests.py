
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


if __name__ == '__main__':
    import time

    # Generate diverse test inputs
    tests = []
    # 1. Empty array
    tests.append({'nums': [], 'k': 5, 'ops': 3})
    # 2. Single element
    tests.append({'nums': [10], 'k': 0, 'ops': 0})
    # 3. All equal
    tests.append({'nums': [5, 5, 5, 5, 5], 'k': 0, 'ops': 0})
    # 4. Increasing with small k
    tests.append({'nums': [1, 2, 4, 7, 7, 8, 12], 'k': 2, 'ops': 2})
    # 5. Negative and positive values
    tests.append({'nums': [-10, -8, -7, -3, 0, 1, 2, 9], 'k': 3, 'ops': 3})
    # 6. Large k dominates distances
    tests.append({'nums': [1, 100, 200, 300, 400, 500], 'k': 1000, 'ops': 2})
    # 7. Many duplicates with a small window
    tests.append({'nums': [1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 4], 'k': 1, 'ops': 3})
    # 8. Zero k with large operations
    tests.append({'nums': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 'k': 0, 'ops': 100})
    # 9. Larger patterned array
    arr9 = []
    for i in xrange(120):
        v = (i * i * 31) % 2001 - 1000  # values in [-1000, 1000]
        arr9.append(v)
    tests.append({'nums': arr9, 'k': 10, 'ops': 20})
    # 10. Extreme integer values
    INT_MIN = -2147483648
    INT_MAX = 2147483647
    tests.append({'nums': [INT_MIN, INT_MIN + 1, -1, 0, 1, INT_MAX - 1, INT_MAX], 'k': 2, 'ops': 3})

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for tc in tests:
            numsCopy = list(tc['nums'])  # ensure sort cost each iteration
            res = sol.maxFrequency(numsCopy, tc['k'], tc['ops'])
            checksum += res
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))

    print 'Checksum: %d' % checksum
    print 'Elapsed time (us): %d' % elapsed_us
