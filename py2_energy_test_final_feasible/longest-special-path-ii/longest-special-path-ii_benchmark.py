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
            stk = [(1, (0, -1, 0, [-1]*2))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u, p, d, left = args
                    prev_d, lookup[nums[u]-1] = lookup[nums[u]-1], d
                    new_left = left[:]
                    curr = prev_d
                    for i in xrange(len(new_left)):
                        if curr > new_left[i]:
                            curr, new_left[i] = new_left[i], curr
                    result = min(result, [-(prefix[(d-1)+1]-prefix[new_left[1]+1]), d-new_left[1]])
                    stk.append((4, (u, prev_d)))
                    stk.append((2, (u, p, d, new_left, 0)))
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
# Space: O(h)
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
            new_left = left[:]
            curr = prev_d
            for i in xrange(len(new_left)):
                if curr > new_left[i]:
                    curr, new_left[i] = new_left[i], curr
            result[0] = min(result[0], [-(prefix[(d-1)+1]-prefix[new_left[1]+1]), d-new_left[1]])
            for v, l in adj[u]:
                if v == p:
                    continue
                prefix.append(prefix[-1]+l)
                dfs(v, u, d+1, new_left)
                prefix.pop()
            lookup[nums[u]-1] = prev_d
    
        adj = [[] for _ in xrange(len(nums))]
        for u, v, l in edges:
            adj[u].append((v, l))
            adj[v].append((u, l))
        lookup = collections.defaultdict(lambda: -1)
        prefix = [0]
        result = [[float("inf"), float("inf")]]
        dfs(0, -1, 0, [-1]*2)
        return [-result[0][0], result[0][1]]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Single node
        ([], [1]),

        # 2) Line of 3 nodes with increasing weights and nums
        (
            [
                [0, 1, 2],
                [1, 2, 3]
            ],
            [1, 2, 3]
        ),

        # 3) Star tree with duplicates in nums
        (
            [
                [0, 1, 1],
                [0, 2, 2],
                [0, 3, 3],
                [0, 4, 4]
            ],
            [1, 1, 2, 2, 3]
        ),

        # 4) Balanced binary tree
        (
            [
                [0, 1, 3],
                [0, 2, 5],
                [1, 3, 2],
                [1, 4, 4],
                [2, 5, 6],
                [2, 6, 1]
            ],
            [2, 3, 2, 1, 3, 1, 2]
        ),

        # 5) Random small tree
        (
            [
                [0, 1, 7],
                [1, 2, 1],
                [1, 3, 8],
                [3, 4, 2],
                [2, 5, 9]
            ],
            [5, 1, 5, 2, 3, 2]
        ),

        # 6) Zero weights line
        (
            [
                [0, 1, 0],
                [1, 2, 0],
                [2, 3, 0]
            ],
            [1, 2, 1, 2]
        ),

        # 7) Very large weights
        (
            [
                [0, 1, 1000000000],
                [1, 2, 1000000000],
                [1, 3, 1000000000]
            ],
            [10, 9, 8, 7]
        ),

        # 8) Chain of 10 nodes
        (
            [
                [0, 1, 1],
                [1, 2, 2],
                [2, 3, 3],
                [3, 4, 4],
                [4, 5, 5],
                [5, 6, 6],
                [6, 7, 7],
                [7, 8, 8],
                [8, 9, 9]
            ],
            [1, 2, 1, 2, 1, 2, 1, 2, 1, 2]
        ),

        # 9) All nums identical
        (
            [
                [0, 1, 3],
                [1, 2, 3],
                [2, 3, 3],
                [3, 4, 3]
            ],
            [7, 7, 7, 7, 7]
        ),

        # 10) Negative and zero nums in a star
        (
            [
                [0, 1, 2],
                [0, 2, 2],
                [0, 3, 2],
                [0, 4, 2],
                [0, 5, 2]
            ],
            [0, -1, -1, 0, -5, 0]
        ),
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