# Time:  O(nlogx + k * n)
# Space: O(n)

from sortedcontainers import SortedList


# two sorted lists, dp
class Solution(object):
    def minOperations(self, nums, x, k):
        """
        :type nums: List[int]
        :type x: int
        :type k: int
        :rtype: int
        """
        class SlidingWindow(object):
            def __init__(self):
                self.left = SortedList()
                self.right = SortedList()
                self.total1 = self.total2 = 0

            def add(self, val):
                if not self.left or val <= self.left[-1]:
                    self.left.add(val)
                    self.total1 += val
                else:
                    self.right.add(val)
                    self.total2 += val
                self.rebalance()

            def remove(self, val):
                if val <= self.left[-1]:
                    self.left.remove(val)
                    self.total1 -= val
                else:
                    self.right.remove(val)
                    self.total2 -= val
                self.rebalance()

            def rebalance(self):
                if len(self.left) < len(self.right):
                    self.total2 -= self.right[0]
                    self.total1 += self.right[0]
                    self.left.add(self.right[0])
                    self.right.pop(0)
                elif len(self.left) > len(self.right)+1:
                    self.total1 -= self.left[-1]
                    self.total2 += self.left[-1]
                    self.right.add(self.left[-1])
                    self.left.pop()

            def median(self):
                return self.left[-1]


        INF = float("inf")
        sw = SlidingWindow()
        cost = [INF]*(len(nums)+1)
        for i in xrange(len(nums)):
            if i-x >= 0:
                sw.remove(nums[i-x])
            sw.add(nums[i])
            if i >= x-1:
                cost[i+1] = (sw.median()*len(sw.left)-sw.total1) + (sw.total2-sw.median()*len(sw.right))
        dp = [0]*(len(nums)+1)
        for i in xrange(k):
            new_dp = [INF]*(len(nums)+1)
            for j in xrange((i+1)*x, len(nums)+1):
                new_dp[j] = min(new_dp[j-1], dp[j-x]+cost[j])
            dp = new_dp
        return dp[-1]


# Time:  O(nlogx + k * n)
# Space: O(n)
import heapq
import collections


# two heaps, dp
class Solution2(object):
    def minOperations(self, nums, x, k):
        """
        :type nums: List[int]
        :type x: int
        :type k: int
        :rtype: int
        """
        class LazyHeap(object):
            def __init__(self, sign):
                self.heap = []
                self.to_remove = collections.defaultdict(int)
                self.cnt = 0
                self.sign = sign

            def push(self, val):
                heapq.heappush(self.heap, self.sign*val)

            def full_remove(self):
                result = []
                for x in self.heap:
                    if x not in self.to_remove:
                        result.append(x)
                        continue
                    self.to_remove[x] -= 1
                    if not self.to_remove[x]:
                        del self.to_remove[x]
                self.heap[:] = result
                heapq.heapify(self.heap)
    
            def remove(self, val):
                self.to_remove[self.sign*val] += 1
                self.cnt += 1
                if self.cnt > len(self.heap)-self.cnt:
                    self.full_remove()
                    self.cnt = 0

            def pop(self):
                self.remove(self.top())

            def top(self):
                while self.heap and self.heap[0] in self.to_remove:
                    self.to_remove[self.heap[0]] -= 1
                    self.cnt -= 1
                    if self.to_remove[self.heap[0]] == 0:
                        del self.to_remove[self.heap[0]]
                    heapq.heappop(self.heap)
                return self.sign*self.heap[0]

            def __len__(self):
                return len(self.heap)-self.cnt


        class SlidingWindow(object):
            def __init__(self):
                self.left = LazyHeap(-1)   # max heap
                self.right = LazyHeap(+1)  # min heap
                self.total1 = self.total2 = 0

            def add(self, val):
                if not self.left or val <= self.left.top():
                    self.left.push(val)
                    self.total1 += val
                else:
                    self.right.push(val)
                    self.total2 += val
                self.rebalance()

            def remove(self, val):
                if val <= self.left.top():
                    self.left.remove(val)
                    self.total1 -= val
                else:
                    self.right.remove(val)
                    self.total2 -= val
                self.rebalance()

            def rebalance(self):
                if len(self.left) < len(self.right):
                    self.total2 -= self.right.top()
                    self.total1 += self.right.top()
                    self.left.push(self.right.top())
                    self.right.pop()
                elif len(self.left) > len(self.right)+1:
                    self.total1 -= self.left.top()
                    self.total2 += self.left.top()
                    self.right.push(self.left.top())
                    self.left.pop()

            def median(self):
                return self.left.top()


        INF = float("inf")
        sw = SlidingWindow()
        cost = [INF]*(len(nums)+1)
        for i in xrange(len(nums)):
            if i-x >= 0:
                sw.remove(nums[i-x])
            sw.add(nums[i])
            if i >= x-1:
                cost[i+1] = (sw.median()*len(sw.left)-sw.total1) + (sw.total2-sw.median()*len(sw.right))
        dp = [0]*(len(nums)+1)
        for i in xrange(k):
            new_dp = [INF]*(len(nums)+1)
            for j in xrange((i+1)*x, len(nums)+1):
                new_dp[j] = min(new_dp[j-1], dp[j-x]+cost[j])
            dp = new_dp
        return dp[-1]


if __name__ == "__main__":
    tests = [
        {'nums': [1, 2, 3, 4, 5], 'x': 1, 'k': 2},
        {'nums': [1, 10, 1, 10, 1, 10], 'x': 2, 'k': 3},
        {'nums': [1, 2, 3, 100, 100, 100, 4, 5], 'x': 3, 'k': 2},
        {'nums': [-5, -1, -3, -2, 100, 101, 102, 103, 0, 0], 'x': 4, 'k': 2},
        {'nums': [7, 7, 7, 1, 2, 3, 7, 7, 7], 'x': 3, 'k': 3},
        {'nums': [1, 100, 100, 100, 100, 1, 1, 1, 1, 1, 1, 50], 'x': 5, 'k': 2},
        {'nums': [0, -1, -2, -3, 4, 5, -6], 'x': 2, 'k': 2},
        {'nums': [10, 10, 10, 20, 20, 19, 30, 31, 32, 5, 5, 5, 100, 100, 100], 'x': 3, 'k': 4},
        {'nums': [1, 2, 100, 2, 1, 50, 50, 50, 50, 50], 'x': 5, 'k': 2},
        {'nums': [8, 1, 9, 2, 7, 3, 6, 4, 5, 0, 5, 0, 100, -100, 100, -100, 50, 51, 49, 50], 'x': 4, 'k': 3},
    ]

    sol = Solution()
    iterations = 1
    sink = None
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            res = sol.minOperations(t['nums'], t['x'], t['k'])
            checksum += int(res)
        sink += checksum
    print(sink)
    # print sink