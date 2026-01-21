# Time:  O(logn) ~ O(n)
# Space: O(1)

class Solution(object):
    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        left, right = 0, len(nums) - 1
        while left < right:
            mid = left + (right - left) / 2

            if nums[mid] == nums[right]:
                right -= 1
            elif nums[mid] < nums[right]:
                right = mid
            else:
                left = mid + 1

        return nums[left]


class Solution2(object):
    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        left, right = 0, len(nums) - 1
        while left < right and nums[left] >= nums[right]:
            mid = left + (right - left) / 2

            if nums[mid] == nums[left]:
                left += 1
            elif nums[mid] < nums[left]:
                right = mid
            else:
                left = mid + 1

        return nums[left]


if __name__ == "__main__":
    tests = [
        [1],
        [2, 2, 2, 2, 2],
        [3, 4, 5, 1, 2],
        [2, 2, 2, 3, 1, 2],
        [10, 1, 10, 10, 10],
        [1, 2, 3, 4, 5, 6, 7],
        [2, 2, 3, 4, 4, 5, 1, 1, 2],
        [5, 6, 7, 0, 1, 2, 3, 4],
        [4, 4, 4, 5, 6, 7, 0, 1, 2, 2, 3],
        [0, 0, 1, 2, 2, 2, 2, 2, 0]
    ]

    sink = 0
    sol = Solution()

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            r = sol.findMin(t)
        #sink = checksum