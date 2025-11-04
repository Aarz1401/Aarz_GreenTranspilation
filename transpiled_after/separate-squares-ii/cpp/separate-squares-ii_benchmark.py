# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn)
# Space: O(n)

# sort, line sweep, segment tree
class Solution(object):
    def separateSquares(self, squares):
        """
        :type squares: List[List[int]]
        :rtype: float
        """
        class SegmentTreeRecu(object):
            def __init__(self, sorted_x):
                self.sorted_x = sorted_x
                n = len(sorted_x)-1
                l = 1<<((n-1).bit_length()+1)
                self.tree = [0]*l
                self.cnt = [0]*l
        
            def update(self, ql, qr, v, l, r, i):  # update [ql, qr) by v, interval [l, r) in sorted_x is covered by i
                if ql >= r or qr <= l:
                    return
                if ql <= l and r <= qr:
                    self.cnt[i] += v
                else:
                    m = l+(r-l)//2
                    self.update(ql, qr, v, l, m, 2*i)
                    self.update(ql, qr, v, m, r, 2*i+1)
                if self.cnt[i] > 0:
                    self.tree[i] = self.sorted_x[r]-self.sorted_x[l]
                else:
                    if r-l == 1:
                        self.tree[i] = 0
                    else:
                        self.tree[i] = self.tree[2*i]+self.tree[2*i+1]
    
        events = []
        x_set = set()
        for x, y, l in squares:
            events.append((y, 1, x, x+l))
            events.append((y+l, -1, x, x+l))
            x_set.add(x)
            x_set.add(x+l)
        events.sort(key=lambda e: e[0])
        sorted_x = sorted(x_set) 
        x_to_idx = {x:i for i, x in enumerate(sorted_x)}
        st = SegmentTreeRecu(sorted_x)
        prev = events[0][0]
        intervals = []
        for y, v, x1, x2 in events:
            if y != prev:
                intervals.append([prev, y, st.tree[1]])
                prev = y
            st.update(x_to_idx[x1], x_to_idx[x2], v, 0, len(sorted_x)-1, 1)
        expect = sum((y2-y1)*curr for y1, y2, curr in intervals)/2.0
        total = 0.0
        for y1, y2, curr in intervals:
            if total+(y2-y1)*curr >= expect:
                break
            total += (y2-y1)*curr
        return y1+(expect-total)/curr

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Single square
        [
            [0, 0, 10]
        ],
        # 2) Two non-overlapping squares horizontally
        [
            [0, 0, 4],
            [10, 0, 4]
        ],
        # 3) Two partially overlapping squares
        [
            [0, 0, 5],
            [3, 0, 5]
        ],
        # 4) Nested squares
        [
            [0, 0, 8],
            [2, 2, 4]
        ],
        # 5) Diagonal staircase of squares
        [
            [0, 0, 2],
            [1, 1, 2],
            [2, 2, 2],
            [3, 3, 2]
        ],
        # 6) Touching edges along x (contiguous union)
        [
            [0, 0, 3],
            [3, 0, 3],
            [6, 0, 3]
        ],
        # 7) Touching edges along y (stacked vertically)
        [
            [0, 0, 3],
            [0, 3, 3],
            [0, 6, 3]
        ],
        # 8) Scattered small squares with varying sizes
        [
            [0, 0, 1],
            [2, 4, 1],
            [4, 2, 1],
            [6, 6, 1],
            [1, 3, 2],
            [5, 1, 2],
            [3, 5, 1],
            [7, 3, 2]
        ],
        # 9) Large coordinates to test numeric stability
        [
            [1000000000, 1000000000, 100000000],
            [1100000000, 1000000050, 50000000],
            [950000000, 1050000000, 120000000]
        ],
        # 10) Dense overlapping grid-like arrangement
        [
            [0, 0, 3], [2, 0, 3], [4, 0, 3],
            [0, 2, 3], [2, 2, 3], [4, 2, 3]
        ],
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.separateSquares(*test)
        else:
            sol.separateSquares(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.separateSquares(*test)
            else:
                result = sol.separateSquares(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()