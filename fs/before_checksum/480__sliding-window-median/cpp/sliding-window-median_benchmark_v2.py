
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
    tests = [
        {'nums': [1, 3, -1, -3, 5, 3, 6, 7], 'k': 3},
        {'nums': [1, 3, -1, -3, 5, 3, 6, 7], 'k': 4},
        {'nums': [5], 'k': 1},
        {'nums': [2, 2, 2, 2, 2, 2], 'k': 3},
        {'nums': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 'k': 5},
        {'nums': [10, 9, 8, 7, 6, 5, 4, 3, 2, 1], 'k': 2},
        {'nums': [0, -1, 1, 0, -2, 2, 0, -3, 3, 0], 'k': 7},
        {'nums': [100, -100, 50, -50, 25, -25, 75, -75, 0, 0], 'k': 4},
        {'nums': [500, -200, 300, -400, 1000, -1000, 750, -750, 250, -250, 125, -125, 60, -60, 30, -30, 15, -15, 7, -7], 'k': 10},
        {'nums': [4, 1, 7, 8, 5, 2, 6, 3, 9], 'k': 9}
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            nums = list(t['nums'])
            k = t['k']
            res = sol.medianSlidingWindow(nums, k)
            checksum += len(res)
            for v in res:
                checksum += int(v)
        sink += checksum
    print(sink)
