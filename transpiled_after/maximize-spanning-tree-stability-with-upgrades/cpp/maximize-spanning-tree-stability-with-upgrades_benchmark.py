# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n + eloge)
# Space: O(n)

# union find, kruskal's algorithm, mst, maximum spanning tree, greedy
class UnionFind(object):  # Time: O(n * alpha(n)), Space: O(n)
    def __init__(self, n):
        self.set = range(n)
        self.rank = [0]*n

    def find_set(self, x):
        stk = []
        while self.set[x] != x:  # path compression
            stk.append(x)
            x = self.set[x]
        while stk:
            self.set[stk.pop()] = x
        return x

    def union_set(self, x, y):
        x, y = self.find_set(x), self.find_set(y)
        if x == y:
            return False
        if self.rank[x] > self.rank[y]:  # union by rank
            x, y = y, x
        self.set[x] = self.set[y]
        if self.rank[x] == self.rank[y]:
            self.rank[y] += 1
        return True


class Solution(object):
    def maxStability(self, n, edges, k):
        """
        :type n: int
        :type edges: List[List[int]]
        :type k: int
        :rtype: int
        """
        uf = UnionFind(n)
        cnt = 0
        result = float("inf")
        for u, v, s, m in edges:
            if not m:
                continue
            if not uf.union_set(u, v):
                return -1
            cnt += 1
            result = min(result, s)
        edges.sort(key=lambda x: -x[2])
        for u, v, s, m in edges:
            if m:
                continue
            if not uf.union_set(u, v):
                continue
            cnt += 1
            if cnt == (n-1)-k:
                result = min(result, s)
            elif cnt == n-1:
                result = min(result, 2*s)
        return result if cnt == n-1 else -1

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Required edges already form a spanning tree
        (4,
         [
             [0, 1, 5, 1], [1, 2, 7, 1], [2, 3, 6, 1],
             [0, 3, 10, 0], [1, 3, 4, 0]
         ],
         0),
        # 2) Required edges contain a cycle -> immediate -1
        (4,
         [
             [0, 1, 3, 1], [1, 2, 4, 1], [2, 0, 5, 1],
             [2, 3, 6, 0]
         ],
         1),
        # 3) No required edges; k = 0; connected via optional edges
        (4,
         [
             [0, 1, 9, 0], [1, 2, 8, 0], [2, 3, 7, 0], [0, 3, 6, 0], [1, 3, 5, 0]
         ],
         0),
        # 4) No required edges; k = 2; both thresholds should be reached
        (5,
         [
             [0, 1, 9, 0], [1, 2, 8, 0], [2, 3, 7, 0], [3, 4, 6, 0],
             [0, 2, 5, 0], [1, 3, 4, 0], [0, 4, 3, 0]
         ],
         2),
        # 5) Disconnected graph -> -1
        (5,
         [
             [0, 1, 5, 0], [1, 2, 5, 0], [3, 4, 5, 0]
         ],
         1),
        # 6) k > n-1; only final 2*s will be used
        (4,
         [
             [0, 1, 8, 0], [1, 2, 7, 0], [2, 3, 6, 0]
         ],
         10),
        # 7) Mix of required and optional edges; k = 1
        (5,
         [
             [0, 1, 6, 1], [1, 2, 9, 1],
             [2, 3, 5, 0], [3, 4, 8, 0], [0, 4, 7, 0], [2, 4, 2, 0]
         ],
         1),
        # 8) Duplicate edge (required and optional); k = 0
        (4,
         [
             [0, 1, 3, 1],
             [0, 1, 10, 0], [1, 2, 4, 0], [2, 3, 6, 0], [0, 3, 5, 0]
         ],
         0),
        # 9) Zero weights involved; doubling zero remains zero
        (3,
         [
             [0, 1, 0, 0], [1, 2, 0, 0], [0, 2, 1, 0]
         ],
         1),
        # 10) Larger small graph with mix of required and optional; k = 0
        (7,
         [
             [0, 1, 5, 1], [1, 2, 7, 1], [2, 3, 6, 1],
             [3, 4, 9, 0], [4, 5, 4, 0], [5, 6, 8, 0], [0, 6, 3, 0], [1, 3, 2, 0]
         ],
         0),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            n, edges, k = test
            sol.maxStability(n, [e[:] for e in edges], k)
        else:
            sol.maxStability(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                n, edges, k = test
                result = sol.maxStability(n, [e[:] for e in edges], k)
            else:
                result = sol.maxStability(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()