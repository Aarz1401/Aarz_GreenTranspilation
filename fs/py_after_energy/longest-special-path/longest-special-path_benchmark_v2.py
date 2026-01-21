
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


if __name__ == "__main__":
    tests = []
    
    # Test 1: Single node
    tests.append({
        'edges': [],
        'nums': [5]
    })
    
    # Test 2: Two nodes, simple edge
    tests.append({
        'edges': [[0, 1, 3]],
        'nums': [1, 2]
    })
    
    # Test 3: Three nodes, star centered at 0
    tests.append({
        'edges': [[0, 1, 4], [0, 2, 7]],
        'nums': [2, 3, 1]
    })
    
    # Test 4: Four nodes in a path, unit weights
    tests.append({
        'edges': [[0, 1, 1], [1, 2, 1], [2, 3, 1]],
        'nums': [1, 2, 3, 4]
    })
    
    # Test 5: Five nodes, include zero-weight edge
    tests.append({
        'edges': [[0, 1, 0], [1, 2, 5], [1, 3, 2], [3, 4, 3]],
        'nums': [5, 4, 5, 6, 7]
    })
    
    # Test 6: Six nodes, balanced branching
    tests.append({
        'edges': [[0, 1, 2], [0, 2, 3], [1, 3, 4], [1, 4, 1], [2, 5, 6]],
        'nums': [3, 4, 5, 6, 4, 5]
    })
    
    # Test 7: Seven nodes, mixed large weights
    tests.append({
        'edges': [[0, 1, 10], [1, 2, 20], [2, 3, 30], [1, 4, 40], [4, 5, 50], [4, 6, 60]],
        'nums': [7, 6, 5, 4, 3, 2, 1]
    })
    
    # Test 8: Eight nodes, multiple zero-weight edges
    tests.append({
        'edges': [[0, 1, 0], [0, 2, 0], [1, 3, 1], [1, 4, 0], [2, 5, 2], [2, 6, 0], [6, 7, 3]],
        'nums': [1, 1, 2, 3, 3, 4, 5, 6]
    })
    
    # Test 9: Nine nodes, heavier weights
    tests.append({
        'edges': [[0, 1, 1000], [0, 2, 2000], [1, 3, 1500], [1, 4, 500], [2, 5, 2500], [2, 6, 3500], [6, 7, 4500], [6, 8, 5500]],
        'nums': [10, 11, 12, 13, 9, 8, 7, 6, 5]
    })
    
    # Test 10: Ten nodes, varied structure
    tests.append({
        'edges': [[0, 1, 5], [0, 2, 3], [1, 3, 2], [1, 4, 4], [2, 5, 6], [2, 6, 1], [5, 7, 2], [6, 8, 3], [8, 9, 4]],
        'nums': [2, 3, 4, 5, 3, 4, 5, 6, 7, 8]
    })
    
    sol = Solution()
    
    iterations = 1000
    #sink = None
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            res = sol.longestSpecialPath(t['edges'], t['nums'])
        #     checksum += res[0]
        #     checksum ^= (res[1] << 1)
        # sink = checksum
    # print sink
