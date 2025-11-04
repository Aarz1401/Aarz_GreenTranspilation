# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n)
# Space: O(n)

# flood fill, bfs, counting sort, greedy
"""
n = 11
edges = [[0,1],[1,2],[2,3],[5,6],[6,7]]
max is 367 but ans is 366, which is wrong by greedy
"""
class Solution_WA(object):
    def maxScore(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        def bfs(u):
            lookup[u] = True
            result = [u]
            for u in result:
                for v in adj[u]:
                    if lookup[v]:
                        continue
                    lookup[v] = True
                    result.append(v)
            return result

        def f(l, r, is_cycle):
            a = b = r
            result = 0
            for c in reversed(xrange(l, r)):
                result += a*c
                a, b = b, c
            if is_cycle:
                result += a*b
            return result

        adj = [[] for _ in xrange(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        cycles, chains = [], []
        lookup = [False]*n
        for u in xrange(n):
            if lookup[u]:
                continue
            comp = bfs(u)
            if all(len(adj[x]) == 2 for x in comp):
                cycles.append(len(comp))
            else:
                chains.append(len(comp))
        result = 0
        for l in cycles:
            result += f(n-l+1, n, True)
            n -= l
        cnt = [0]*((max(chains) if chains else 0)+1)
        for l in chains:
            cnt[l] += 1
        for l in reversed(xrange(len(cnt))):
            for _ in xrange(cnt[l]):
                result += f(n-l+1, n, False)
                n -= l
        return result

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Empty graph
        (0, []),
        # 2) Single node, no edges
        (1, []),
        # 3) Single node with a self-loop
        (1, [[0, 0]]),
        # 4) Two nodes, one edge
        (2, [[0, 1]]),
        # 5) Triangle cycle (3-cycle)
        (3, [[0, 1], [1, 2], [2, 0]]),
        # 6) Mixed: 3-cycle + path of length 3 + isolated node
        (7, [[0, 1], [1, 2], [2, 0], [3, 4], [4, 5]]),
        # 7) Star graph with 6 nodes (center 0 connected to 1..5)
        (6, [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5]]),
        # 8) Complete graph K5
        (5, [[0, 1], [0, 2], [0, 3], [0, 4],
             [1, 2], [1, 3], [1, 4],
             [2, 3], [2, 4],
             [3, 4]]),
        # 9) Mixed: 4-cycle with a tail + a 3-path + two isolated nodes
        (10, [[0, 1], [1, 2], [2, 3], [3, 0], [1, 4], [5, 6], [6, 7]]),
        # 10) Mixed: three disjoint edges, a 4-cycle, and two isolated nodes
        (12, [[0, 1], [2, 3], [4, 5], [8, 9], [9, 10], [10, 11], [11, 8]]),
    ]

    # Warm-up
    sol = Solution_WA()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxScore(*test)
        else:
            sol.maxScore(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution_WA()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxScore(*test)
            else:
                result = sol.maxScore(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()