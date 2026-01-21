
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


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    nums_list = []
    edges_list = []

    # Test 1: Single node
    nums_list.append([1])
    edges_list.append([])

    # Test 2: Two nodes
    nums_list.append([1, 2])
    edges_list.append([[0, 1, 5]])

    # Test 3: Three-node chain
    nums_list.append([2, 1, 2])
    edges_list.append([[0, 1, 3], [1, 2, 4]])

    # Test 4: Star centered at 0
    nums_list.append([1, 1, 2, 2, 3])
    edges_list.append([[0, 1, 1], [0, 2, 2], [0, 3, 3], [0, 4, 4]])

    # Test 5: Balanced tree with varied weights
    nums_list.append([3, 1, 4, 1, 5, 9, 2])
    edges_list.append([[0, 1, 2], [0, 2, 3], [1, 3, 4], [1, 4, 5], [2, 5, 6], [2, 6, 7]])

    # Test 6: Random-ish tree, Fibonacci-like nums
    nums_list.append([7, 1, 1, 2, 3, 5, 8, 13])
    edges_list.append([[0, 1, 10], [1, 2, 20], [1, 3, 5], [3, 4, 8], [0, 5, 7], [5, 6, 3], [6, 7, 12]])

    # Test 7: Chain of 10 nodes with patterned nums
    nums_list.append([0, 0, 1, 1, 0, 2, 2, 3, 3, 0])
    e = []
    for k in xrange(1, 10):
        e.append([k - 1, k, k * 2 + 1])
    edges_list.append(e)

    # Test 8: Deeper tree with negatives and large nums
    nums_list.append([5, 4, 3, 2, 1, 0, -1, -2, -3, 100, 100, 100])
    edges_list.append([[0, 1, 1], [0, 2, 2], [2, 3, 3], [2, 4, 4], [4, 5, 5],
                       [1, 6, 6], [6, 7, 7], [6, 8, 8], [8, 9, 9], [9, 10, 10], [10, 11, 11]])

    # Test 9: Binary tree of 15 nodes
    nums9 = []
    for x in xrange(15):
        nums9.append(x % 5)
    nums_list.append(nums9)

    e9 = []
    for node in xrange(1, 15):
        parent = (node - 1) // 2
        e9.append([parent, node, node + 1])
    edges_list.append(e9)

    # Test 10: Multi-level branching
    nums_list.append([1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4])
    edges_list.append([
        [0, 1, 1], [0, 2, 2], [0, 3, 3], [0, 4, 4], [0, 5, 5],
        [5, 6, 6], [5, 7, 7], [5, 8, 8], [5, 9, 9], [5, 10, 10],
        [10, 11, 11], [10, 12, 12], [10, 13, 13],
        [13, 14, 14], [14, 15, 15], [14, 16, 16], [14, 17, 17],
        [17, 18, 18], [17, 19, 19]
    ])

    # Benchmark
    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for t in xrange(10):
            edges = [edge[:] for edge in edges_list[t]]
            nums = list(nums_list[t])
            res = sol.longestSpecialPath(edges, nums)
            A = int(res[0]) * 1000003
            B = int(res[1]) + t
            checksum += (A ^ B)
    end = time.time()

    ms = (end - start) * 1000.0
    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % ms
