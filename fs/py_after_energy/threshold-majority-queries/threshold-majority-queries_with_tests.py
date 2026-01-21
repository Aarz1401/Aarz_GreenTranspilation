import sys
import types
import bisect

# Provide a minimal stub for sortedcontainers.SortedList if the real package isn't available
if 'sortedcontainers' not in sys.modules:
    mod = types.ModuleType('sortedcontainers')

    class SortedList(object):
        def __init__(self, iterable=None):
            self._list = sorted(iterable) if iterable else []
        def add(self, value):
            bisect.insort_left(self._list, value)
        def remove(self, value):
            i = bisect.bisect_left(self._list, value)
            if i == len(self._list) or self._list[i] != value:
                raise ValueError('value not found in SortedList')
            self._list.pop(i)
        def __len__(self):
            return len(self._list)
        def __getitem__(self, idx):
            return self._list[idx]
        def __iter__(self):
            return iter(self._list)

    mod.SortedList = SortedList
    sys.modules['sortedcontainers'] = mod

# Time:  O(nlogn + qlogq + (n + q) * sqrt(n) + q * n)
# Space: O(n + q)

# sort, coordinate compression, mo's algorithm
class Solution(object):
    def subarrayMajority(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # reference: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
        def mo_s_algorithm():  # Time: O(QlogQ + (N + Q) * sqrt(N) + Q * N)
            def add(i):  # Time: O(F) = O(1)
                idx = num_to_idx[nums[i]]
                if cnt[idx]:
                    cnt2[cnt[idx]] -= 1
                cnt[idx] += 1
                cnt2[cnt[idx]] += 1
                max_freq[0] = max(max_freq[0], cnt[idx])

            def remove(i):  # Time: O(F) = O(1)
                idx = num_to_idx[nums[i]]
                cnt2[cnt[idx]] -= 1
                if not cnt2[max_freq[0]]:
                    max_freq[0] -= 1
                cnt[idx] -= 1
                if cnt[idx]:
                    cnt2[cnt[idx]] += 1

            def get_ans(t):  # Time: O(A) = O(N)
                if max_freq[0] < t:
                    return -1
                i = next(i for i in xrange(len(cnt)) if cnt[i] == max_freq[0])
                return sorted_nums[i]

            cnt = [0]*len(num_to_idx)
            cnt2 = [0]*(len(nums)+1)
            max_freq = [0]
            result = [-1]*len(queries)
            block_size = int(len(nums)**0.5)+1  # O(S) = O(sqrt(N))
            idxs = range(len(queries))
            idxs.sort(key=lambda x: (queries[x][0]//block_size, queries[x][1] if (queries[x][0]//block_size)&1 else -queries[x][1]))  # Time: O(QlogQ)
            left, right = 0, -1
            for i in idxs:  # Time: O((N / S) * N * F + S * Q * F + Q * A) = O((N + Q) * sqrt(N) + Q * N), O(S) = O(sqrt(N)), O(F) = O(logN), O(A) = O(1)
                l, r, t = queries[i]
                while left > l:
                    left -= 1
                    add(left)
                while right < r:
                    right += 1
                    add(right)
                while left < l:
                    remove(left)
                    left += 1
                while right > r:
                    remove(right)
                    right -= 1
                result[i] = get_ans(t)
            return result

        sorted_nums = sorted(set(nums))
        num_to_idx = {x:i for i, x in enumerate(sorted_nums)}
        return mo_s_algorithm()


# Time:  O(nlogn + qlogq + (n + q) * sqrt(n) * logn)
# Space: O(n + q)
from sortedcontainers import SortedList


# sort, coordinate compression, mo's algorithm, sorted list
class Solution_TLE(object):
    def subarrayMajority(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # reference: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
        def mo_s_algorithm():  # Time: O(QlogQ + (N + Q) * sqrt(N) * logN)
            def add(i):  # Time: O(F) = O(logN)
                idx = num_to_idx[nums[i]]
                if cnt[idx]:
                    lookup[cnt[idx]].remove(nums[i])
                cnt[idx] += 1
                lookup[cnt[idx]].add(nums[i])
                max_freq[0] = max(max_freq[0], cnt[idx])

            def remove(i):  # Time: O(F) = O(logN)
                idx = num_to_idx[nums[i]]
                lookup[cnt[idx]].remove(nums[i])
                if not lookup[max_freq[0]]:
                    max_freq[0] -= 1
                cnt[idx] -= 1
                if cnt[idx]:
                    lookup[cnt[idx]].add(nums[i])

            def get_ans(t):  # Time: O(A) = O(logN)
                return lookup[max_freq[0]][0] if max_freq[0] >= t else -1

            cnt = [0]*len(num_to_idx)
            lookup = [SortedList() for _ in xrange(len(nums)+1)]
            max_freq = [0]
            result = [-1]*len(queries)
            block_size = int(len(nums)**0.5)+1  # O(S) = O(sqrt(N))
            idxs = range(len(queries))
            idxs.sort(key=lambda x: (queries[x][0]//block_size, queries[x][1] if (queries[x][0]//block_size)&1 else -queries[x][1]))  # Time: O(QlogQ)
            left, right = 0, -1
            for i in idxs:  # Time: O((N / S) * N * F + S * Q * F + Q * A) = O((N + Q) * sqrt(N) * logN), O(S) = O(sqrt(N)), O(F) = O(logN), O(A) = O(1)
                l, r, t = queries[i]
                while left > l:
                    left -= 1
                    add(left)
                while right < r:
                    right += 1
                    add(right)
                while left < l:
                    remove(left)
                    left += 1
                while right > r:
                    remove(right)
                    right -= 1
                result[i] = get_ans(t)
            return result

        num_to_idx = {x:i for i, x in enumerate(sorted(set(nums)))}
        return mo_s_algorithm()


if __name__ == "__main__":
    import time

    def genQueries(n, q, seed):
        x = [seed & 0xFFFFFFFF]
        def nxt():
            t = x[0]
            t ^= ((t << 13) & 0xFFFFFFFF)
            t ^= (t >> 17)
            t ^= ((t << 5) & 0xFFFFFFFF)
            x[0] = t & 0xFFFFFFFF
            return x[0]
        res = []
        for _ in range(q):
            l = nxt() % n
            r = nxt() % n
            if l > r:
                l, r = r, l
            length = r - l + 1
            thr = (nxt() % length) + 1
            res.append([l, r, thr])
        return res

    tests = []

    # Test 1: All equal elements
    tc = {}
    tc['nums'] = [1, 1, 1, 1]
    tc['queries'] = [
        [0, 3, 1],
        [0, 3, 4],
        [1, 2, 2],
        [2, 3, 3]
    ]
    tests.append(tc)

    # Test 2: All distinct
    tc = {}
    tc['nums'] = [i for i in range(1, 11)]
    tc['queries'] = [
        [0, 9, 1],
        [0, 9, 2],
        [3, 7, 1],
        [2, 2, 1],
        [5, 9, 3]
    ]
    tests.append(tc)

    # Test 3: Alternating two values
    tc = {}
    tc['nums'] = [2 if (i % 2 == 0) else 3 for i in range(20)]
    tc['queries'] = [
        [0, 19, 6],
        [0, 19, 11],
        [2, 10, 3],
        [5, 15, 4],
        [0, 1, 1],
        [0, 0, 1]
    ]
    tests.append(tc)

    # Test 4: Negative values and mixed frequencies
    tc = {}
    tc['nums'] = [-5, -5, -5, -1, -1, 0, 0, 0, 0, 10, -5]
    tc['queries'] = [
        [0, 10, 3],
        [3, 9, 3],
        [5, 8, 2],
        [0, 4, 3],
        [0, 10, 6],
        [10, 10, 1],
        [1, 1, 2]
    ]
    tests.append(tc)

    # Test 5: Generated pattern, size 100
    tc = {}
    tc['nums'] = [((i * 17 + 13) % 25) - 12 for i in range(100)]
    tc['queries'] = genQueries(100, 50, 12345)
    tests.append(tc)

    # Test 6: Repeated structural pattern, size 120
    tc = {}
    nums = [0] * 120
    for i in range(120):
        if i % 6 == 0:
            nums[i] = 5
        elif i % 3 == 0:
            nums[i] = 3
        elif i % 2 == 0:
            nums[i] = 2
        else:
            nums[i] = 1
    tc['nums'] = nums
    tc['queries'] = genQueries(120, 60, 54321)
    tests.append(tc)

    # Test 7: Skewed distribution with heavy majority
    tc = {}
    nums = [7] * 150
    for i in range(150):
        if i % 10 == 0:
            nums[i] = i
        if i % 7 == 3:
            nums[i] = 3
    tc['nums'] = nums
    tc['queries'] = genQueries(150, 70, 99991)
    tests.append(tc)

    # Test 8: Larger mixed values
    tc = {}
    tc['nums'] = [((i * 37) % 100) - 50 for i in range(250)]
    tc['queries'] = genQueries(250, 120, 424242)
    tests.append(tc)

    # Test 9: Sorted ascending
    tc = {}
    tc['nums'] = [i for i in range(60)]
    tc['queries'] = genQueries(60, 30, 777)
    tests.append(tc)

    # Test 10: Sorted descending
    tc = {}
    tc['nums'] = [60 - i for i in range(60)]
    tc['queries'] = genQueries(60, 30, 888)
    tests.append(tc)

    start = time.time()

    checksum = 0
    MOD64 = (1 << 64) - 1

    iterations = 1000
    for iter in range(iterations):
        solver = Solution()
        for ti, tc in enumerate(tests):
            ans = solver.subarrayMajority(tc['nums'], tc['queries'])
            for i, a in enumerate(ans):
                v = a & MOD64
                term = (v * 1315423911 + (ti * 104729 + i)) & MOD64
                checksum = (checksum + term) & MOD64

    elapsed_ns = int((time.time() - start) * 1e9)

    print "Checksum: %d" % (checksum & MOD64)
    print "Elapsed(ns): %d" % elapsed_ns