# Time:  O(nlogn)
# Space: O(n)

class Solution(object):
    def countRangeSum(self, nums, lower, upper):
        """
        :type nums: List[int]
        :type lower: int
        :type upper: int
        :rtype: int
        """
        def countAndMergeSort(sums, start, end, lower, upper):
            if end - start <= 1:  # The size of range [start, end) less than 2 is always with count 0.
                return 0
            mid = start + (end - start) / 2
            count = countAndMergeSort(sums, start, mid, lower, upper) + \
                    countAndMergeSort(sums, mid, end, lower, upper)
            j, k, r = mid, mid, mid
            tmp = []
            for i in xrange(start, mid):
                # Count the number of range sums that lie in [lower, upper].
                while k < end and sums[k] - sums[i] < lower:
                    k += 1
                while j < end and sums[j] - sums[i] <= upper:
                    j += 1
                count += j - k

                # Merge the two sorted arrays into tmp.
                while r < end and sums[r] < sums[i]:
                    tmp.append(sums[r])
                    r += 1
                tmp.append(sums[i])
            # Copy tmp back to sums.
            sums[start:start+len(tmp)] = tmp
            return count

        sums = [0] * (len(nums) + 1)
        for i in xrange(len(nums)):
            sums[i + 1] = sums[i] + nums[i]
        return countAndMergeSort(sums, 0, len(sums), lower, upper)


# Divide and Conquer solution.
class Solution2(object):
    def countRangeSum(self, nums, lower, upper):
        """
        :type nums: List[int]
        :type lower: int
        :type upper: int
        :rtype: int
        """
        def countAndMergeSort(sums, start, end, lower, upper):
            if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
                return 0

            mid = start + (end - start) / 2
            count = countAndMergeSort(sums, start, mid, lower, upper) + \
                    countAndMergeSort(sums, mid + 1, end, lower, upper)
            j, k, r = mid + 1, mid + 1, mid + 1
            tmp = []
            for i in xrange(start, mid + 1):
                # Count the number of range sums that lie in [lower, upper].
                while k <= end and sums[k] - sums[i] < lower:
                    k += 1
                while j <= end and sums[j] - sums[i] <= upper:
                    j += 1
                count += j - k

                # Merge the two sorted arrays into tmp.
                while r <= end and sums[r] < sums[i]:
                    tmp.append(sums[r])
                    r += 1
                tmp.append(sums[i])

            # Copy tmp back to sums
            sums[start:start+len(tmp)] = tmp
            return count

        sums = [0] * (len(nums) + 1)
        for i in xrange(len(nums)):
            sums[i + 1] = sums[i] + nums[i]
        return countAndMergeSort(sums, 0, len(sums) - 1, lower, upper)


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test cases
    tests = []

    # 1) Empty array
    tests.append({'nums': [], 'lower': 0, 'upper': 0})

    # 2) Single positive element
    tests.append({'nums': [5], 'lower': 5, 'upper': 5})

    # 3) Single negative element
    tests.append({'nums': [-3], 'lower': -3, 'upper': -2})

    # 4) All zeros
    zeros = [0] * 100
    tests.append({'nums': zeros, 'lower': 0, 'upper': 0})

    # 5) Increasing sequence
    inc = [i + 1 for i in xrange(50)]
    tests.append({'nums': inc, 'lower': 10, 'upper': 100})

    # 6) Decreasing negative sequence
    dec = [-(i + 1) for i in xrange(50)]
    tests.append({'nums': dec, 'lower': -100, 'upper': -10})

    # 7) Large magnitude values near int boundaries
    INT_MAX = 2147483647
    big = [INT_MAX, -INT_MAX, INT_MAX, -INT_MAX]
    tests.append({'nums': big, 'lower': -1000000000, 'upper': 1000000000})

    # 8) Deterministic pseudo-random values in [-100, 100], size 200
    rnd = []
    s = 123456789
    for i in xrange(200):
        s = (s * 1664525 + 1013904223) & 0xFFFFFFFF
        val = int((s % 201) - 100)
        rnd.append(val)
    tests.append({'nums': rnd, 'lower': -50, 'upper': 50})

    # 9) Repeating pattern, size 500
    base = [-3, -1, 0, 1, 3, 5, -5]
    pattern = [base[i % 7] for i in xrange(500)]
    tests.append({'nums': pattern, 'lower': -10, 'upper': 10})

    # 10) Sparse spikes with large positives/negatives
    sparse = [0] * 300
    for i in xrange(300):
        if i % 30 == 0:
            sparse[i] += 1000
        if i % 45 == 0:
            sparse[i] -= 1200
    tests.append({'nums': sparse, 'lower': -1500, 'upper': 1500})

    # Benchmark
    sol = Solution()
    iterations = 1000
    checksum = 0L

    start = time.time()
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            t = tests[i]
            res = sol.countRangeSum(t['nums'], t['lower'], t['upper'])
            checksum += (long(res) ^ (long(iter) * 1315423911L + long(i)))
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms