# Time:  O(k * (m + n + k)) ~ O(k * (m + n + k^2))
# Space: O(m + n + k^2)

class Solution(object):
    def maxNumber(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        def get_max_digits(nums, start, end, max_digits):
            max_digits[end] = max_digit(nums, end)
            for i in reversed(xrange(start, end)):
                max_digits[i] = delete_digit(max_digits[i + 1])

        def max_digit(nums, k):
            drop = len(nums) - k
            res = []
            for num in nums:
                while drop and res and res[-1] < num:
                    res.pop()
                    drop -= 1
                res.append(num)
            return res[:k]

        def delete_digit(nums):
            res = list(nums)
            for i in xrange(len(res)):
                if i == len(res) - 1 or res[i] < res[i + 1]:
                    res = res[:i] + res[i+1:]
                    break
            return res

        def merge(a, b):
            return [max(a, b).pop(0) for _ in xrange(len(a)+len(b))]

        m, n = len(nums1), len(nums2)

        max_digits1, max_digits2 = [[] for _ in xrange(k + 1)], [[] for _ in xrange(k + 1)]
        get_max_digits(nums1, max(0, k - n), min(k, m), max_digits1)
        get_max_digits(nums2, max(0, k - m), min(k, n), max_digits2)

        return max(merge(max_digits1[i], max_digits2[k-i]) \
                   for i in xrange(max(0, k - n), min(k, m) + 1))


if __name__ == "__main__":
    sol = Solution()
    tests = [
        {'a': [3, 4, 6, 5], 'b': [9, 1, 2, 5, 8, 3], 'k': 5},
        {'a': [6, 7], 'b': [6, 0, 4], 'k': 5},
        {'a': [3, 9], 'b': [8, 9], 'k': 3},
        {'a': [1, 2, 3, 4, 5], 'b': [5, 4, 3, 2, 1], 'k': 5},
        {'a': [9, 9, 9, 9], 'b': [9, 9, 9], 'k': 6},
        {'a': [1], 'b': [2, 3, 4, 5, 6, 7, 8, 9], 'k': 4},
        {'a': [8, 6, 9], 'b': [1, 7, 5], 'k': 5},
        {'a': [2, 5, 6, 4, 4, 0], 'b': [7, 3, 8, 0, 6, 5, 7, 6, 2], 'k': 15},
        {'a': [5, 2, 1, 9, 0], 'b': [3, 9, 5, 6], 'k': 6},
        {'a': [0, 0, 0, 0, 0, 0], 'b': [0, 0, 0, 0], 'k': 7}
    ]

    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for tc in tests:
            res = sol.maxNumber(tc['a'][:], tc['b'][:], tc['k'])
            s = 0
            for v in res:
                s += v
            checksum += s
        sink += checksum
    print(sink)
    # print sink