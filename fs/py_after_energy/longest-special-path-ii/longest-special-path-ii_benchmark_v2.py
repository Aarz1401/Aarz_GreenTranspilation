
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
    tests = []
    
    # Test 1: Single node
    tests.append({
        'edges': [],
        'nums': [5]
    })
    
    # Test 2: Two nodes, single edge
    tests.append({
        'edges': [[0, 1, 7]],
        'nums': [1, 1]
    })
    
    # Test 3: Path of 5 nodes
    tests.append({
        'edges': [[0, 1, 3], [1, 2, 4], [2, 3, 5], [3, 4, 6]],
        'nums': [2, 1, 2, 3, 1]
    })
    
    # Test 4: Star with center 0
    tests.append({
        'edges': [[0, 1, 10], [0, 2, 20], [0, 3, 30], [0, 4, 40], [0, 5, 50]],
        'nums': [1, 2, 3, 2, 1, 3]
    })
    
    # Test 5: Balanced binary tree (7 nodes)
    tests.append({
        'edges': [[0, 1, 2], [0, 2, 3], [1, 3, 4], [1, 4, 5], [2, 5, 6], [2, 6, 7]],
        'nums': [3, 1, 2, 3, 1, 2, 3]
    })
    
    # Test 6: Random tree (8 nodes)
    tests.append({
        'edges': [[0, 1, 5], [1, 2, 1], [1, 3, 9], [3, 4, 2], [3, 5, 8], [5, 6, 7], [2, 7, 4]],
        'nums': [4, 4, 2, 5, 1, 3, 2, 5]
    })
    
    # Test 7: Tree (10 nodes)
    tests.append({
        'edges': [[0, 1, 3], [0, 2, 4], [1, 3, 2], [1, 4, 6], [2, 5, 5], [2, 6, 1], [6, 7, 7], [4, 8, 9], [8, 9, 3]],
        'nums': [1, 3, 5, 7, 9, 2, 4, 6, 8, 10]
    })
    
    # Test 8: Larger tree (20 nodes)
    tests.append({
        'edges': [
            [0, 1, 1], [0, 2, 2], [1, 3, 3], [1, 4, 4], [2, 5, 5], [2, 6, 6],
            [3, 7, 7], [3, 8, 8], [4, 9, 9], [4, 10, 10], [5, 11, 11], [5, 12, 12],
            [6, 13, 13], [6, 14, 14], [7, 15, 15], [8, 16, 16], [9, 17, 17],
            [10, 18, 18], [11, 19, 19]
        ],
        'nums': [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2]
    })
    
    # Test 9: Star (15 nodes)
    e9 = []
    for v in range(1, 15):
        e9.append([0, v, 2 * v])
    tests.append({
        'edges': e9,
        'nums': [5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1]
    })
    
    # Test 10: Larger tree (30 nodes)
    tests.append({
        'edges': [
            [0, 1, 1], [0, 2, 2], [1, 3, 3], [1, 4, 4], [2, 5, 5], [2, 6, 6],
            [3, 7, 7], [3, 8, 8], [4, 9, 9], [4, 10, 10], [5, 11, 11], [5, 12, 12],
            [6, 13, 13], [6, 14, 14], [7, 15, 15], [7, 16, 16], [8, 17, 17], [8, 18, 18],
            [9, 19, 19], [9, 20, 20], [10, 21, 21], [10, 22, 22], [11, 23, 23], [12, 24, 24],
            [13, 25, 25], [14, 26, 26], [15, 27, 27], [16, 28, 28], [17, 29, 29]
        ],
        'nums': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
    })
    
    iterations = 1000
    for iter in xrange(iterations):
        checksum = 0
        sol = Solution()
        for t in xrange(10):
            res = sol.longestSpecialPath(tests[t]['edges'], tests[t]['nums'])
            if len(res) >= 2:
                checksum += res[0] + res[1]
        sink = checksum
    # print sink
