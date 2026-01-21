
# Time:  O(n + q)
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


# iterative dfs, Tarjan's Offline LCA Algorithm, combinatorics
class Solution(object):
    def assignEdgeWeights(self, edges, queries):
        """
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        MOD = 10**9+7
        def iter_dfs():
            lookup = [False]*len(adj)
            lookup2 = [[] for _ in xrange(len(adj))]
            for i, q in enumerate(queries):
                for x in q:
                    lookup2[x-1].append(i)
            uf = UnionFind(len(adj))
            ancestor = range(len(adj))
            dist = [0]*len(adj)
            result = [0]*len(queries)
            stk = [(1, (0,))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u = args[0]
                    for i in lookup2[u]:
                        if queries[i][0] == queries[i][1]:
                            continue
                        result[i] += dist[u]
                        for x in queries[i]:
                            if lookup[x-1]:
                                result[i] -= 2*dist[ancestor[uf.find_set(x-1)]]
                    lookup[u] = True
                    stk.append((2, (u, 0)))
                elif step == 2:
                    u, i = args
                    if i == len(adj[u]):
                        continue
                    v = adj[u][i]
                    stk.append((2, (u, i+1)))
                    if lookup[v]:
                        continue
                    dist[v] = dist[u]+1
                    stk.append((3, (v, u)))
                    stk.append((1, (v, u)))
                elif step == 3:
                    v, u = args
                    uf.union_set(v, u)
                    ancestor[uf.find_set(u)] = u                    
            return result

        adj = [[] for _ in xrange(len(edges)+1)]
        for u, v in edges:
            adj[u-1].append(v-1)
            adj[v-1].append(u-1)
        result = iter_dfs()
        POW2 = [1]*(len(adj)-1)
        for i in xrange(len(POW2)-1):
            POW2[i+1] = (POW2[i]*2)%MOD
        return [POW2[x-1] if x-1 >= 0 else 0 for x in result]


# Time:  O(n + q)
# Space: O(n + q)
# dfs, Tarjan's Offline LCA Algorithm, combinatorics
class Solution2(object):
    def assignEdgeWeights(self, edges, queries):
        """
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        MOD = 10**9+7
        def dfs(u):
            for i in lookup2[u]:
                if queries[i][0] == queries[i][1]:
                    continue
                result[i] += dist[u]
                for x in queries[i]:
                    if lookup[x-1]:
                        result[i] -= 2*dist[ancestor[uf.find_set(x-1)]]
            lookup[u] = True
            for v in adj[u]:
                if lookup[v]:
                    continue
                dist[v] = dist[u]+1
                dfs(v)
                uf.union_set(v, u)
                ancestor[uf.find_set(u)] = u
            
        adj = [[] for _ in xrange(len(edges)+1)]
        for u, v in edges:
            adj[u-1].append(v-1)
            adj[v-1].append(u-1)
        lookup = [False]*len(adj)
        lookup2 = [[] for _ in xrange(len(adj))]
        for i, q in enumerate(queries):
            for x in q:
                lookup2[x-1].append(i)
        uf = UnionFind(len(adj))
        ancestor = range(len(adj))
        dist = [0]*len(adj)
        result = [0]*len(queries)
        dfs(0)
        POW2 = [1]*(len(adj)-1)
        for i in xrange(len(POW2)-1):
            POW2[i+1] = (POW2[i]*2)%MOD
        return [POW2[x-1] if x-1 >= 0 else 0 for x in result]


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test cases
    tests = []

    # 1) Single node tree, self queries
    t = {}
    t['edges'] = []  # n = 1
    t['queries'] = [[1,1], [1,1], [1,1]]
    tests.append(t)

    # 2) Two-node tree with various pairs
    t = {}
    t['edges'] = [[1,2]]
    t['queries'] = [[1,2], [2,1], [1,1], [2,2], [1,2]]
    tests.append(t)

    # 3) Chain of 5 nodes
    t = {}
    t['edges'] = [[1,2],[2,3],[3,4],[4,5]]
    t['queries'] = [[1,5], [2,4], [3,5], [1,3], [2,5]]
    tests.append(t)

    # 4) Star with 6 nodes centered at 1
    t = {}
    t['edges'] = [[1,2],[1,3],[1,4],[1,5],[1,6]]
    t['queries'] = [[2,3], [4,6], [2,5], [1,3], [5,5]]
    tests.append(t)

    # 5) Balanced-ish binary tree with 7 nodes
    t = {}
    t['edges'] = [[1,2],[1,3],[2,4],[2,5],[3,6],[3,7]]
    t['queries'] = [[4,5], [4,6], [2,3], [7,7], [5,6], [1,7], [4,7]]
    tests.append(t)

    # 6) Unbalanced tree with 10 nodes
    t = {}
    t['edges'] = [[1,2],[2,3],[3,4],[4,5],[5,6],[3,7],[7,8],[2,9],[9,10]]
    t['queries'] = [[1,6], [8,10], [4,7], [2,8], [6,9], [1,10], [5,5]]
    tests.append(t)

    # 7) Long chain with 15 nodes
    t = {}
    t['edges'] = []
    for i in range(1, 15):
        t['edges'].append([i, i+1])
    t['queries'] = [[1,15], [1,8], [7,14], [3,12], [5,5], [2,13], [4,11]]
    tests.append(t)

    # 8) Tree with 4 nodes but empty queries
    t = {}
    t['edges'] = [[1,2],[2,3],[2,4]]
    t['queries'] = []
    tests.append(t)

    # 9) Multi-level tree with 8 nodes
    t = {}
    t['edges'] = [[1,2],[1,3],[2,4],[2,5],[3,6],[6,7],[6,8]]
    t['queries'] = [[4,5], [4,6], [7,8], [3,5], [2,8], [1,7], [5,7]]
    tests.append(t)

    # 10) Larger tree with 20 nodes
    t = {}
    t['edges'] = [
        [1,2],[1,3],[2,4],[2,5],[3,6],[3,7],
        [4,8],[5,9],[5,10],[6,11],[7,12],[7,13],
        [8,14],[9,15],[10,16],[11,17],[12,18],[13,19],[14,20]
    ]
    t['queries'] = [
        [14,20], [15,16], [17,18], [19,4], [10,12], [2,20], [6,13], [1,11], [3,15], [8,18]
    ]
    tests.append(t)

    # Benchmark
    checksum = 0
    mask64 = (1 << 64) - 1
    def to_s64(x):
        x &= mask64
        if x >= (1 << 63):
            x -= (1 << 64)
        return x

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for t in tests:
            sol = Solution()
            edges = [list(e) for e in t['edges']]
            queries = [list(q) for q in t['queries']]
            ans = sol.assignEdgeWeights(edges, queries)
            checksum = to_s64(checksum + int(len(ans)))
            for i in xrange(len(ans)):
                checksum = to_s64(checksum + ans[i])
                c = checksum
                mixed = (c << 7) ^ (c >> 3)
                checksum = to_s64(c ^ mixed)
    end = time.time()

    elapsed_ms = int(round((end - start) * 1000.0))
    print 'Checksum:', checksum
    print 'Elapsed time (ms):', elapsed_ms
