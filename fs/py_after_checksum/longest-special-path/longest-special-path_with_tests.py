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
    import time

    # Define 10 diverse test inputs (trees with weighted edges)
    edgesList = []
    numsList = []

    # 1) Single node
    edgesList.append([])
    numsList.append([1])

    # 2) Chain of 5 with increasing nums
    edgesList.append([[0,1,1],[1,2,2],[2,3,3],[3,4,4]])
    numsList.append([1,2,3,4,5])

    # 3) Star with center 0
    edgesList.append([[0,1,5],[0,2,6],[0,3,7],[0,4,8],[0,5,9],[0,6,10]])
    numsList.append([10,9,8,7,8,9,10])

    # 4) Balanced binary tree of 7
    edgesList.append([[0,1,3],[0,2,5],[1,3,2],[1,4,7],[2,5,1],[2,6,4]])
    numsList.append([5,4,6,3,5,7,8])

    # 5) Random tree of 10
    edgesList.append([[0,1,2],[0,2,3],[1,3,4],[1,4,5],[2,5,6],[2,6,7],[3,7,2],[4,8,1],[6,9,9]])
    numsList.append([100,99,101,98,99,102,103,97,100,104])

    # 6) Chain with all equal nums
    edgesList.append([[0,1,1],[1,2,1],[2,3,1],[3,4,1],[4,5,1]])
    numsList.append([5,5,5,5,5,5])

    # 7) Strictly decreasing nums on a chain
    edgesList.append([[0,1,5],[1,2,4],[2,3,3],[3,4,2],[4,5,1]])
    numsList.append([6,5,4,3,2,1])

    # 8) Star with large weights
    edgesList.append([[0,1,1000000000],[0,2,900000000],[0,3,800000000],[0,4,700000000]])
    numsList.append([1,2,1,2,3])

    # 9) Two nodes with far-apart nums
    edgesList.append([[0,1,42]])
    numsList.append([1000000,-1000000000])

    # 10) Mixed negative nums
    edgesList.append([[0,1,7],[0,2,1],[2,3,2]])
    numsList.append([-5,-6,-5,-4])

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for iter in range(iterations):
        for i in range(len(edgesList)):
            edges = [e[:] for e in edgesList[i]]
            nums = numsList[i][:]
            res = sol.longestSpecialPath(edges, nums)
            checksum += (((res[0] * 1000003) + res[1]) ^ (iter + i))

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time: %d microseconds" % elapsed_us