# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n + e)
# Space: O(n + e)

import collections


# iterative dfs, two pointers, sliding window, prefix sum
class Solution(object):
    def longestSpecialPath(self, edges, nums):
        """
        :type edges: List[List[int]]
        :type nums: List[int]
        :rtype: List[int]
        """
        def iter_dfs():
            result = [float("inf")]*2
            lookup = collections.defaultdict(lambda: -1)
            prefix = [0]
            stk = [(1, (0, -1, 0, -1))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u, p, d, left = args
                    prev_d, lookup[nums[u]-1] = lookup[nums[u]-1], d
                    left = max(left, prev_d)
                    result = min(result, [-(prefix[(d-1)+1]-prefix[left+1]), d-left])
                    stk.append((4, (u, prev_d)))
                    stk.append((2, (u, p, d, left, 0)))
                elif step == 2:
                    u, p, d, left, i = args
                    if i == len(adj[u]):
                        continue
                    stk.append((2, (u, p, d, left, i+1)))
                    v, l = adj[u][i]
                    if v == p:
                        continue
                    prefix.append(prefix[-1]+l)
                    stk.append((3, None))
                    stk.append((1, (v, u, d+1, left)))
                elif step == 3:
                    prefix.pop()
                elif step == 4:
                    u, prev_d = args
                    lookup[nums[u]-1] = prev_d
            return [-result[0], result[1]]
    
        adj = [[] for _ in xrange(len(nums))]
        for u, v, l in edges:
            adj[u].append((v, l))
            adj[v].append((u, l))        
        return iter_dfs()


# Time:  O(n + e)
# Space: O(n + e)
import collections


# dfs, two pointers, sliding window, prefix sum
class Solution2(object):
    def longestSpecialPath(self, edges, nums):
        """
        :type edges: List[List[int]]
        :type nums: List[int]
        :rtype: List[int]
        """
        def dfs(u, p, d, left):
            prev_d, lookup[nums[u]-1] = lookup[nums[u]-1], d
            left = max(left, prev_d)
            result[0] = min(result[0], [-(prefix[(d-1)+1]-prefix[left+1]), d-left])
            for v, l in adj[u]:
                if v == p:
                    continue
                prefix.append(prefix[-1]+l)
                dfs(v, u, d+1, left)
                prefix.pop()
            lookup[nums[u]-1] = prev_d
    
        adj = [[] for _ in xrange(len(nums))]
        for u, v, l in edges:
            adj[u].append((v, l))
            adj[v].append((u, l))
        lookup = collections.defaultdict(lambda: -1)
        prefix = [0]
        result = [[float("inf"), float("inf")]]
        dfs(0, -1, 0, -1)
        return [-result[0][0], result[0][1]]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([], [1]),
        ([[0, 1, 5]], [1, 2]),
        ([[0, 1, 1], [1, 2, 2], [2, 3, 3], [3, 4, 4]], [1, 2, 3, 4, 5]),
        ([[0, 1, 1], [0, 2, 2], [0, 3, 3], [0, 4, 4], [0, 5, 5]], [2, 2, 2, 2, 2, 2]),
        ([[0, 1, 3], [0, 2, 1], [1, 3, 4], [1, 4, 2], [2, 5, 7], [2, 6, 6]], [3, 1, 2, 3, 2, 1, 3]),
        ([[0, 1, 0], [1, 2, 0], [2, 3, 0]], [5, 4, 5, 4]),
        ([[0, 1, 2], [1, 2, 5], [1, 3, 1], [3, 4, 3], [3, 5, 8], [2, 6, 1], [6, 7, 2], [6, 8, 4], [8, 9, 3]], [1, 3, 2, 3, 1, 2, 4, 4, 3, 5]),
        ([[0, 1, 100], [1, 2, 200], [1, 3, 150], [3, 4, 250], [3, 5, 50], [2, 6, 300], [6, 7, 400]], [8, 7, 6, 5, 4, 3, 2, 1]),
        ([[0, 1, 1], [1, 2, 2], [1, 3, 0], [3, 4, 5], [3, 5, 0], [2, 6, 7], [6, 7, 0], [6, 8, 9]], [1, 2, 1, 2, 1, 2, 1, 2, 1]),
        ([[0, 1, 1], [1, 2, 1], [2, 3, 1], [3, 4, 1], [4, 5, 1], [5, 6, 1], [6, 7, 1], [7, 8, 1], [8, 9, 1], [9, 10, 1], [10, 11, 1]], [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6]),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.longestSpecialPath(*test)
        else:
            sol.longestSpecialPath(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.longestSpecialPath(*test)
            else:
                result = sol.longestSpecialPath(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()