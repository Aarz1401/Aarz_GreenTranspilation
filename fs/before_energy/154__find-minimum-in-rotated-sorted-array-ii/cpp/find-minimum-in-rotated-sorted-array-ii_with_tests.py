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
    import timeit

    # Prepare 10 diverse test inputs
    tests = []

    # 1. Single element
    tests.append([1])

    # 2. Two elements, sorted
    tests.append([1, 2])

    # 3. Two elements, rotated
    tests.append([2, 1])

    # 4. Multiple elements, rotated, no duplicates
    tests.append([3, 4, 5, 1, 2])

    # 5. Duplicates around pivot
    tests.append([2, 2, 2, 0, 1, 2])

    # 6. All identical
    tests.append([10, 10, 10, 10, 10])

    # 7. Many duplicates with a unique minimum
    tests.append([1, 1, 1, 0, 1])

    # 8. Larger array rotated at pivot 73: [73..99, 0..72]
    v8 = []
    for i in xrange(73, 100):
        v8.append(i)
    for i in xrange(0, 73):
        v8.append(i)
    tests.append(v8)

    # 9. Includes negatives, rotated with duplicates
    tests.append([-1, 0, 1, -3, -2, -1])

    # 10. Already sorted with duplicates
    tests.append([0, 0, 1, 1, 2, 2, 3, 3, 4, 4])

    solver = Solution()

    checksum = 0

    start = timeit.default_timer()

    iterations = 1000
    for _ in xrange(iterations):
        for t in tests:
            checksum += solver.findMin(t)

    end = timeit.default_timer()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: {}".format(checksum)
    print "Elapsed time (ns): {}".format(elapsed_ns)