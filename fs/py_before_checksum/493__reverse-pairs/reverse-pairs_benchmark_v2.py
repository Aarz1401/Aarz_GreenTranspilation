# Time:  O(nlogn)
# Space: O(n)

class Solution(object):
    def reversePairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def merge(nums, start, mid, end):
            r = mid + 1
            tmp = []
            for i in xrange(start, mid + 1):
                while r <= end and nums[i] > nums[r]:
                    tmp.append(nums[r])
                    r += 1
                tmp.append(nums[i])
            nums[start:start+len(tmp)] = tmp

        def countAndMergeSort(nums, start, end):
            if end - start <= 0:
                return 0

            mid = start + (end - start) / 2
            count = countAndMergeSort(nums, start, mid) + countAndMergeSort(nums, mid + 1, end)
            r = mid + 1
            for i in xrange(start, mid + 1):
                while r <= end and nums[i] > nums[r] * 2:
                    r += 1
                count += r - (mid + 1)
            merge(nums, start, mid, end)
            return count

        return countAndMergeSort(nums, 0, len(nums) - 1)

if __name__ == "__main__":
    tests = [
        [1, 3, 2, 3, 1],
        [2, 4, 3, 5, 1],
        [1, 2, 3, 4, 5, 6],
        [6, 5, 4, 3, 2, 1],
        [-5, -2, -1, 0, 1, 2, 3],
        [2000000000, -1000000000, 1000000000, -500000000, 0],
        [-1, -2, -3, -4, -5],
        [1, 10, 2, 9, 3, 8, 4, 7, 5, 6],
        [9, 1, 3, 2, 3, 1, 5, 0, -1, 8],
        [-100000000, 50000000, -25000000, 12500000, -6250000, 3125000, -1562500, 781250, -390625, 195312, -97656, 48828, -24414, 12207, -6103, 3051, -1525, 762, -381, 190, -95, 47, -23, 11, -5, 2, -1, 0, 1, 3]
    ]

    iterations = 1
    sink = 0
    for _ in xrange(iterations):
        checksum = 0
        sol = Solution()
        for t in tests:
            nums = list(t)
            checksum += sol.reversePairs(nums)
        sink += checksum
    print(sink)