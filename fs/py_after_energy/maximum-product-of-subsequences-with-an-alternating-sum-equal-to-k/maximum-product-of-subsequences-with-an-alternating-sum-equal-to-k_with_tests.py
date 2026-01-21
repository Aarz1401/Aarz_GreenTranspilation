# Time:  O(n * k * l), l = limits
# Space: O(n * k * l)

import collections


# dp
class Solution(object):
    def maxProduct(self, nums, k, limit):
        """
        :type nums: List[int]
        :type k: int
        :type limit: int
        :rtype: int
        """
        total = sum(nums)
        if k > total or k < -total:  # optimized to speed up
            return -1
        dp = collections.defaultdict(set)
        for x in nums:
            new_dp = collections.defaultdict(set, {k:set(v) for k, v in dp.iteritems()})
            new_dp[(1, x)].add(min(x, limit+1))
            for (p, total), products in dp.iteritems():
                new_state = (p^1, total+(x if p == 0 else -x))
                for v in products:
                    new_dp[new_state].add(min(v*x, limit+1))
            dp = new_dp
        result = -1
        for (p, total), products in dp.iteritems():
            if total != k:
                continue
            for v in products:
                if v <= limit:
                    result = max(result, v)
        return result


if __name__ == "__main__":
    from time import time

    # Define 10 diverse test inputs
    numsList = [
        [1, 2, 3, 4],                # Case 1: simple positives
        [5],                         # Case 2: single element
        [0, 0, 5],                   # Case 3: includes zeros
        [5, -2, 7, -3],              # Case 4: includes negatives
        [2, 2, 2, 2, 2],             # Case 5: duplicates
        [3, 3, 3, 3],                # Case 6: duplicates length 4
        [1000, 1000],                # Case 7: large values to trigger cap
        [9, 8, 7],                   # Case 8: small with known alt sum 1
        [0, 5, 0, 5],                # Case 9: zeros interleaved
        [1, 1, 2, 3, 5, 8, 13, 21]   # Case 10: Fibonacci-like
    ]

    ks = [
        3,    # Case 1 target (subseq [2,3,4] -> 2-3+4=3)
        5,    # Case 2 target ([5])
        5,    # Case 3 target ([5] or [0,0,5])
        7,    # Case 4 target ([7] or [5,-2])
        2,    # Case 5 target (odd-length subseqs or single)
        0,    # Case 6 target (even-length subseqs)
        0,    # Case 7 target ([1000,1000] -> 0)
        1,    # Case 8 target ([9,8] -> 1)
        0,    # Case 9 target ([0] subseqs)
        6     # Case 10 target ([3,5,8] -> 3-5+8=6)
    ]

    limits = [
        100,       # Case 1 limit
        10,        # Case 2 limit
        1000,      # Case 3 limit
        1000,      # Case 4 limit
        100,       # Case 5 limit
        100,       # Case 6 limit
        500000,    # Case 7 limit to trigger cap
        1000000,   # Case 8 limit
        10,        # Case 9 limit
        1000       # Case 10 limit
    ]

    sol = Solution()
    checksum = 0

    start = time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(10):
            res = sol.maxProduct(numsList[i], ks[i], limits[i])
            checksum += res

    end = time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (microseconds): %d" % (elapsed_us,)