# Time:  O((n + q) * logn)
# Space: O(nlogn)

# prefix sum, greedy, binary lifting
class Solution(object):
    def pathExistenceQueries(self, n, nums, maxDiff, queries):
        """
        :type n: int
        :type nums: List[int]
        :type maxDiff: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def ceil_log2_x(x):
            return (x-1).bit_length() if x-1 >= 0 else -1

        sorted_i = sorted((i for i in xrange(n)), key=lambda i : nums[i])
        i_to_idx = [0]*n
        for idx, i in enumerate(sorted_i):
            i_to_idx[i] = idx
        prefix = [0]*n
        for i in xrange(n-1):
            prefix[i+1] = prefix[i]+int(nums[sorted_i[i+1]]-nums[sorted_i[i]] > maxDiff)
        P = [[n-1]*n for _ in xrange(ceil_log2_x(n-1)+1)]
        left = 0
        for right in xrange(n):
            while nums[sorted_i[right]]-nums[sorted_i[left]] > maxDiff:
                P[0][left] = right-1
                left += 1
        for i in xrange(len(P)-1):
            for j in xrange(n):
                P[i+1][j] = P[i][P[i][j]]
        result = [-1]*len(queries)
        for idx, (i, j) in enumerate(queries):
            if i == j:
                result[idx] = 0
                continue
            if prefix[i_to_idx[i]] != prefix[i_to_idx[j]]:
                continue
            if i_to_idx[i] > i_to_idx[j]:
                i, j = j, i
            curr, l = i_to_idx[i], 0
            for k in reversed(xrange(len(P))):
                if P[k][curr] < i_to_idx[j]:
                    curr = P[k][curr]
                    l += 1<<k
            result[idx] = l+1
        return result


if __name__ == "__main__":
    tests = []
    tests.append((1, [5], 0, [[0, 0]]))
    tests.append((2, [1, 2], 1, [[0, 1], [1, 0]]))
    tests.append((2, [1, 5], 2, [[0, 1], [0, 0], [1, 1]]))
    tests.append((5, [10, 10, 10, 10, 10], 0, [[0, 4], [1, 3], [2, 2]]))
    tests.append((6, [1, 4, 7, 10, 13, 16], 3, [[0, 5], [2, 4], [1, 3]]))
    tests.append((6, [1, 100, 2, 101, 3, 102], 2, [[0, 2], [1, 5], [0, 5]]))
    tests.append((8, [5, 1, 6, 2, 7, 3, 8, 4], 1, [[7, 0], [3, 4], [1, 6]]))
    tests.append((10, [0, 2, 4, 6, 100, 102, 104, 1000, 1002, 1004], 3, [[0, 3], [4, 6], [7, 9], [0, 9], [3, 4]]))
    tests.append((5, [50, 40, 30, 20, 10], 15, [[0, 4], [1, 3], [2, 2]]))
    tests.append((7, [3, 9, 12, 20, 21, 30, 31], 5, [[1, 2], [3, 4], [0, 6], [5, 6]]))

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            n, nums, maxDiff, queries = t
            res = sol.pathExistenceQueries(n, nums, maxDiff, queries)
            for v in res:
                checksum += v
            checksum += len(res)
        sink += checksum
    print(sink)
    # print sink