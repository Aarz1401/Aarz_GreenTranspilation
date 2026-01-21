# Time:  O(nlogn + nlogw), n = len(nums), w = max(nums)-min(nums)
# Space: O(1)

class Solution(object):
    def smallestDistancePair(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        # Sliding window solution
        def possible(guess, nums, k):
            count, left = 0, 0
            for right, num in enumerate(nums):
                while num-nums[left] > guess:
                    left += 1
                count += right-left
            return count >= k

        nums.sort()
        left, right = 0, nums[-1]-nums[0]+1
        while left < right:
            mid = left + (right-left)/2
            if possible(mid, nums, k):
                right = mid
            else:
                left = mid+1
        return left

if __name__ == "__main__":
    tests = [
        {'nums': [1, 100], 'k': 1},
        {'nums': [1, 3, 1], 'k': 1},
        {'nums': [1, 2, 3, 4, 5], 'k': 4},
        {'nums': [10, 10, 10, 10], 'k': 6},
        {'nums': [1, 6, 1, 2, 5, 9], 'k': 7},
        {'nums': [0, 0, 0, 0, 0, 0], 'k': 10},
        {'nums': [0, 1000000], 'k': 1},
        {'nums': [1, 1, 2, 2, 3, 3, 4, 4], 'k': 16},
        {'nums': [1, 3, 6, 10, 15, 21, 28, 36], 'k': 20},
        {'nums': [4, 1, 4, 2, 8, 5, 7, 2, 3], 'k': 12}
    ]

    solution = Solution()

    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            nums = list(t['nums'])
            result = solution.smallestDistancePair(nums, t['k'])
            checksum += result
        sink += checksum
    print(sink)