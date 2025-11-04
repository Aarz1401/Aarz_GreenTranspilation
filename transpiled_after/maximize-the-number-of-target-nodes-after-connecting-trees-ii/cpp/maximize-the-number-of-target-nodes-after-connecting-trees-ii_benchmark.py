# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n + m)
# Space: O(n + m)

# bfs
class Solution(object):
    def maxTargetNodes(self, edges1, edges2):
        """
        :type edges1: List[List[int]]
        :type edges2: List[List[int]]
        :rtype: List[int]
        """
        def bfs(adj):
            result = [0]*len(adj)
            parity = 0
            lookup = [-1]*len(adj)
            lookup[0] = parity
            q = [0]
            while q:
                new_q = []
                for u in q:
                    for v in adj[u]:
                        if lookup[v] != -1:
                            continue
                        lookup[v] = parity^1
                        new_q.append(v)
                q = new_q
                parity ^= 1
            cnt = sum(lookup)
            return [cnt if lookup[u] else len(adj)-cnt for u in xrange(len(adj))]
    
        def find_adj(edges):
            adj = [[] for _ in xrange(len(edges)+1)]
            for u, v in edges:
                adj[u].append(v)
                adj[v].append(u)
            return adj

        adj2 = find_adj(edges2)
        mx = max(bfs(adj2))
        adj1 = find_adj(edges1)
        return [mx+x for x in bfs(adj1)]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # Test 1: Single node trees
        ([], []),

        # Test 2: Two-node trees
        ([[0, 1]], [[0, 1]]),

        # Test 3: Chain vs Star (4 nodes)
        ([[0, 1], [1, 2], [2, 3]], [[0, 1], [0, 2], [0, 3]]),

        # Test 4: Balanced binary tree (7 nodes) vs Chain (7 nodes)
        (
            [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6]],
            [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6]]
        ),

        # Test 5: Long Chain (10 nodes) vs Star (10 nodes)
        (
            [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9]],
            [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5], [0, 6], [0, 7], [0, 8], [0, 9]]
        ),

        # Test 6: Star (8 nodes) vs balanced-ish (8 nodes)
        (
            [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5], [0, 6], [0, 7]],
            [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6], [6, 7]]
        ),

        # Test 7: Random tree (12 nodes) vs small chain (5 nodes)
        (
            [[0, 1], [1, 2], [1, 3], [3, 4], [2, 5], [5, 6], [0, 7], [7, 8], [8, 9], [9, 10], [10, 11]],
            [[0, 1], [1, 2], [2, 3], [3, 4]]
        ),

        # Test 8: Two different random trees (6 nodes)
        (
            [[0, 1], [1, 2], [1, 3], [3, 4], [4, 5]],
            [[0, 2], [2, 3], [3, 1], [1, 4], [4, 5]]
        ),

        # Test 9: Balanced (15 nodes) vs random (15 nodes)
        (
            [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6],
             [3, 7], [3, 8], [4, 9], [4, 10], [5, 11], [5, 12], [6, 13], [6, 14]],
            [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7],
             [3, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14]]
        ),

        # Test 10: Irregular (16 nodes) vs branching (16 nodes)
        (
            [[0, 1], [1, 2], [2, 3], [3, 4], [1, 5], [5, 6], [6, 7],
             [0, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15]],
            [[0, 1], [0, 2], [0, 3], [3, 4], [3, 5], [5, 6], [5, 7],
             [2, 8], [2, 9], [9, 10], [10, 11], [10, 12], [1, 13], [13, 14], [14, 15]]
        ),
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxTargetNodes(*test)
        else:
            sol.maxTargetNodes(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxTargetNodes(*test)
            else:
                result = sol.maxTargetNodes(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()