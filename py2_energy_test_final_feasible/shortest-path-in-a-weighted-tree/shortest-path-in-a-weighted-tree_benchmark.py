# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn)
# Space: O(n)

class BIT(object):  # 0-indexed.
    def __init__(self, n):
        self.__bit = [0]*(n+1)  # Extra one for dummy node.

    def add(self, i, val):
        i += 1  # Extra one for dummy node.
        while i < len(self.__bit):
            self.__bit[i] += val
            i += (i & -i)

    def query(self, i):
        i += 1  # Extra one for dummy node.
        ret = 0
        while i > 0:
            ret += self.__bit[i]
            i -= (i & -i)
        return ret


# iterative dfs, fenwick tree
class Solution(object):
    def treeQueries(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def iter_dfs():
            L, R, dist, lookup = [0]*n, [0]*n, [0]*n, [0]*n
            cnt = 0
            stk = [(1, (0, -1, 0))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u, p, d = args
                    L[u] = cnt
                    cnt += 1
                    dist[u] = d
                    stk.append((2, (u,)))
                    for v, w in adj[u]:
                        if v == p:
                            continue
                        lookup[v] = w
                        stk.append((1, (v, u, d+w)))
                elif step == 2:
                    u = args[0]
                    R[u] = cnt
            return L, R, dist, lookup

        adj = [[] for _ in xrange(n)]
        for u, v, w in edges:
            u -= 1
            v -= 1
            adj[u].append((v, w))
            adj[v].append((u, w))
        L, R, dist, lookup = iter_dfs()
        bit = BIT(n)
        result = []
        for q in queries:
            if q[0] == 1:
                _, u, v, w = q
                u -= 1
                v -= 1
                if L[u] > L[v]:
                    u, v = v, u 
                diff = w-lookup[v]
                bit.add(L[v], diff)
                bit.add(R[v], -diff)
                lookup[v] = w
            else:
                _, x = q
                x -= 1
                result.append(dist[x]+bit.query(L[x]))
        return result


# Time:  O(nlogn)
# Space: O(n)
# dfs, fenwick tree
class Solution2(object):
    def treeQueries(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def dfs(u, p, d):
            L[u] = cnt[0]
            cnt[0] += 1
            dist[u] = d
            for v, w in adj[u]:
                if v == p:
                    continue
                lookup[v] = w
                dfs(v, u, d+w)
            R[u] = cnt[0]

        adj = [[] for _ in xrange(n)]
        for u, v, w in edges:
            u -= 1
            v -= 1
            adj[u].append((v, w))
            adj[v].append((u, w))
        L, R, dist, lookup = [0]*n, [0]*n, [0]*n, [0]*n
        cnt = [0]
        dfs(0, -1, 0)
        bit = BIT(n)
        result = []
        for q in queries:
            if q[0] == 1:
                _, u, v, w = q
                u -= 1
                v -= 1
                if L[u] > L[v]:
                    u, v = v, u 
                diff = w-lookup[v]
                bit.add(L[v], diff)
                bit.add(R[v], -diff)
                lookup[v] = w
            else:
                _, x = q
                x -= 1
                result.append(dist[x]+bit.query(L[x]))
        return result

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # Test 1: Single node tree
        (1,
         [],
         [
             [2, 1]
         ]),

        # Test 2: Two-node tree with update
        (2,
         [
             [1, 2, 5]
         ],
         [
             [2, 2],
             [1, 1, 2, 7],
             [2, 2]
         ]),

        # Test 3: Star-shaped tree
        (6,
         [
             [1, 2, 3], [1, 3, 4], [1, 4, 5], [1, 5, 6], [1, 6, 7]
         ],
         [
             [2, 2], [2, 3], [2, 6],
             [1, 1, 4, 10], [2, 4],
             [1, 1, 2, 2], [2, 2]
         ]),

        # Test 4: Line tree with negative update and reversed endpoints
        (5,
         [
             [1, 2, 1], [2, 3, 2], [3, 4, 3], [4, 5, 4]
         ],
         [
             [2, 5],
             [1, 4, 3, -1],
             [2, 5],
             [1, 1, 2, 5],
             [2, 5]
         ]),

        # Test 5: Balanced-ish tree with zero weights
        (7,
         [
             [1, 2, 0], [1, 3, 5], [2, 4, 0], [2, 5, 1], [3, 6, 2], [3, 7, 0]
         ],
         [
             [2, 4], [2, 7],
             [1, 2, 5, 3],
             [2, 5],
             [1, 3, 7, 4],
             [2, 7]
         ]),

        # Test 6: Random tree with multiple updates on same edge
        (8,
         [
             [1, 2, 3], [1, 3, 1], [2, 4, 4], [2, 5, 2], [3, 6, 7], [6, 7, 5], [6, 8, 6]
         ],
         [
             [2, 7],
             [1, 6, 7, 10],
             [2, 7],
             [1, 6, 7, 5],
             [2, 7],
             [1, 2, 5, 1],
             [2, 5]
         ]),

        # Test 7: Heavy weights within int range after sum
        (4,
         [
             [1, 2, 100000000], [2, 3, 100000000], [3, 4, 100000000]
         ],
         [
             [2, 4],
             [1, 2, 3, 50000000],
             [2, 4]
         ]),

        # Test 8: Negative weights and update to more negative
        (3,
         [
             [1, 2, -5], [2, 3, -5]
         ],
         [
             [2, 3],
             [2, 2],
             [1, 2, 3, -10],
             [2, 3]
         ]),

        # Test 9: Mixed updates with reversed endpoint orders
        (5,
         [
             [1, 2, 2], [2, 3, 3], [2, 4, 4], [1, 5, 1]
         ],
         [
             [2, 3],
             [1, 3, 2, 10],
             [2, 3],
             [1, 5, 1, 0],
             [2, 5],
             [1, 4, 2, 1],
             [2, 4]
         ]),

        # Test 10: Chain with zeros, toggle updates
        (6,
         [
             [1, 2, 0], [2, 3, 0], [3, 4, 0], [4, 5, 0], [5, 6, 0]
         ],
         [
             [2, 6],
             [1, 3, 4, 5],
             [2, 6],
             [1, 3, 4, 0],
             [2, 6],
             [1, 2, 3, 2],
             [2, 6]
         ]),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.treeQueries(*test)
        else:
            sol.treeQueries(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.treeQueries(*test)
            else:
                result = sol.treeQueries(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()