
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
                    self.tree[i] = self.query_fn(self.tree[i<<1], self.tree[(i<<1)+1])

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


if __name__ == "__main__":
    import time
    import sys

    # Define 10 diverse test inputs
    tests = []
    tests_capacity = 10  # reserved in C++, no effect in Python

    # 1. All positive
    tests.append([1, 2, 3, 4, 5])

    # 2. All negative
    tests.append([-1, -2, -3, -4])

    # 3. Mixed positives and negatives
    tests.append([3, -2, 5, -1, 6, -3])

    # 4. Large values and extremes
    INT_MAX = 2147483647
    tests.append([INT_MAX, -1, INT_MAX, -2, -1000000000, 999999999])

    # 5. Many zeros
    v5 = [0] * 100
    tests.append(v5)

    # 6. Alternating duplicates to stress mn1
    tests.append([5, -5, 5, -5, 5, -5, 5, -5])

    # 7. Programmatically generated patterned sequence (length 200)
    v7 = []
    for i in xrange(200):
        val = (i * 37) % 201  # range [0, 200]
        val = int(val) - 100  # range [-100, 100]
        if i % 3 == 0:
            val = -val
        v7.append(val)
    tests.append(v7)

    # 8. Monotonic negative to positive crossing
    v8 = list(range(-50, 51))
    tests.append(v8)

    # 9. Single element
    tests.append([42])

    # 10. Empty vector
    tests.append([])

    sol = Solution()
    checksum = 0

    iterations = 1000
    mask = (1 << 64) - 1

    start = time.time()
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            try:
                res = sol.maxSubarraySum(tests[i])
            except Exception:
                res = 0
            if not isinstance(res, (int, long)):
                try:
                    if res != res or res == float("inf") or res == float("-inf"):
                        res = 0
                    else:
                        res = int(res)
                except Exception:
                    res = 0
            addend = ((res & mask) + 0x9e3779b97f4a7c15 + ((iter & mask) << 1) + i) & mask
            checksum = (checksum ^ addend) & mask
            checksum = (((checksum << 7) & mask) | (checksum >> (64 - 7))) & mask
    end = time.time()

    elapsed_ns = int(round((end - start) * 1e9))

    sys.stdout.write("Checksum: %d\n" % checksum)
    sys.stdout.write("Elapsed time (ns): %d\n" % elapsed_ns)
