# Time:  O(n)
# Space: O(k)

from collections import deque


class Solution(object):
    def maxSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        result, dq = [], deque()
        for i in xrange(len(nums)):
            if dq and i-dq[0] == k:
                dq.popleft()
            while dq and nums[dq[-1]] <= nums[i]:
                dq.pop()
            dq.append(i)
            if i >= k-1:
                result.append(nums[dq[0]])
        return result


if __name__ == "__main__":
    tests = [
        {'nums': [1], 'k': 1},
        {'nums': [4, -1, 7, 7, 5], 'k': 1},
        {'nums': [1, 3, 2, 5, 4], 'k': 5},
        {'nums': [1, 2, 3, 4, 5, 6], 'k': 3},
        {'nums': [6, 5, 4, 3, 2, 1], 'k': 2},
        {'nums': [2, 2, 2, 2, 2], 'k': 3},
        {'nums': [-5, -2, -3, -1, -4], 'k': 2},
        {'nums': [1000000000, 500000000, 1000000000, -1000000000, 0], 'k': 3},
        {'nums': [9, 9, 1, 3, 7, 2, 6, 5], 'k': 4},
        {'nums': [1, 3, -1, -3, 5, 3, 6, 7, 0, 2, 9, -8, 4, 4, 10], 'k': 5}
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            out = sol.maxSlidingWindow(t['nums'][:], t['k'])
            for v in out:
                checksum ^= v
        sink += checksum
    print(sink)

    # print sink