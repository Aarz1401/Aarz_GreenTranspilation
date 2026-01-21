# Time:  O(n)
# Space: O(n)

import collections


# mono deque, two pointers, sliding window
class Solution(object):
    def countNonDecreasingSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        result = cnt = 0
        dq = collections.deque()
        right = len(nums)-1
        for left in reversed(xrange(len(nums))):
            while dq and nums[dq[-1]] < nums[left]:
                l = dq.pop()
                r = dq[-1]-1 if dq else right
                cnt += (r-l+1)*(nums[left]-nums[l])
            dq.append(left)
            while cnt > k:
                cnt -= nums[dq[0]]-nums[right]
                if dq[0] == right:
                    dq.popleft()
                right -= 1
            result += right-left+1
        return result


if __name__ == "__main__":
    class Test(object):
        def __init__(self, nums, k):
            self.nums = nums
            self.k = k

    tests = [
        Test([5], 0),
        Test([1, 2, 3, 4], 0),
        Test([4, 3, 2, 1], 0),
        Test([3, 1, 2, 1, 2], 2),
        Test([2, 2, 2, 2, 2], 0),
        Test([0, 0, 1, 0, 0], 3),
        Test([1, 5, 2, 6, 3, 7, 4, 8, 5, 9], 20),
        Test([1000000000, 1, 1000000000, 1], 3000000000),
        Test([5, 1], 3),
        Test([1, 3, 2, 2, 5, 1, 7, 2, 3], 5)
    ]

    iterations = 1
    sink = 0
    for iter in xrange(iterations):
        checksum = 0
        sol = Solution()
        for t in tests:
            r = sol.countNonDecreasingSubarrays(t.nums, t.k)
            checksum += int(r)
        sink += checksum
    print(sink)
    # print sink