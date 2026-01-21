
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
    import time

    tests = []

    # Test 1: Small 2-node tree with multiple updates/queries
    t = {}
    t['n'] = 2
    t['edges'] = [[1, 2, 5]]
    t['queries'] = [
        [2, 1], [2, 2],
        [1, 1, 2, 7], [2, 2],
        [1, 1, 2, 3], [2, 2]
    ]
    tests.append(t)

    # Test 2: Chain of 5 nodes
    t = {}
    t['n'] = 5
    t['edges'] = []
    for i in xrange(1, t['n']):
        t['edges'].append([i, i + 1, i])  # weights 1,2,3,4
    t['queries'] = [
        [2, 5],
        [1, 2, 3, 10],
        [2, 5],
        [1, 4, 5, 1],
        [2, 3],
        [1, 1, 2, 5],
        [2, 5],
        [2, 1],
        [2, 4]
    ]
    tests.append(t)

    # Test 3: Star tree centered at 1
    t = {}
    t['n'] = 7
    t['edges'] = []
    for v in xrange(2, 8):
        t['edges'].append([1, v, 2 * (v - 1)])  # 2,4,6,8,10,12
    t['queries'] = [
        [2, 2], [2, 3], [2, 4], [2, 5], [2, 6], [2, 7],
        [1, 1, 7, 3], [2, 7],
        [1, 1, 2, 5], [2, 2],
        [1, 1, 6, 1], [2, 6],
        [2, 1]
    ]
    tests.append(t)

    # Test 4: Balanced binary tree with updates
    t = {}
    t['n'] = 7
    t['edges'] = [
        [1, 2, 3], [1, 3, 5],
        [2, 4, 2], [2, 5, 4],
        [3, 6, 6], [3, 7, 8]
    ]
    t['queries'] = [
        [2, 4], [2, 5], [2, 6], [2, 7],
        [1, 2, 5, 10],
        [1, 1, 3, 7],
        [2, 5], [2, 6], [2, 7]
    ]
    tests.append(t)

    # Test 5: Deep chain with large weights
    t = {}
    t['n'] = 10
    t['edges'] = []
    for i in xrange(1, t['n']):
        t['edges'].append([i, i + 1, 100000 + i])
    t['queries'] = [
        [2, 10],
        [1, 5, 6, 200000],
        [2, 10],
        [1, 1, 2, 50000],
        [2, 2], [2, 10]
    ]
    tests.append(t)

    # Test 6: 1-indexed heap-like tree (n=15) with patterned weights
    t = {}
    t['n'] = 15
    t['edges'] = []
    for i in xrange(2, t['n'] + 1):
        p = i // 2
        w = (i * 3) % 10 + 1
        t['edges'].append([p, i, w])
    t['queries'] = [
        [2, 15], [2, 8],
        [1, 7, 14, 9], [2, 14],
        [1, 5, 10, 8], [2, 10],
        [1, 1, 3, 5], [2, 6], [2, 15],
        [1, 2, 5, 7], [2, 9], [2, 12]
    ]
    tests.append(t)

    # Test 7: Mixed shape with repeated edge updates
    t = {}
    t['n'] = 8
    t['edges'] = [
        [1, 2, 1], [1, 3, 2],
        [2, 4, 3], [2, 5, 4],
        [3, 6, 5], [6, 7, 6], [6, 8, 7]
    ]
    t['queries'] = [
        [2, 7],
        [1, 6, 7, 1], [2, 7],
        [1, 6, 7, 10], [2, 7],
        [1, 3, 6, 1],
        [2, 8], [2, 5]
    ]
    tests.append(t)

    # Test 8: Star with only queries (no updates)
    t = {}
    t['n'] = 5
    t['edges'] = [
        [1, 2, 1], [1, 3, 2], [1, 4, 3], [1, 5, 4]
    ]
    t['queries'] = [
        [2, 1], [2, 2], [2, 3], [2, 4], [2, 5]
    ]
    tests.append(t)

    # Test 9: Chain with all updates before queries
    t = {}
    t['n'] = 6
    t['edges'] = [
        [1, 2, 5], [2, 3, 5], [3, 4, 5], [4, 5, 5], [5, 6, 5]
    ]
    t['queries'] = [
        [1, 2, 3, 1], [1, 4, 5, 2], [1, 1, 2, 3], [1, 5, 6, 4], [1, 3, 4, 5],
        [2, 6], [2, 3], [2, 5], [2, 1], [2, 2]
    ]
    tests.append(t)

    # Test 10: Random-ish tree with mixed queries/updates
    t = {}
    t['n'] = 12
    t['edges'] = [
        [1, 2, 3], [1, 3, 1],
        [2, 4, 4], [2, 5, 2],
        [3, 6, 7], [3, 7, 5],
        [4, 8, 6], [5, 9, 3],
        [6, 10, 2], [7, 11, 4], [7, 12, 8]
    ]
    t['queries'] = [
        [2, 12], [2, 11], [2, 8],
        [1, 7, 12, 3], [2, 12],
        [1, 1, 3, 2], [1, 2, 5, 6],
        [2, 9], [2, 3], [2, 10], [2, 5],
        [1, 6, 10, 5], [2, 10],
        [1, 4, 8, 1], [2, 8],
        [2, 1]
    ]
    tests.append(t)

    solver = Solution()

    checksum = 0
    mask = (1 << 64) - 1

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        for t in tests:
            res = solver.treeQueries(t['n'], t['edges'], t['queries'])
            for v in res:
                term = ((v & mask) * 1315423911) & mask
                term = (term + iter) & mask
                checksum = (checksum + term) & mask
            checksum = (checksum + len(res)) & mask
    end = time.time()

    elapsed_ms = (end - start) * 1000.0
    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms
