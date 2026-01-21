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
    import time

    tests = [
        {'nums1': [3, 4, 6, 5], 'nums2': [9, 1, 2, 5, 8, 3], 'k': 5},
        {'nums1': [6, 7], 'nums2': [6, 0, 4], 'k': 5},
        {'nums1': [], 'nums2': [1, 2, 3, 4, 5], 'k': 3},
        {'nums1': [9, 8, 7], 'nums2': [], 'k': 2},
        {'nums1': [1, 1, 1], 'nums2': [1, 1], 'k': 0},
        {'nums1': [5, 9, 1, 3, 7, 2], 'nums2': [3, 9, 5, 2, 1, 8, 6], 'k': 13},
        {'nums1': [2, 5, 6, 4, 4, 0], 'nums2': [7, 3, 8, 0, 6, 5, 7, 6, 2], 'k': 15},
        {'nums1': [0, 1, 2, 3, 4, 5, 6, 7, 8, 9], 'nums2': [9, 8, 7, 6, 5, 4, 3, 2, 1, 0], 'k': 10},
        {'nums1': [0, 0, 0, 0], 'nums2': [0, 0, 0], 'k': 6},
        {'nums1': [9, 9, 9, 1], 'nums2': [9, 9, 8], 'k': 5},
    ]

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for tci in xrange(len(tests)):
            a = list(tests[tci]['nums1'])
            b = list(tests[tci]['nums2'])
            res = sol.maxNumber(a, b, tests[tci]['k'])
            checksum = (checksum + len(res) + iter + tci) & mask
            for r in xrange(len(res)):
                term = ((res[r] + 3) * (r + 11 + tci) + (iter + 1)) & mask
                checksum ^= term
                checksum &= mask
                mix = ((checksum << 7) ^ (checksum >> 3)) & mask
                checksum = (checksum + mix) & mask
    end = time.time()

    elapsed_ms = (end - start) * 1000.0
    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %.6f" % elapsed_ms