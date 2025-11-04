# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (1, [42], 0, [[0, 0]]),
        (2, [1, 100], 1000, [[0, 1], [1, 0], [0, 0], [1, 1]]),
        (3, [3, 1, 2], 1, [[0, 1], [1, 2], [0, 2], [2, 0]]),
        (4, [5, 5, 5, 5], 0, [[0, 3], [2, 1], [0, 0], [3, 2]]),
        (5, [-5, 0, 5, 10, -10], 5, [[0, 4], [4, 2], [1, 3], [2, 2]]),
        (6, [0, 1, 2, 100, 101, 102], 1, [[0, 2], [3, 5], [0, 5], [1, 4]]),
        (5, [7, 7, 10, 10, 13], 0, [[0, 1], [2, 3], [1, 2], [3, 4]]),
        (7, [10, 8, 12, 6, 14, 4, 16], 3, [[0, 6], [1, 3], [2, 4], [5, 0]]),
        (8, [1, 1, 1, 1, 1, 1, 1, 1], 0, [[0, 7], [3, 4], [6, 6], [2, 5]]),
        (9, [0, 5, 0, 5, 0, 5, 0, 5, 0], 4, [[0, 2], [1, 3], [0, 1], [7, 8]]),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.pathExistenceQueries(*test)
        else:
            sol.pathExistenceQueries(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.pathExistenceQueries(*test)
            else:
                result = sol.pathExistenceQueries(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()