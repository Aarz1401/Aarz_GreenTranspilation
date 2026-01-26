# Time:  O(n * t)
# Space: O(max(k, t))

import collections


class Solution(object):
    # @param {integer[]} nums
    # @param {integer} k
    # @param {integer} t
    # @return {boolean}
    def containsNearbyAlmostDuplicate(self, nums, k, t):
        if k < 0 or t < 0:
            return False
        window = collections.OrderedDict()
        for n in nums:
            # Make sure window size
            if len(window) > k:
                window.popitem(False)

            bucket = n if not t else n // t
            # At most 2t items.
            for m in (window.get(bucket - 1), window.get(bucket), window.get(bucket + 1)):
                if m is not None and abs(n - m) <= t:
                    return True
            window[bucket] = n
        return False

if __name__ == "__main__":
    tests = [
        {'nums': [1, 2, 3, 1], 'k': 3, 't': 0},
        {'nums': [1, 0, 1, 1], 'k': 1, 't': 2},
        {'nums': [1, 5, 9, 1, 5, 9], 'k': 2, 't': 3},
        {'nums': [-1, -3, -6, -2], 'k': 2, 't': 2},
        {'nums': [1000000000, -1000000000], 'k': 1, 't': 2000000000},
        {'nums': [1, 1], 'k': 0, 't': 0},
        {'nums': [0, 100, 200, 300], 'k': 10, 't': 50},
        {'nums': [-100, -99, -98, -97], 'k': 1, 't': 1},
        {'nums': [2147483647, 2147483646, -2147483647, -2147483647 - 1], 'k': 3, 't': 1},
        {'nums': [-1, 2147483647, -2147483647 - 1, 0, 1], 'k': 1, 't': 0}
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for test in tests:
            v = list(test['nums'])
            r = sol.containsNearbyAlmostDuplicate(v, test['k'], test['t']) 
        #sink = checksum