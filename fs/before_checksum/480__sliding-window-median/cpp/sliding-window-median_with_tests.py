# Fallback for sortedcontainers.SortedList if not available
try:
    import sortedcontainers as _sc  # noqa: F401
except Exception:
    import sys
    import types
    from bisect import insort, bisect_left

    class _FallbackSortedList(object):
        def __init__(self, iterable=None):
            self._list = []
            if iterable is not None:
                for x in iterable:
                    insort(self._list, x)

        def add(self, value):
            insort(self._list, value)

        def remove(self, value):
            i = bisect_left(self._list, value)
            if i != len(self._list) and self._list[i] == value:
                self._list.pop(i)
            else:
                raise ValueError('value not found in SortedList')

        def __getitem__(self, idx):
            return self._list[idx]

        def __len__(self):
            return len(self._list)

        def __iter__(self):
            return iter(self._list)

        def __repr__(self):
            return 'SortedList(%r)' % self._list

    mod = types.ModuleType('sortedcontainers')
    mod.SortedList = _FallbackSortedList
    sys.modules['sortedcontainers'] = mod

# Time:  O(nlogk)
# Space: O(k)

from sortedcontainers import SortedList


class Solution(object):
    def medianSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        sl = SortedList(float(nums[i])for i in xrange(k))
        result = [(sl[k//2]+sl[k//2-(1-k%2)])/2]
        for i in xrange(k, len(nums)):
            sl.add(float(nums[i]))
            sl.remove(nums[i-k])
            result.append((sl[k//2]+sl[k//2-(1-k%2)])/2)
        return result


# Time:  O(nlogk)
# Space: O(k)
import collections
import heapq


class Solution2(object):
    def medianSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        def lazy_delete(heap, to_remove, sign):
            while heap and sign*heap[0] in to_remove:
                to_remove[sign*heap[0]] -= 1
                if not to_remove[sign*heap[0]]:
                    del to_remove[sign*heap[0]]
                heapq.heappop(heap)

        def full_delete(heap, to_remove, sign):  # Time: O(k), Space: O(k)
            result = []
            for x in heap:
                if sign*x not in to_remove:
                    result.append(x)
                    continue
                to_remove[sign*x] -= 1
                if not to_remove[sign*x]:
                    del to_remove[sign*x]
            heap[:] = result
            heapq.heapify(heap)

        min_heap, max_heap = [], []
        for i in xrange(k):
            if i%2 == 0:
                heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
            else:
                heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
        to_remove = collections.defaultdict(int)
        for i in xrange(k, len(nums)):
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
            if nums[i-k] > -max_heap[0]:
                heapq.heappush(min_heap, -heapq.heappop(max_heap))
            to_remove[nums[i-k]] += 1
            lazy_delete(max_heap, to_remove, -1)
            lazy_delete(min_heap, to_remove, 1)
            if len(min_heap)+len(max_heap) > 2*k:
                full_delete(max_heap, to_remove, -1)
                full_delete(min_heap, to_remove, 1)
            result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
        return result


# Time:  O(nlogn) due to lazy delete
# Space: O(n)
import collections
import heapq


class Solution3(object):
    def medianSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        def lazy_delete(heap, to_remove, sign):
            while heap and sign*heap[0] in to_remove:
                to_remove[sign*heap[0]] -= 1
                if not to_remove[sign*heap[0]]:
                    del to_remove[sign*heap[0]]
                heapq.heappop(heap)

        min_heap, max_heap = [], []
        for i in xrange(k):
            if i%2 == 0:
                heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
            else:
                heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
        to_remove = collections.defaultdict(int)
        for i in xrange(k, len(nums)):
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
            if nums[i-k] > -max_heap[0]:
                heapq.heappush(min_heap, -heapq.heappop(max_heap))
            to_remove[nums[i-k]] += 1
            lazy_delete(max_heap, to_remove, -1)
            lazy_delete(min_heap, to_remove, 1)
            result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
        return result

if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs
    tests = []

    # 1. Classic mixed example, odd k
    tests.append({'nums': [1, 3, -1, -3, 5, 3, 6, 7], 'k': 3})

    # 2. Single element, k = 1
    tests.append({'nums': [42], 'k': 1})

    # 3. Small ascending, even k
    tests.append({'nums': [1, 2, 3, 4, 5], 'k': 2})

    # 4. Descending, even k
    tests.append({'nums': list(range(10, 0, -1)), 'k': 4})

    # 5. All duplicates, odd k
    tests.append({'nums': [5] * 7, 'k': 5})

    # 6. Negatives and positives, odd k
    tests.append({'nums': [-10, -5, 0, 5, 10, -15, 20, 25, -30], 'k': 5})

    # 7. Extreme integer values, odd k
    INT_MAX = 2147483647
    INT_MIN = -2147483648
    tests.append({'nums': [INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1, 0, 123456789, -123456789], 'k': 3})

    # 8. Empty input with k = 0
    tests.append({'nums': [], 'k': 0})

    # 9. Larger dataset with patterned values, k = 50
    v9 = []
    for i in range(200):
        val = ((i * 37) % 100) - 50 + (i if (i & 1) else (-(i // 2)))
        v9.append(val)
    tests.append({'nums': v9, 'k': 50})

    # 10. Window size equals array size
    v10 = []
    for i in range(30):
        val = (i if (i % 2) else -i) + (3 if (i % 5 == 0) else -3)
        v10.append(val)
    tests.append({'nums': v10, 'k': 30})

    # Benchmark harness
    sol = Solution()
    checksum = 0.0

    start = time.time()
    iterations = 1
    for iter in range(iterations):
        for t in range(len(tests)):
            nums = tests[t]['nums']
            k = tests[t]['k']
            if k <= 0 or k > len(nums):
                res = []
            else:
                res = sol.medianSlidingWindow(nums, k)
            for i in range(len(res)):
                checksum += res[i] * (1.0 + float(i + t))
            checksum += float(len(res) + k)
    end = time.time()

    elapsed_ns = int(round((end - start) * 1e9))
    print "Checksum: %s" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns