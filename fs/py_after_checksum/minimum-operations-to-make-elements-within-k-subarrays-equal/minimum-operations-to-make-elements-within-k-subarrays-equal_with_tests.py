
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
    import time

    # Prepare tests
    tests = []

    # 1) Increasing sequence, x=1 (costs 0), k=5
    tests.append({'nums': [1,2,3,4,5,6,7,8,9,10], 'x': 1, 'k': 5})

    # 2) Random small array, x=2, k=2
    tests.append({'nums': [5,1,9,3,14,2,8,6], 'x': 2, 'k': 2})

    # 3) All equal numbers (costs 0), x=3, k=3
    tests.append({'nums': [7,7,7,7,7,7,7,7,7], 'x': 3, 'k': 3})

    # 4) Mixed negatives and positives, x=3, k=2
    tests.append({'nums': [-10,-5,0,5,10,-3,3,-2,2,-1,1,4], 'x': 3, 'k': 2})

    # 5) x > n (impossible), expect INF-like result
    tests.append({'nums': [1,2,3,4,5], 'x': 6, 'k': 1})

    # 6) k = 0 (no operations), expect 0
    tests.append({'nums': [9,8,7,6,5,4,3], 'x': 3, 'k': 0})

    # 7) Larger array (generated), x=5, k=10
    v = [((i * 37) % 1000) - 500 for i in xrange(600)]
    tests.append({'nums': v, 'x': 5, 'k': 10})

    # 8) Another larger array with different pattern, x=8, k=16
    v = [((i * i + 3 * i + 7) % 100) - 50 for i in xrange(400)]
    tests.append({'nums': v, 'x': 8, 'k': 16})

    # 9) Single element, x=1, k=1 (cost 0)
    tests.append({'nums': [42], 'x': 1, 'k': 1})

    # 10) Exact fill: n=12, x=3, k=4
    tests.append({'nums': [4,1,7,3,2,9,5,8,6,10,11,0], 'x': 3, 'k': 4})

    sol = Solution()

    start_time = time.time()
    checksum = 0
    MASK = (1 << 64) - 1

    iterations = 1
    for it in xrange(iterations):
        for t in tests:
            # Pass a copy of nums to avoid unintended in-place modifications
            res = sol.minOperations(t['nums'][:], t['x'], t['k'])
            # Ensure we get a 64-bit integer even for non-integer or infinite results
            try:
                r = int(res)
            except Exception:
                try:
                    if res == float('inf'):
                        r = MASK
                    elif res == float('-inf'):
                        r = 0
                    else:
                        r = int(res)
                except Exception:
                    r = hash(str(res)) & MASK
            mix = ((r & MASK) + 0x9e3779b97f4a7c15 + (it & MASK) + (len(t['nums']) & MASK)) & MASK
            checksum = (checksum ^ mix) & MASK

    end_time = time.time()
    elapsed_us = int(round((end_time - start_time) * 1000000))

    print "Checksum: " + str(checksum)
    print "Elapsed time (microseconds): " + str(elapsed_us)
