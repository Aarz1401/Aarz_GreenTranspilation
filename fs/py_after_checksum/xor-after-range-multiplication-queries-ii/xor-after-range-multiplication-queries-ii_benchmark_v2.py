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
    tests = []

    # Test 1
    t = {}
    t['nums'] = [1]
    t['queries'] = [
        [0, 0, 1, 2]
    ]
    tests.append(t)

    # Test 2
    t = {}
    t['nums'] = [5, 4, 3, 2, 1]
    t['queries'] = [
        [0, 4, 1, 3],
        [1, 4, 2, 5],
        [1, 4, 5, 7]
    ]
    tests.append(t)

    # Test 3
    t = {}
    t['nums'] = [0] * 10
    for i in range(10):
        t['nums'][i] = i
    t['queries'] = [
        [1, 7, 2, 11],
        [0, 9, 3, 13],
        [2, 8, 5, 7]
    ]
    tests.append(t)

    # Test 4
    t = {}
    t['nums'] = [0] * 50
    for i in range(50):
        t['nums'][i] = i + 1
    t['queries'] = [
        [0, 49, 7, 19],
        [5, 45, 9, 17],
        [10, 20, 2, 23]
    ]
    tests.append(t)

    # Test 5
    t = {}
    t['nums'] = [0] * 100
    for i in range(100):
        t['nums'][i] = i + 1
    t['queries'] = [
        [0, 99, 11, 29],
        [3, 97, 12, 31],
        [50, 99, 25, 37],
        [1, 50, 5, 41]
    ]
    tests.append(t)

    # Test 6
    t = {}
    t['nums'] = [2] * 37
    t['queries'] = [
        [0, 36, 7, 43],
        [1, 35, 8, 47],
        [3, 20, 4, 53]
    ]
    tests.append(t)

    # Test 7
    t = {}
    t['nums'] = [0] * 64
    for i in range(64):
        t['nums'][i] = (i * i) % 1000
    t['queries'] = [
        [0, 63, 1, 3],
        [5, 60, 16, 97],
        [2, 30, 3, 7],
        [0, 63, 10, 59]
    ]
    tests.append(t)

    # Test 8
    t = {}
    t['nums'] = [1000000006, 1000000006]
    t['queries'] = [
        [0, 1, 2, 5],
        [1, 1, 1, 3]
    ]
    tests.append(t)

    # Test 9
    t = {}
    t['nums'] = [0] * 30
    for i in range(30):
        t['nums'][i] = (i % 7) + 1
    t['queries'] = [
        [0, 29, 6, 13],
        [2, 28, 7, 17],
        [1, 19, 5, 19],
        [10, 10, 3, 23]
    ]
    tests.append(t)

    # Test 10
    t = {}
    t['nums'] = [0] * 200
    for i in range(200):
        t['nums'][i] = ((i * 31 + 7) % 1000) + 1
    t['queries'] = [
        [0, 199, 15, 7],
        [5, 195, 16, 11],
        [20, 180, 20, 17],
        [33, 150, 3, 19],
        [7, 123, 14, 23]
    ]
    tests.append(t)

    iterations = 1
    sink = 0
    for iter in range(iterations):
        checksum = 0
        for test in tests:
            nums = list(test['nums'])
            queries = [list(q) for q in test['queries']]
            sol = Solution()
            checksum += sol.xorAfterQueries(nums, queries)
        sink += checksum
    print(sink)