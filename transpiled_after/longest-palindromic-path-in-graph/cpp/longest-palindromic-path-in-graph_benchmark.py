# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Precompute edges for special cases
    # 7) Six-node almost complete graph (skip edge 0-5)
    edges_7 = [[i, j] for i in xrange(6) for j in xrange(i + 1, 6) if not (i == 0 and j == 5)]
    # 10) Twenty-node complete graph
    n10 = 20
    edges_10 = [[i, j] for i in xrange(n10) for j in xrange(i + 1, n10)]

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Single node
        (1, [], "a"),
        # 2) Two nodes, connected, same label
        (2, [[0, 1]], "aa"),
        # 3) Two nodes, disconnected, different labels
        (2, [], "ab"),
        # 4) Three-node path with palindromic labels
        (3, [[0, 1], [1, 2]], "aba"),
        # 5) Four-node cycle
        (4, [[0, 1], [1, 2], [2, 3], [3, 0]], "abca"),
        # 6) Five-node star centered at 0
        (5, [[0, 1], [0, 2], [0, 3], [0, 4]], "abcba"),
        # 7) Six-node almost complete graph (skip edge 0-5)
        (6, edges_7, "abccba"),
        # 8) Seven-node sparse tree-like structure
        (7, [[0, 1], [0, 2], [1, 3], [2, 4], [4, 5], [5, 6]], "abacaba"),
        # 9) Eight-node disconnected components (path + cycle)
        (8, [[0, 1], [1, 2], [2, 3], [4, 5], [5, 6], [6, 7], [7, 4]], "abcdabcd"),
        # 10) Twenty-node complete graph to hit the fast path
        (n10, edges_10, "abcdefghijklmnopqrst"),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxLen(*test)
        else:
            sol.maxLen(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxLen(*test)
            else:
                result = sol.maxLen(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()