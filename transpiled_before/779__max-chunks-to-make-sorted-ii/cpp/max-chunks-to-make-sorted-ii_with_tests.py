# Time:  O(n)
# Space: O(n)

# mono stack solution
class Solution(object):
    def maxChunksToSorted(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        result, increasing_stk = 0, []
        for num in arr:
            max_num = num if not increasing_stk else max(increasing_stk[-1], num)
            while increasing_stk and increasing_stk[-1] > num:
                increasing_stk.pop()
            increasing_stk.append(max_num)
        return len(increasing_stk)


# Time:  O(nlogn)
# Space: O(n)
class Solution2(object):
    def maxChunksToSorted(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        def compare(i1, i2):
            return arr[i1]-arr[i2] if arr[i1] != arr[i2] else i1-i2

        idxs = [i for i in xrange(len(arr))]
        result, max_i = 0, 0
        for i, v in enumerate(sorted(idxs, cmp=compare)):
            max_i = max(max_i, v)
            if max_i == i:
                result += 1
        return result


if __name__ == "__main__":
    # Test cases
    tests = []
    tests.append([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    tests.append([9, 8, 7, 6, 5, 4, 3, 2, 1, 0])
    tests.append([2, 1, 3, 4, 4, 0, 0, 2])
    tests.append([7, 7, 7, 7, 7])
    tests.append([2, 0, 1, 4, 3, 6, 5, 8, 7])
    tests.append([1000000, 2000000, 3000000, 4000000])
    tests.append([-1, -3, -2, 0, -4, 5])
    tests.append([1, 2, 2, 3, 3, 0, 4, 4])
    tests.append([42])
    tests.append([])

    # Benchmark harness
    sol = Solution()
    checksum = 0

    import time
    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for i in xrange(len(tests)):
            result = sol.maxChunksToSorted(tests[i])
            checksum += result * (i + 1)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us