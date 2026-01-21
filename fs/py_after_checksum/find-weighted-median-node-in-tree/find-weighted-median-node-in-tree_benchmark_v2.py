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


if __name__ == '__main__':
    tests = []

    # 1) Single node
    tests.append({
        'n': 1,
        'edges': [],
        'queries': [[0, 0]]
    })

    # 2) Two nodes
    tests.append({
        'n': 2,
        'edges': [[0, 1, 5]],
        'queries': [[0, 1], [1, 0], [0, 0], [1, 1]]
    })

    # 3) Three-node chain
    tests.append({
        'n': 3,
        'edges': [[0, 1, 2], [1, 2, 3]],
        'queries': [[0, 2], [0, 1], [1, 2]]
    })

    # 4) Star with center 0
    tests.append({
        'n': 4,
        'edges': [[0, 1, 1], [0, 2, 2], [0, 3, 3]],
        'queries': [[1, 2], [1, 3], [2, 3], [0, 3]]
    })

    # 5) Chain with varied weights
    tests.append({
        'n': 5,
        'edges': [[0, 1, 1], [1, 2, 1], [2, 3, 10], [3, 4, 1]],
        'queries': [[0, 4], [0, 3], [2, 4]]
    })

    # 6) Balanced-ish tree
    tests.append({
        'n': 6,
        'edges': [[0, 1, 4], [0, 2, 1], [1, 3, 2], [1, 4, 2], [2, 5, 7]],
        'queries': [[3, 5], [4, 5], [3, 4], [2, 5], [0, 5]]
    })

    # 7) Unbalanced with a branch
    tests.append({
        'n': 7,
        'edges': [[0, 1, 1], [1, 2, 1], [2, 3, 1], [3, 4, 1], [4, 5, 10], [2, 6, 2]],
        'queries': [[6, 5], [0, 6], [1, 4], [3, 5]]
    })

    # 8) Larger branching
    tests.append({
        'n': 8,
        'edges': [[0, 1, 3], [0, 2, 5], [1, 3, 4], [1, 4, 6], [2, 5, 2], [5, 6, 1], [5, 7, 8]],
        'queries': [[3, 7], [4, 6], [6, 7], [2, 7]]
    })

    # 9) Long chain of 9
    tests.append({
        'n': 9,
        'edges': [[0, 1, 1], [1, 2, 1], [2, 3, 1], [3, 4, 1], [4, 5, 1], [5, 6, 1], [6, 7, 1], [7, 8, 1]],
        'queries': [[0, 8], [2, 6], [3, 3], [1, 7]]
    })

    # 10) Tree with varying weights
    tests.append({
        'n': 10,
        'edges': [[0, 1, 9], [0, 2, 3], [2, 3, 4], [2, 4, 5], [4, 5, 6], [4, 6, 7], [6, 7, 8], [6, 8, 2], [8, 9, 1]],
        'queries': [[1, 9], [5, 7], [3, 5], [0, 9], [2, 6]]
    })

    sol = Solution()
    sink = 0
    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for t in tests:
            res = sol.findMedian(t['n'], t['edges'], t['queries'])
            for x in res:
                checksum += x
        sink += checksum
    print(sink)