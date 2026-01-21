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


if __name__ == "__main__":
    import time

    # Build 10 diverse test inputs
    tests = []

    # 1) Single node, trivial queries
    t = {}
    t['n'] = 1
    t['edges'] = []
    t['queries'] = [[0,0], [0,0]]
    tests.append(t)

    # 2) Two-node tree
    t = {}
    t['n'] = 2
    t['edges'] = [[0,1,5]]
    t['queries'] = [[0,1], [1,0], [0,0], [1,1]]
    tests.append(t)

    # 3) Star tree with center 0
    t = {}
    t['n'] = 7
    t['edges'] = [[0,1,3],[0,2,5],[0,3,2],[0,4,7],[0,5,11],[0,6,1]]
    t['queries'] = [[1,2],[3,4],[5,6],[1,6],[2,5],[3,0],[4,1],[2,3]]
    tests.append(t)

    # 4) Path of length 10
    t = {}
    t['n'] = 10
    t['edges'] = []
    for i in range(9):
        t['edges'].append([i, i+1, i+1])
    t['queries'] = [[0,9],[2,7],[8,4],[3,3],[9,1],[0,0],[5,9],[1,6]]
    tests.append(t)

    # 5) Balanced-ish binary tree n=15
    t = {}
    t['n'] = 15
    t['edges'] = []
    for i in range(7):
        l = 2*i+1
        r = 2*i+2
        if l < t['n']:
            t['edges'].append([i, l, i+2])
        if r < t['n']:
            t['edges'].append([i, r, i+3])
    t['queries'] = [[14,0],[7,8],[10,11],[3,4],[13,9],[6,1],[2,14],[5,12],[0,0]]
    tests.append(t)

    # 6) Random-like tree n=20 (fixed)
    t = {}
    t['n'] = 20
    t['edges'] = [
        [0,1,4],[0,2,8],[2,3,3],[1,4,7],[3,5,6],[2,6,5],[5,7,9],[4,8,2],[6,9,1],
        [7,10,4],[8,11,3],[9,12,8],[10,13,2],[11,14,7],[12,15,5],[13,16,4],[14,17,6],[15,18,3],[16,19,9]
    ]
    t['queries'] = [[0,19],[4,14],[10,3],[12,7],[5,15],[11,6],[18,2],[9,9],[1,13],[8,0]]
    tests.append(t)

    # 7) Heavy weights path n=8
    t = {}
    t['n'] = 8
    t['edges'] = []
    w = 1000000000
    for i in range(7):
        t['edges'].append([i, i+1, w - (i*3)])
    t['queries'] = [[0,7],[1,6],[2,5],[3,4],[0,0],[7,7],[1,1]]
    tests.append(t)

    # 8) Repeated queries on a moderate tree n=12
    t = {}
    t['n'] = 12
    t['edges'] = [
        [0,1,1],[0,2,2],[1,3,3],[1,4,4],[2,5,5],[2,6,6],
        [3,7,7],[4,8,8],[5,9,9],[6,10,10],[6,11,11]
    ]
    t['queries'] = [[7,9],[7,9],[7,9],[8,10],[8,10],[3,11],[3,11],[0,11],[5,1],[2,8],[4,4]]
    tests.append(t)

    # 9) Non-empty tree but zero queries
    t = {}
    t['n'] = 5
    t['edges'] = [[0,1,2],[1,2,3],[2,3,4],[3,4,5]]
    t['queries'] = []
    tests.append(t)

    # 10) Larger path n=50 with mixed queries
    t = {}
    t['n'] = 50
    t['edges'] = []
    for i in range(49):
        t['edges'].append([i, i+1, (i%7)+1])
    t['queries'] = [
        [0,49],[10,40],[5,25],[12,12],[3,44],[7,33],[0,1],[1,2],[2,3],[3,4],
        [20,21],[21,22],[22,23],[23,24],[24,25],[25,26],[26,27],[27,28],[28,29],[30,35]
    ]
    tests.append(t)

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    t1 = time.time()
    iterations = 1000
    for iter in range(iterations):
        for ti in range(len(tests)):
            n = tests[ti]['n']
            edges = [e[:] for e in tests[ti]['edges']]
            queries = [q[:] for q in tests[ti]['queries']]
            res = sol.findMedian(n, edges, queries)
            checksum ^= (len(res) + (ti + 1))
            checksum &= mask
            for i in range(len(res)):
                checksum = (checksum * 1000003 + (res[i] + 1) + (i + 1)) & mask
    t2 = time.time()
    elapsed_ns = int((t2 - t1) * 1000000000)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns