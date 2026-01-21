
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


if __name__ == "__main__":
    tests = []

    # Test 1: Single node
    tests.append({
        'n': 1,
        'edges': [],
        'queries': [[2, 1]]
    })

    # Test 2: Small chain with updates
    tests.append({
        'n': 3,
        'edges': [[1, 2, 5], [2, 3, 7]],
        'queries': [[2, 3], [1, 2, 3, 10], [2, 3], [1, 1, 2, 1], [2, 3], [2, 2], [2, 1]]
    })

    # Test 3: Star tree
    tests.append({
        'n': 5,
        'edges': [[1, 2, 1], [1, 3, 2], [1, 4, 3], [1, 5, 4]],
        'queries': [[2, 5], [1, 1, 3, 10], [2, 3], [2, 5], [1, 1, 5, 1], [2, 5], [2, 1]]
    })

    # Test 4: Balanced tree
    tests.append({
        'n': 7,
        'edges': [[1, 2, 3], [1, 3, 4], [2, 4, 5], [2, 5, 6], [3, 6, 7], [3, 7, 8]],
        'queries': [[2, 4], [2, 7], [1, 3, 7, 2], [2, 7], [1, 1, 3, 10], [2, 6], [2, 2], [1, 2, 5, 1], [2, 5]]
    })

    # Test 5: Random small tree with multiple updates
    tests.append({
        'n': 6,
        'edges': [[1, 2, 2], [1, 3, 5], [2, 4, 1], [2, 5, 2], [3, 6, 3]],
        'queries': [[2, 6], [1, 1, 3, 1], [2, 6], [1, 2, 5, 10], [2, 5], [1, 2, 4, 5], [2, 4], [2, 3]]
    })

    # Test 6: Chain of 10 nodes with several updates
    tests.append({
        'n': 10,
        'edges': [[1, 2, 1], [2, 3, 2], [3, 4, 3], [4, 5, 4], [5, 6, 5], [6, 7, 6], [7, 8, 7], [8, 9, 8], [9, 10, 9]],
        'queries': [[2, 10], [1, 5, 6, 10], [2, 10], [1, 1, 2, 0], [2, 1], [2, 2], [2, 3], [1, 9, 10, 1], [2, 10], [2, 5]]
    })

    # Test 7: Star with only queries
    tests.append({
        'n': 4,
        'edges': [[1, 2, 7], [1, 3, 8], [1, 4, 9]],
        'queries': [[2, 2], [2, 3], [2, 4], [2, 1], [2, 3], [2, 2]]
    })

    # Test 8: Mixed weights with larger values
    tests.append({
        'n': 8,
        'edges': [[1, 2, 100], [2, 3, 200], [2, 4, 300], [1, 5, 400], [5, 6, 500], [5, 7, 600], [7, 8, 700]],
        'queries': [[2, 8], [1, 5, 7, 1000], [2, 8], [1, 1, 5, 50], [2, 8], [2, 6], [1, 2, 4, 100], [2, 4]]
    })

    # Test 9: Complete binary tree up to 15
    tests.append({
        'n': 15,
        'edges': [[1, 2, 2], [1, 3, 3], [2, 4, 4], [2, 5, 5], [3, 6, 6], [3, 7, 7], [4, 8, 8], [4, 9, 9],
                  [5, 10, 10], [5, 11, 11], [6, 12, 12], [6, 13, 13], [7, 14, 14], [7, 15, 15]],
        'queries': [[2, 15], [1, 7, 15, 1], [2, 15], [1, 1, 3, 10], [2, 15], [2, 14], [1, 2, 5, 1], [2, 11]]
    })

    # Test 10: Random tree with repeated updates
    tests.append({
        'n': 9,
        'edges': [[1, 2, 5], [1, 3, 2], [3, 4, 4], [3, 5, 1], [2, 6, 3], [6, 7, 6], [6, 8, 2], [8, 9, 7]],
        'queries': [[2, 9], [1, 6, 8, 5], [2, 9], [1, 1, 2, 1], [2, 9], [1, 3, 4, 10], [2, 4], [1, 3, 5, 7], [2, 5], [2, 6]]
    })

    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            sol = Solution()
            out = sol.treeQueries(t['n'], t['edges'], t['queries'])
    #         for v in out:
    #             checksum += v
    #     sink = checksum
    # print(sink)
