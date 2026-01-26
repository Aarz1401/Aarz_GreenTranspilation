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
    tests = [
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [1, 1, 1, 1],
        [2, 1, 3, 4, 4],
        [2, 2, 1, 1, 3, 3],
        [-2, -1, -3, 4, 3],
        [0],
        [1, 0, 1, 3, 2],
        [1000000000, -1000000000, 0, 999999999, -999999999],
        [1, 3, 2, 2, 2]
    ]

    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        sol = Solution()
        for t in tests:
            checksum += sol.maxChunksToSorted(t)
        sink += checksum
    print(sink)
    # print sink