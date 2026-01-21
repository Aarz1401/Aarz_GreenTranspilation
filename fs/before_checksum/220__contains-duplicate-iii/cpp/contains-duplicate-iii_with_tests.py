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
    import time

    # Define INT_MAX as in C++
    INT_MAX = 2147483647

    # Prepare 10 diverse test inputs
    tests = []

    # 1) Simple duplicate within k, t = 0
    tests.append(([1, 2, 3, 1], 3, 0))

    # 2) Negative numbers, t > 0 (floor division with negatives)
    tests.append(([-3, -1, -4, -2], 2, 1))

    # 3) Increasing sequence, no duplicates, small k, t = 0
    tests.append((list(range(1, 11)), 1, 0))

    # 4) Near INT_MAX values, small t
    tests.append(([INT_MAX, INT_MAX - 1, INT_MAX - 2, INT_MAX - 3], 1, 1))

    # 5) k = 0 edge case, duplicates exist but should be false
    tests.append(([1, 1], 0, 0))

    # 6) Mixed signs with small k and t > 0
    tests.append(([-10, 5, -6, 7, -8, 9], 2, 3))

    # 7) Duplicate far apart but within large k
    v = []
    for i in range(59):
        v.append(i)
    v.append(0)  # duplicate of first element at the end
    tests.append((v, 100, 0))

    # 8) Repeating pattern, duplicates just beyond k (should be false)
    v = [i % 50 for i in range(200)]
    tests.append((v, 49, 0))

    # 9) Larger increasing array, no duplicates, t = 0 (should be false)
    v = list(range(1000))
    tests.append((v, 100, 0))

    # 10) Arithmetic progression including negatives, t large enough to match neighbors
    v = list(range(-1000, 1001, 10))
    tests.append((v, 5, 10))

    sol = Solution()
    checksum = 0L

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            tc = tests[i]
            res = sol.containsNearbyAlmostDuplicate(tc[0], tc[1], tc[2])
            term = (long(iter + 1) * 1315423911) + long(i)
            checksum += (1 if res else 0) * term
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))
    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us