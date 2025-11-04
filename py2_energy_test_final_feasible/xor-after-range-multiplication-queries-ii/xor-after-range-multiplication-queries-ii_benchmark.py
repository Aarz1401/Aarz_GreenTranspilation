# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(qlogm + (q + n) * sqrt(n))
# Space: O(n * sqrt(n))

import collections


# sqrt decomposition, difference array, fast exponentiation
class Solution(object):
    def xorAfterQueries(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        MOD = 10**9+7
        def inv(x):
            return pow(x, MOD-2, MOD)

        block_size = int(len(nums)**0.5)+1
        diffs = collections.defaultdict(lambda: [1]*len(nums))
        for l, r, k, v in queries:
            if k <= block_size:
                diffs[k][l] = (diffs[k][l]*v)%MOD
                r += k-(r-l)%k
                if r < len(nums):
                    diffs[k][r] = (diffs[k][r]*inv(v))%MOD
            else:
                for i in xrange(l, r+1, k):
                    nums[i] = (nums[i]*v)%MOD
        for k, diff in diffs.iteritems():
            for i in xrange(len(diff)):
                if i-k >= 0:
                    diff[i] = (diff[i]*diff[i-k])%MOD
                nums[i] = (nums[i]*diff[i])%MOD
        return reduce(lambda accu, x: accu^x, nums, 0)

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (
            [5],
            [
                [0, 0, 1, 3]
            ]
        ),

        (
            [1, 2, 3, 4, 5],
            [
                [0, 4, 1, 2],  # small k=1
                [0, 4, 4, 3],  # large k=4
                [1, 3, 2, 5]   # small k=2
            ]
        ),

        (
            [0,1,2,3,4,5,6,7,8,9],
            [
                [0, 3, 2, 7],   # small k=2, rprime < n
                [2, 8, 3, 11],  # small k=3, rprime >= n
                [1, 9, 7, 13]   # large k=7
            ]
        ),

        (
            [2,3,5,7,11,13,17,19],
            [
                [3, 3, 2, 17],          # small k=2, rprime < n
                [0, 7, 4, 1000000006],  # large k=4, v = MOD-1
                [1, 6, 3, 29]           # small k=3, rprime < n
            ]
        ),

        (
            [1,2,3,4,5,6,7,8,9,10,11,12],
            [
                [0, 11, 5, 0],     # large k=5, zero multiplier
                [0, 11, 1, 2],     # small k=1
                [2, 10, 6, 123456] # large k=6
            ]
        ),

        (
            [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16],
            [
                [0, 15, 4, -3],          # small k=4, negative multiplier
                [5, 10, 6, 9],           # large k=6
                [2, 14, 5, 1000000006]   # small k=5, v = MOD-1
            ]
        ),

        (
            [42, 7],
            [
                [0, 1, 2, 3],  # small k=2
                [0, 1, 3, 5]   # large k=3
            ]
        ),

        (
            [3,1,4,1,5,9,2,6,5],
            [
                [0, 8, 4, 2147483647], # small k=4, big v
                [2, 7, 5, 123456789],  # large k=5
                [1, 1, 1, 37]          # small k=1, rprime < n
            ]
        ),

        (
            [0, 0, 0],
            [
                # empty
            ]
        ),

        (
            [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19],
            [
                [0, 19, 1, 999999937], # small k=1
                [5, 15, 5, 77],        # small k=5
                [2, 18, 6, 12345],     # large k=6
                [3, 17, 2, 31]         # small k=2, rprime < n
            ]
        ),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            nums, queries = test
            sol.xorAfterQueries(list(nums), queries)
        else:
            sol.xorAfterQueries(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                nums, queries = test
                result = sol.xorAfterQueries(list(nums), queries)
            else:
                result = sol.xorAfterQueries(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()