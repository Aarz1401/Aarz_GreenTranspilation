# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n)
# Space: O(n)

import collections


# hash table, greedy, kadane's algorithm
class Solution(object):
    def maxSubarraySum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        result = float("-inf")
        curr = mn = mn0 = 0
        mn1 = collections.defaultdict(int)
        for x in nums:
            curr += x
            result = max(result, curr-mn)
            mn1[x] = min(mn1[x], mn0)+x
            mn0 = min(mn0, curr)
            mn = min(mn, mn1[x], mn0)
        return result


# Time:  O(n)
# Space: O(n)
import collections


# hash table, greedy, kadane's algorithm
class Solution2(object):
    def maxSubarraySum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        result = float("-inf")
        curr = mn = mn0 = 0
        mn1 = collections.defaultdict(int)
        for x in nums:
            curr += x
            result = max(result, curr-mn)
            if x < 0:
                mn1[x] = min(mn1[x], mn0)+x
                mn = min(mn, mn1[x])
            mn0 = min(mn0, curr)
            mn = min(mn, mn0)
        return result


# Time:  O(nlogn)
# Space: O(n)
import collections


# segment tree
class Solution_TLE(object):
    def maxSubarraySum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MAX, TOTAL, PREFIX, SUFFIX = range(4)
        # Template:
        # https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/block-placement-queries.py
        class SegmentTree(object):
            def __init__(self, N,
                        build_fn=lambda _: None,
                        query_fn=lambda x, y: y if x is None else x if y is None else max(x, y),
                        update_fn=lambda x: x):
                self.tree = [None]*(1<<((N-1).bit_length()+1))
                self.base = len(self.tree)>>1
                self.query_fn = query_fn
                self.update_fn = update_fn
                for i in xrange(self.base, self.base+N):
                    self.tree[i] = build_fn(i-self.base)
                for i in reversed(xrange(1, self.base)):
                    self.tree[i] = query_fn(self.tree[i<<1], self.tree[(i<<1)+1])

            def update(self, i, h):
                x = self.base+i
                self.tree[x] = self.update_fn(h)
                while x > 1:
                    x >>= 1
                    self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])

            def query(self, L, R):
                L += self.base
                R += self.base
                left = right = None
                while L <= R:
                    if L & 1:
                        left = self.query_fn(left, self.tree[L])
                        L += 1
                    if R & 1 == 0:
                        right = self.query_fn(self.tree[R], right)
                        R -= 1
                    L >>= 1
                    R >>= 1
                return self.query_fn(left, right)
        
        def build(i):
            return [nums[i]]*4
        
        def query(x, y):
            if x is None:
                return y
            if y is None:
                return x
            return [max(x[MAX], y[MAX], x[SUFFIX]+y[PREFIX]),
                    x[TOTAL]+y[TOTAL],
                    max(x[PREFIX], x[TOTAL]+y[PREFIX]),
                    max(y[SUFFIX], x[SUFFIX]+y[TOTAL])]

        mx = max(nums)
        if mx < 0:
            return mx
        mn = min(nums)
        if mn >= 0:
            return sum(nums)
        groups = collections.defaultdict(list)
        for i, x in enumerate(nums):
            groups[x].append(i)
        st = SegmentTree(len(nums), build_fn=build, query_fn=query)
        result = st.tree[1][0]  # st.query(0, len(nums)-1)[0]
        for k, v in groups.iteritems():
            for i in v:
                st.update(i, None)
            result = max(result, st.tree[1][0])  # st.query(0, len(nums)-1)[0]
            for i in v:
                st.update(i, [k]*4)
        return result

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        [1, 2, 3, 4, 5, 6, 7],
        [-1, -2, -3, -4, -5, -6],
        [3, -1, 3, 3, -1, 3, -1, 3],
        [0, 1, 0, 2, 0, 3, 0, -2, 0, 4, 0],
        [1073741823, -1, 2, -3, -1073741823, 4, -5, 6],
        [5],
        [1000000, -1000000, 1000000, -1000000, 1000000, -1000000, 1000000],
        [-5, -1, -5, -1, -5, -1, -5],
        [-2, 1, -3, 4, -1, 2, 1, -5, 4],
        [10, -5, -5, -5, 10, -5, 10, -5, 10],
    ]

    # Warm-up
    sol = Solution_TLE()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxSubarraySum(*test)
        else:
            sol.maxSubarraySum(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution_TLE()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxSubarraySum(*test)
            else:
                result = sol.maxSubarraySum(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()