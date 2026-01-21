
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
            result[idx] = st.query(s, len(nums)-1)[x]
        return result

if __name__ == "__main__":
    import time
    import random

    # Assume buildTests() and Solution are defined in the original Python2 solution environment

    def buildTests():
        # Deterministic small test
        yield {
            'nums': [1, 2, 3, 4],
            'k': 3,
            'queries': [
                (1, 5, 0, 0),
                (2, 6, 1, 2),
                (0, 7, 2, 1),
                (3, 9, 0, 2),
            ],
        }

        # Tuple-style test
        yield ([2, 3], 5, [
            (0, 4, 0, 2),
            (1, 7, 0, 3),
            (0, 1, 1, 1),
        ])

        # Edge case k=1
        yield {
            'nums': [0],
            'k': 1,
            'queries': [
                (0, 0, 0, 0),
                (0, 5, 0, 0),
                (0, 7, 0, 0),
            ],
        }

        # Randomized small cases
        random.seed(0xC0FFEE)
        for n in [5, 8, 12]:
            k = random.randint(2, 6)
            nums = [random.randint(0, 20) for _ in xrange(n)]
            q = random.randint(5, 15)
            queries = []
            for _ in xrange(q):
                i = random.randint(0, n - 1)
                v = random.randint(0, 20)
                s = random.randint(0, n - 1)
                x = random.randint(0, k - 1)
                queries.append((i, v, s, x))
            yield {'nums': nums, 'k': k, 'queries': queries}

        # Another deterministic mixed case
        yield {
            'nums': [7, 0, 5],
            'k': 4,
            'queries': [
                (2, 3, 0, 1),
                (1, 9, 1, 2),
                (0, 8, 0, 0),
                (1, 2, 2, 3),
            ],
        }

    def _extract_field(tc, name):
        # Attribute-style access
        if hasattr(tc, name):
            return getattr(tc, name)
        # Dict-style access
        if isinstance(tc, dict) and name in tc:
            return tc[name]
        # Tuple/list-style access
        idx_map = {'nums': 0, 'k': 1, 'queries': 2}
        if hasattr(tc, '__getitem__') and name in idx_map:
            idx = idx_map[name]
            try:
                return tc[idx]
            except Exception:
                pass
        raise ValueError("Cannot extract field '%s' from test case: %r" % (name, tc))

    tests = list(buildTests())
    solver = Solution()

    start = time.time()

    checksum = 0
    iterations = 1000

    for _ in xrange(iterations):
        for tc in tests:
            nums = _extract_field(tc, 'nums')
            k = _extract_field(tc, 'k')
            queries = _extract_field(tc, 'queries')
            res = solver.resultArray(nums, k, queries)
            for v in res:
                checksum += int(v)

    end = time.time()
    elapsed_us = int(round((end - start) * 1e6))

    print "Checksum: %d" % checksum
    print "Time (microseconds): %d" % elapsed_us
