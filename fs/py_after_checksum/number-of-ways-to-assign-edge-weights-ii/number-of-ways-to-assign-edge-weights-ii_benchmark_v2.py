
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
    tests = [
        {'edges': [[1, 2]], 'queries': [[1, 2], [1, 1]]},
        {'edges': [[1, 2], [2, 3], [3, 4], [4, 5]], 'queries': [[1, 5], [2, 4], [3, 3]]},
        {'edges': [[1, 2], [1, 3], [1, 4], [1, 5], [1, 6]], 'queries': [[2, 3], [4, 5], [6, 1]]},
        {'edges': [[1, 2], [1, 3], [2, 4], [2, 5], [3, 6], [3, 7]], 'queries': [[4, 5], [4, 6], [7, 7]]},
        {'edges': [[1, 2], [1, 3], [3, 4], [3, 5], [2, 6], [6, 7], [5, 8]], 'queries': [[7, 8], [2, 5], [4, 6]]},
        {'edges': [[1, 2], [2, 3], [2, 4], [4, 5], [4, 6], [6, 7], [3, 8], [8, 9], [9, 10]], 'queries': [[1, 10], [5, 7], [3, 6], [8, 8]]},
        {'edges': [[5, 1], [5, 2], [5, 3], [5, 4], [5, 6], [5, 7], [5, 8], [5, 9]], 'queries': [[1, 9], [2, 7], [4, 5]]},
        {'edges': [[1, 2], [2, 3], [3, 4], [4, 5], [3, 6], [6, 7], [2, 8], [8, 9], [5, 10], [10, 11], [11, 12]], 'queries': [[7, 9], [12, 1], [6, 10], [3, 3]]},
        {'edges': [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15]], 'queries': [[1, 15], [5, 10], [7, 7], [2, 14]]},
        {'edges': [[1, 2], [1, 3], [2, 4], [2, 5], [3, 6], [3, 7], [4, 8], [4, 9], [5, 10], [5, 11], [6, 12], [6, 13]], 'queries': [[8, 9], [8, 13], [10, 11], [12, 1]]}
    ]

    sol = Solution()

    iterations = 1
    sink = 0
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            out = sol.assignEdgeWeights(t['edges'], t['queries'])
            for v in out:
                checksum += v
        sink += checksum
    print(sink)
    # print sink
