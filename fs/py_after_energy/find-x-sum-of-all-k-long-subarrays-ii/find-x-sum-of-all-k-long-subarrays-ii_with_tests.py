# Time:  O(nlogn)
# Space: O(n)

from sortedcontainers import SortedList
import collections


# freq table, sorted list, two pointers, sliding window
class Solution(object):
    def findXSum(self, nums, k, x):
        """
        :type nums: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        def update(v, d, curr):
            if d == 1:
                sl.add((-cnt[v], -v))
            if sl.index((-cnt[v], -v)) < x:
                curr += d*cnt[v]*v
                if x < len(sl):
                    nc, nv = sl[x]
                    curr -= d*nc*nv
            if d != 1:
                sl.remove((-cnt[v], -v))
            return curr

        sl = SortedList()
        cnt = collections.defaultdict(int)
        result = []
        curr = 0
        for i, v in enumerate(nums):
            if v in cnt:
                curr = update(v, -1, curr)
            cnt[v] += 1
            curr = update(v, +1, curr)
            if i < k-1:
                continue
            result.append(curr)
            curr = update(nums[i-(k-1)], -1, curr)
            cnt[nums[i-(k-1)]] -= 1
            if cnt[nums[i-(k-1)]]:
                curr = update(nums[i-(k-1)], +1, curr)
            else:
                del cnt[nums[i-(k-1)]]
        return result


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test cases
    tests = []

    # 1) Mixed small array
    tests.append((
        [1, 2, 3, 2, 2, 3, 1, 4, 4, 4, 5, 5, 6, 1, 2, 3, 7, 7, 7, 8],
        5,
        3
    ))

    # 2) All same values
    v = [42] * 200
    tests.append((v, 50, 1))

    # 3) Strictly increasing sequence
    v = [0] * 500
    for i in xrange(500):
        v[i] = i + 1
    tests.append((v, 100, 10))

    # 4) Negative and positive mix with modular pattern
    v = [0] * 256
    for i in xrange(256):
        v[i] = (i * 7 % 101) - 50
    tests.append((v, 60, 8))

    # 5) k = 1, small ranges
    v = [0] * 100
    for i in xrange(100):
        v[i] = (i * 31 + 7) % 9 - 4
    tests.append((v, 1, 1))

    # 6) k = n, repeated pattern
    v = [0] * 150
    for i in xrange(150):
        v[i] = i % 20
    tests.append((v, 150, 20))

    # 7) x = 0
    v = [0] * 80
    for i in xrange(80):
        v[i] = (i % 5) - 2
    tests.append((v, 10, 0))

    # 8) Many distinct values in a higher range
    v = [0] * 300
    for i in xrange(300):
        v[i] = 1000 + i
    tests.append((v, 30, 15))

    # 9) k > n (should result in empty output)
    v = [0] * 30
    for i in xrange(30):
        v[i] = (i * 97 + 12345) % 1000 - 500
    tests.append((v, 100, 10))

    # 10) Large magnitude values alternating sign
    INT_MAX = 2147483647
    INT_MIN = -2147483648
    v = [0] * 200
    for i in xrange(200):
        if i % 2 == 0:
            v[i] = INT_MAX // 4 - i
        else:
            v[i] = INT_MIN // 4 + i
    tests.append((v, 50, 25))

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            nums, k, x = tests[i]
            res = sol.findXSum(nums, k, x)

            for j in xrange(len(res)):
                checksum += res[j] + 1315423911 + ((iter + 1) * (i + 1) * (j + 1))
            checksum += len(res) * (i + 1) + iter

    end = time.time()
    elapsed_ns = long((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed(ns): %d" % elapsed_ns