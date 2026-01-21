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
    import time

    INT_MAX = 2147483647
    INT_MIN = -2147483648

    t1 = []
    t2 = [42]
    t3 = [5] * 20
    t4 = []
    for i in xrange(1, 101):
        t4.append(i)
    t5 = []
    for i in xrange(100, 0, -1):
        t5.append(i)
    t6 = [-5, 3, -2, 7, -1, 0, 4, -3, 2, -4, 8, -6, 6, -8, 5, -7]
    t7 = [0, 0, 0, 0, 0, 1, 0, -1, -1, 2, -2, 3, -3, 4, -4]
    t8 = [INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1, 0, 1, -1, 2, -2, 3, -3]
    t9 = []
    for i in xrange(100):
        t9.append(1000000000 if (i % 2 == 0) else -1000000000)
    t10 = []
    state = 123456789
    for i in xrange(512):
        state = (1664525 * state + 1013904223) & 0xFFFFFFFF
        if state >= 0x80000000:
            val = state - 0x100000000
        else:
            val = state
        t10.append(int(val))

    prototypes = [t1, t2, t3, t4, t5, t6, t7, t8, t9, t10]

    sol = Solution()
    checksum = 0L

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for base in prototypes:
            work = list(base)
            result = sol.reversePairs(work)
            checksum += result
            if work:
                checksum += work[0]

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us