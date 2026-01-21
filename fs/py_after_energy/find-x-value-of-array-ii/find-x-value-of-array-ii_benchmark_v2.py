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
    tests = []

    # Test 1
    tests.append({
        'nums': [5],
        'k': 1,
        'queries': [
            [0, 7, 0, 1]
        ]
    })

    # Test 2
    tests.append({
        'nums': [1, 2, 3],
        'k': 2,
        'queries': [
            [1, 5, 0, 0],
            [0, -3, 1, 1],
            [2, 4, 2, 2]
        ]
    })

    # Test 3
    tests.append({
        'nums': [-5, 7, 0, 12, -3],
        'k': 3,
        'queries': [
            [3, -2, 0, 0],
            [1, 9, 2, 1],
            [4, 6, 1, 2],
            [0, -7, 4, 3]
        ]
    })

    # Test 4
    tests.append({
        'nums': [2, 4, 6, 8],
        'k': 4,
        'queries': [
            [2, 5, 0, 0],
            [3, -1, 1, 1],
            [0, 7, 2, 2],
            [1, 3, 3, 4]
        ]
    })

    # Test 5
    tests.append({
        'nums': [1, 1, 1, 1, 1, 1],
        'k': 5,
        'queries': [
            [5, 2, 0, 0],
            [4, 3, 1, 1],
            [3, 4, 2, 2],
            [2, 5, 3, 3],
            [1, 6, 4, 4],
            [0, 7, 5, 5]
        ]
    })

    # Test 6
    tests.append({
        'nums': [-10, 3, -7, 9, 0, 2, 5],
        'k': 7,
        'queries': [
            [6, -2, 0, 0],
            [5, 14, 1, 3],
            [4, -21, 2, 5],
            [3, 7, 3, 7],
            [2, 8, 4, 2]
        ]
    })

    # Test 7
    tests.append({
        'nums': [1000000, -1000000],
        'k': 8,
        'queries': [
            [1, 123456, 0, 0],
            [0, -654321, 1, 4],
            [1, 1, 1, 8]
        ]
    })

    # Test 8
    tests.append({
        'nums': [1, 2, 3, 4, 5, 6, 7, 8],
        'k': 10,
        'queries': [
            [7, 9, 0, 0],
            [6, -5, 2, 5],
            [5, 11, 4, 7],
            [4, -13, 6, 9],
            [3, 17, 7, 10],
            [2, 19, 5, 3]
        ]
    })

    # Test 9
    tests.append({
        'nums': [0,1,2,3,4,5,6,7,8,9],
        'k': 9,
        'queries': [
            [9, -1, 0, 0],
            [8, -2, 1, 1],
            [7, -3, 2, 2],
            [6, -4, 3, 3],
            [5, -5, 4, 4],
            [4, -6, 5, 5],
            [3, -7, 6, 6],
            [2, -8, 7, 7],
            [1, -9, 8, 8],
            [0, -10, 9, 9]
        ]
    })

    # Test 10
    tests.append({
        'nums': [9, -4, 6],
        'k': 6,
        'queries': [
            [2, 1000000007, 0, 0],
            [1, -1000000007, 1, 3],
            [0, 123456789, 2, 6]
        ]
    })

    sink = 0
    iterations = 1000
    for _ in range(iterations):
        #checksum = 0
        for t in range(len(tests)):
            sol = Solution()
            nums = list(tests[t]['nums'])
            k = tests[t]['k']
            queries = [q[:] for q in tests[t]['queries']]
            out = sol.resultArray(nums, k, queries)
            #for v in out:
                #checksum += v
        #sink = checksum
    #print(sink)