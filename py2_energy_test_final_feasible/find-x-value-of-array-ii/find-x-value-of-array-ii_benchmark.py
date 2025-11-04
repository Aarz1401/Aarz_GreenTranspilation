# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n * k + q * k * logn)
# Space: O(n * k)

# segment tree
class Solution(object):
    def resultArray(self, nums, k, queries):
        """
        :type nums: List[int]
        :type k: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
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
            x = nums[i]%k
            cnt = [0]*(k+1)
            cnt[x] = 1
            cnt[-1] = x
            return cnt

        def update(x):
            x %= k
            cnt = [0]*(k+1)
            cnt[x] = 1
            cnt[-1] = x
            return cnt
            
        def query(x, y):
            if x is None and y is None:
                return [0]*(k+1)
            if x is None:
                return y
            if y is None:
                return x
            cnt = x[:]
            for i in xrange(k):
                cnt[x[-1]*i%k] += y[i]
            cnt[-1] = x[-1]*y[-1]%k
            return cnt
        
        st = SegmentTree(len(nums), build_fn=build, update_fn=update, query_fn=query)
        result = [0]*len(queries)
        for idx, (i, v, s, x) in enumerate(queries):
            st.update(i, v)
            res = st.query(s, len(nums)-1)
            if x < 0 or x >= len(res):
                result[idx] = 0
            else:
                result[idx] = res[x]
        return result

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([0], 1, [[0, 0, 0, 0]]),
        ([1, 2], 2, [[1, -3, 0, 1]]),
        ([-1, -2, -3], 3, [[0, 4, 1, 0]]),
        ([5, 5, 5], 2, [[2, 6, 2, 2]]),
        ([7], 5, [[0, 7, 0, 5]]),
        ([-1000000000, 1000000000], 3, [[0, -1000000000, 1, 10]]),
        ([1, 0, 1, 0], 2, [[3, 1, 0, -1]]),
        ([2147483647, -2147483648], 7, [[1, 2147483646, 1, 3]]),
        ([2, 2], 4, [[0, 2, 5, 4]]),
        ([1, 2, 3, 4], 3, [[2, 5, 3, 1]]),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.resultArray(*test)
        else:
            sol.resultArray(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.resultArray(*test)
            else:
                result = sol.resultArray(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
