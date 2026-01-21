# Time:  O(n^4 * 2^n)
# Space: O(n + e)

# bitmasks, dp, freq table
class Solution(object):
    def maxLen(self, n, edges, label):
        """
        :type n: int
        :type edges: List[List[int]]
        :type label: str
        :rtype: int
        """
        def popcount(x):
            return bin(x).count('1')

        if len(edges) == n*(n-1)//2:  # to improve performance
            cnt = [0]*26
            for x in label:
                cnt[ord(x)-ord('a')] += 1
            return 2*sum(c//2 for c in cnt)+1*any(c%2 for c in cnt)

        adj = [[] for _ in xrange(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        dp = [[[False]*n for _ in xrange(n)]for _ in xrange(1<<n)]
        for u in xrange(n):
            dp[1<<u][u][u] = True
        for u, v in edges:
            if label[u] == label[v]:
                dp[(1<<u)|(1<<v)][min(u, v)][max(u, v)] = True
        result = 0
        for mask in xrange(1, 1<<n):
            for u in xrange(n):
                for v in xrange(u, n):
                    if not dp[mask][u][v]:
                        continue
                    result = max(result, popcount(mask))
                    for nu in adj[u]:
                        if mask&(1<<nu):
                            continue
                        for nv in adj[v]:
                            if mask&(1<<nv):
                                continue
                            if nu == nv:
                                continue
                            if label[nu] == label[nv]:
                                dp[mask|(1<<nu)|(1<<nv)][min(nu, nv)][max(nu, nv)] = True
        return result


if __name__ == "__main__":
    def build_complete_edges(n):
        e = []
        for i in xrange(n):
            for j in xrange(i + 1, n):
                e.append([i, j])
        return e

    def build_almost_complete_edges(n, a, b):
        u = a if a < b else b
        v = b if a < b else a
        e = []
        for i in xrange(n):
            for j in xrange(i + 1, n):
                if i == u and j == v:
                    continue
                e.append([i, j])
        return e

    tests = []

    # 1) n=1, complete
    tests.append({'n': 1, 'edges': build_complete_edges(1), 'label': "a"})

    # 2) n=5, complete
    tests.append({'n': 5, 'edges': build_complete_edges(5), 'label': "abcde"})

    # 3) n=6, complete
    tests.append({'n': 6, 'edges': build_complete_edges(6), 'label': "aabbcc"})

    # 4) n=12, complete
    tests.append({'n': 12, 'edges': build_complete_edges(12), 'label': "abacabadabac"})

    # 5) n=7, almost complete (missing one edge)
    tests.append({'n': 7, 'edges': build_almost_complete_edges(7, 1, 5), 'label': "abacaba"})

    # 6) n=9, path
    e = []
    for i in xrange(8):
        e.append([i, i + 1])
    tests.append({'n': 9, 'edges': e, 'label': "abccbaabc"})

    # 7) n=9, star centered at 0
    e = []
    for i in xrange(1, 9):
        e.append([0, i])
    tests.append({'n': 9, 'edges': e, 'label': "aaaaaaaaa"})

    # 8) n=7, cycle
    e = []
    for i in xrange(6):
        e.append([i, i + 1])
    e.append([6, 0])
    tests.append({'n': 7, 'edges': e, 'label': "abcdefa"})

    # 9) n=10, tree
    e = [
        [0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[3,7],[4,8],[6,9]
    ]
    tests.append({'n': 10, 'edges': e, 'label': "abcabcabca"})

    # 10) n=8, two components (two paths)
    e = [
        [0,1],[1,2],[2,3],
        [4,5],[5,6],[6,7]
    ]
    tests.append({'n': 8, 'edges': e, 'label': "abbaabba"})

    sink = 0
    sol = Solution()

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            res = sol.maxLen(t['n'], t['edges'], t['label'])
            checksum += res
        sink += checksum
    print(sink)