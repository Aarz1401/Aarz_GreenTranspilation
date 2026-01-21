
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


if __name__ == "__main__":
    import time

    def makeArray(n, base, modval):
        a = [0] * n
        for i in xrange(n):
            a[i] = ((i * base + 17) % modval) + 1
        return a

    tests = []

    # Test 1: Single element, small k, boundary v values
    tc = {}
    tc['nums'] = [42]
    tc['queries'] = [
        [0, 0, 1, 2],
        [0, 0, 1, 1000000006]
    ]
    tests.append(tc)

    # Test 2: Small array with mixed ks
    tc = {}
    tc['nums'] = [1, 2, 3, 4, 5]
    tc['queries'] = [
        [0, 4, 1, 3],
        [1, 3, 2, 5],
        [2, 2, 1, 7],
        [0, 4, 4, 11]
    ]
    tests.append(tc)

    # Test 3: n=100, mixed small/large ks
    tc = {}
    tc['nums'] = makeArray(100, 37, 1000)
    tc['queries'] = [
        [0, 99, 50, 2],
        [10, 90, 60, 3],
        [5, 5, 1000, 1000000006],
        [20, 80, 7, 13],
        [0, 99, 11, 17]
    ]
    tests.append(tc)

    # Test 4: n=200, varied patterns and ks including boundaries
    tc = {}
    tc['nums'] = makeArray(200, 73, 10000)
    tc['queries'] = [
        [0, 199, 2, 5],
        [50, 150, 3, 7],
        [1, 8, 3, 11],
        [20, 180, 4, 13],
        [0, 199, 100, 17],
        [50, 150, 10, 19],
        [0, 199, 5, 23],
        [10, 190, 97, 29]
    ]
    tests.append(tc)

    # Test 5: Empty array (no-op)
    tc = {}
    tc['nums'] = []
    tc['queries'] = []
    tests.append(tc)

    # Test 6: n=32, k at block boundary and beyond
    tc = {}
    tc['nums'] = makeArray(32, 29, 2000)
    tc['queries'] = [
        [0, 31, 6, 7],
        [0, 31, 7, 11],
        [5, 25, 6, 17],
        [10, 10, 1000, 19],
        [3, 29, 6, 23]
    ]
    tests.append(tc)

    # Test 7: n=64, multiple overlapping small ks
    tc = {}
    tc['nums'] = makeArray(64, 17, 5000)
    tc['queries'] = [
        [0, 63, 1, 3],
        [1, 62, 2, 5],
        [2, 60, 4, 7],
        [3, 59, 8, 11],
        [0, 63, 16, 13],
        [5, 55, 3, 97],
        [10, 20, 1, 1000000006],
        [0, 0, 64, 23]
    ]
    tests.append(tc)

    # Test 8: n=120, direct and diff mix, single index updates
    tc = {}
    tc['nums'] = makeArray(120, 31, 1000)
    tc['queries'] = [
        [0, 0, 500, 2],
        [119, 119, 1000, 3],
        [0, 119, 5, 29],
        [10, 110, 25, 37],
        [5, 115, 6, 41],
        [20, 80, 11, 43],
        [50, 60, 100, 47]
    ]
    tests.append(tc)

    # Test 9: n=15, rprime >= n cases (no inverse placement)
    tc = {}
    tc['nums'] = makeArray(15, 7, 100)
    tc['queries'] = [
        [0, 14, 5, 2],
        [0, 10, 5, 3],
        [1, 13, 4, 5],
        [2, 12, 6, 7]
    ]
    tests.append(tc)

    # Test 10: n=256, heavier mix including boundary and large ks
    tc = {}
    tc['nums'] = makeArray(256, 67, 10000)
    tc['queries'] = [
        [0, 255, 17, 2],
        [0, 255, 18, 3],
        [100, 200, 5, 5],
        [50, 220, 9, 7],
        [0, 255, 64, 11],
        [10, 245, 32, 13],
        [123, 123, 1000, 97],
        [0, 255, 1, 1000000006],
        [5, 250, 7, 89],
        [80, 160, 40, 101]
    ]
    tests.append(tc)

    start = time.time()

    sol = Solution()
    checksum = 0

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            nums = list(tests[i]['nums'])
            queries = [list(q) for q in tests[i]['queries']]
            res = sol.xorAfterQueries(nums, queries)
            checksum += (res ^ i)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us
