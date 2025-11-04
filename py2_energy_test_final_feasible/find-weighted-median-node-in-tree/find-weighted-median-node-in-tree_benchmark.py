# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n + qlogh)
# Space: O(n + q)

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


def binary_search(left, right, check):
    while left <= right:
        mid = left+(right-left)//2
        if check(mid):
            right = mid-1
        else:
            left = mid+1
    return left


# iterative dfs, Tarjan's Offline LCA Algorithm, binary search, prefix sum
class Solution(object):
    def findMedian(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def iter_dfs():
            lookup = [False]*len(adj)
            lookup2 = [[] for _ in xrange(len(adj))]
            for i, q in enumerate(queries):
                for x in q:
                    lookup2[x].append(i)
            uf = UnionFind(len(adj))
            ancestor = range(len(adj))
            depth = [0]*len(adj)
            dist = [0]*len(adj)
            lca = [0]*len(queries)
            result = [0]*len(queries)
            stk = [(1, (0,))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u = args[0]
                    for i in lookup2[u]:
                        if queries[i][0] == queries[i][1]:
                            lca[i] = u
                            continue
                        result[i] += dist[u]
                        for x in queries[i]:
                            if lookup[x]:
                                lca[i] = ancestor[uf.find_set(x)]
                                result[i] -= 2*dist[lca[i]]
                    lookup[u] = True
                    stk.append((2, (u, 0)))
                elif step == 2:
                    u, i = args
                    if i == len(adj[u]):
                        continue
                    v, w = adj[u][i]
                    stk.append((2, (u, i+1)))
                    if lookup[v]:
                        continue
                    dist[v] = dist[u]+w
                    depth[v] = depth[u]+1
                    stk.append((3, (v, u)))
                    stk.append((1, (v, u)))
                elif step == 3:
                    v, u = args
                    uf.union_set(v, u)
                    ancestor[uf.find_set(u)] = u                    
            return result, lca, dist, depth
    
        def iter_dfs2():
            lookup3 = [[] for _ in xrange(len(adj))]
            for i, (u, v) in enumerate(queries):
                if 2*(dist[u]-dist[lca[i]]) >= result[i]:
                    lookup3[u].append((i, 0))
                else:
                    lookup3[v].append((i, 1))
            result2 = [0]*len(queries)
            path = []
            stk = [(1, (0,))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u = args[0]
                    path.append(u)
                    for i, t in lookup3[u]:
                        d = depth[u]-depth[lca[i]]
                        if t == 0:
                            j = binary_search(0, d, lambda x: 2*(dist[u]-dist[path[-(x+1)]]) >= result[i])
                            result2[i] = path[-(j+1)]
                        else:
                            l = dist[queries[i][0]]-dist[lca[i]]
                            j = binary_search(0, d-1, lambda x: 2*(l+(dist[path[-((d-1)+1)+x]]-dist[lca[i]])) >= result[i])
                            result2[i] = path[-((d-1)+1)+j]
                    stk.append((3, None))
                    stk.append((2, (u, 0)))
                elif step == 2:
                    u, i = args
                    if i == len(adj[u]):
                        continue
                    v, w = adj[u][i]
                    stk.append((2, (u, i+1)))
                    if len(path) >= 2 and path[-2] == v:
                        continue
                    dist[v] = dist[u]+w
                    depth[v] = depth[u]+1
                    stk.append((1, (v, u)))
                elif step == 3:
                    path.pop()
            return result2
    
        adj = [[] for _ in xrange(len(edges)+1)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        result, lca, dist, depth = iter_dfs()
        return iter_dfs2()


# Time:  O(n + qlogh)
# Space: O(n + q)
# dfs, Tarjan's Offline LCA Algorithm, binary search, prefix sum
class Solution2(object):
    def findMedian(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def dfs(u):
            for i in lookup2[u]:
                if queries[i][0] == queries[i][1]:
                    lca[i] = u
                    continue
                result[i] += dist[u]
                for x in queries[i]:
                    if lookup[x]:
                        lca[i] = ancestor[uf.find_set(x)]
                        result[i] -= 2*dist[lca[i]]
            lookup[u] = True
            for v, w in adj[u]:
                if lookup[v]:
                    continue
                dist[v] = dist[u]+w
                depth[v] = depth[u]+1
                dfs(v)
                uf.union_set(v, u)
                ancestor[uf.find_set(u)] = u
    
        def dfs2(u):
            path.append(u)
            for i, t in lookup3[u]:
                d = depth[u]-depth[lca[i]]
                if t == 0:
                    j = binary_search(0, d, lambda x: 2*(dist[u]-dist[path[-(x+1)]]) >= result[i])
                    result2[i] = path[-(j+1)]
                else:
                    l = dist[queries[i][0]]-dist[lca[i]]
                    j = binary_search(0, d-1, lambda x: 2*(l+(dist[path[-((d-1)+1)+x]]-dist[lca[i]])) >= result[i])
                    result2[i] = path[-((d-1)+1)+j]
            for v, w in adj[u]:
                if len(path) >= 2 and path[-2] == v:
                    continue
                dfs2(v)
            path.pop()
    
        adj = [[] for _ in xrange(len(edges)+1)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        lookup = [False]*len(adj)
        lookup2 = [[] for _ in xrange(len(adj))]
        for i, q in enumerate(queries):
            for x in q:
                lookup2[x].append(i)
        uf = UnionFind(len(adj))
        ancestor = range(len(adj))
        dist = [0]*len(adj)
        depth = [0]*len(adj)
        result = [0]*len(queries)
        lca = [-1]*len(queries)
        dfs(0)
        result2 = [0]*len(queries)
        lookup3 = [[] for _ in xrange(len(adj))]
        for i, (u, v) in enumerate(queries):
            if 2*(dist[u]-dist[lca[i]]) >= result[i]:
                lookup3[u].append((i, 0))
            else:
                lookup3[v].append((i, 1))
        path = []
        dfs2(0)
        return result2

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (5,
         [(0, 1, 1), (1, 2, 2), (2, 3, 3), (3, 4, 4)],
         [(0, 4), (1, 3), (2, 2), (4, 0)]
        ),
        (7,
         [(0, 1, 5), (0, 2, 1), (0, 3, 9), (0, 4, 2), (0, 5, 7), (0, 6, 3)],
         [(1, 2), (3, 4), (5, 6), (1, 0)]
        ),
        (7,
         [(0, 1, 4), (0, 2, 6), (1, 3, 3), (1, 4, 5), (2, 5, 2), (2, 6, 8)],
         [(3, 4), (3, 5), (5, 6), (4, 6)]
        ),
        (6,
         [(0, 1, 0), (1, 2, 0), (2, 3, 10), (3, 4, 0), (4, 5, 1)],
         [(0, 5), (1, 4), (2, 2), (3, 5)]
        ),
        (1,
         [],
         [(0, 0), (0, 0)]
        ),
        (4,
         [(0, 1, 1000000000), (1, 2, 1000000000), (1, 3, 999999999)],
         [(2, 3), (0, 3), (0, 2)]
        ),
        (9,
         [(0, 1, 2), (1, 2, 2), (1, 3, 7), (3, 4, 1), (3, 5, 1), (0, 6, 3), (6, 7, 3), (6, 8, 3)],
         [(2, 4), (7, 8), (2, 8), (5, 8), (0, 4)]
        ),
        (8,
         [(0, 1, 1), (1, 2, 1), (2, 3, 1), (3, 4, 10), (4, 5, 10), (5, 6, 10), (3, 7, 100)],
         [(0, 6), (0, 7), (2, 5), (1, 4)]
        ),
        (10,
         [(0, 1, 1), (1, 2, 1000), (2, 3, 1), (3, 4, 1000), (4, 5, 1), (5, 6, 1000), (6, 7, 1), (7, 8, 1000), (8, 9, 1)],
         [(0, 9), (0, 5), (4, 9), (3, 7)]
        ),
        (15,
         [
             (0, 1, 1), (0, 2, 2),
             (1, 3, 3), (1, 4, 4),
             (2, 5, 5), (2, 6, 6),
             (3, 7, 7), (3, 8, 8),
             (4, 9, 9), (4, 10, 10),
             (5, 11, 11), (5, 12, 12),
             (6, 13, 13), (6, 14, 14)
         ],
         [(7, 8), (7, 14), (9, 11), (10, 13), (12, 14), (0, 14)]
        ),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.findMedian(*test)
        else:
            sol.findMedian(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.findMedian(*test)
            else:
                result = sol.findMedian(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()