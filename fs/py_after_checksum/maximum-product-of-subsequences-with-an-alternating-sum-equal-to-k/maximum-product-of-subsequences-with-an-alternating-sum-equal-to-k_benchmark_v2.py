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
    tests = [
        {'nums': [1, 2, 3], 'k': 1, 'limit': 10},
        {'nums': [3, 1, 4, 2], 'k': 4, 'limit': 100},
        {'nums': [0, 0, 5], 'k': 0, 'limit': 0},
        {'nums': [2, 2, 2, 2], 'k': 0, 'limit': 10},
        {'nums': [6, 2, 3], 'k': 4, 'limit': 20},
        {'nums': [7], 'k': 7, 'limit': 6},
        {'nums': [5, 1, 2, 3], 'k': 6, 'limit': 10},
        {'nums': [1, 0, 2, 0], 'k': 1, 'limit': 5},
        {'nums': [10, 5, 1], 'k': 5, 'limit': 50},
        {'nums': [1, 2], 'k': 5, 'limit': 100}
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            arr = list(t['nums'])
            res = sol.maxProduct(arr, t['k'], t['limit'])
            checksum += res
        sink += checksum
    print(sink)