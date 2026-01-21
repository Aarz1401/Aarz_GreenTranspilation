# Time:  O(nlogs), s is the sum of nums
# Space: O(1)

class Solution(object):
    def splitArray(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        def check(nums, m, s):
            cnt, curr_sum = 1, 0
            for num in nums:
                curr_sum += num
                if curr_sum > s:
                    curr_sum = num
                    cnt += 1
            return cnt <= m

        left, right = max(nums), sum(nums)
        while left <= right:
            mid = left + (right - left) // 2
            if check(nums, m, mid):
                right = mid - 1
            else:
                left = mid + 1
        return left


if __name__ == "__main__":
    tests = [
        {'nums': [7, 2, 5, 10, 8], 'm': 2},
        {'nums': [5], 'm': 1},
        {'nums': [1, 1, 1, 1, 1], 'm': 5},
        {'nums': [1, 2, 3, 4, 5, 6, 7, 8, 9], 'm': 3},
        {'nums': [1000000, 1000000, 1000000, 1000000], 'm': 2},
        {'nums': [2, 3, 1, 2, 4, 3], 'm': 1},
        {'nums': [9, 8, 7, 6], 'm': 4},
        {'nums': [5, 1, 8, 3, 2, 7, 4, 6, 9, 10, 11, 13, 12, 14, 15, 16, 18, 17, 19, 20], 'm': 5},
        {'nums': [0, 0, 0, 0, 0, 10], 'm': 3},
        {'nums': [100, 1, 100, 1, 100, 1, 100, 1, 100, 1], 'm': 3}
    ]

    sink = 0
    sol = Solution()

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += sol.splitArray(t['nums'], t['m'])
        sink += checksum
    print(sink)