# Time:  O(n)
# Space: O(n)

# iterative dfs, tree dp
class Solution(object):
    def subtreeInversionSum(self, edges, nums, k):
        """
        :type edges: List[List[int]]
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def iter_dfs():
            dp = []
            ret = [0]*3
            stk = [(1, (0, -1, ret))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u, p, ret = args
                    dp.append([0]*2)
                    ret[:] = [nums[u], 0, 0]
                    stk.append((4, (u, p, ret)))
                    stk.append((2, (u, p, ret, 0)))
                elif step == 2:
                    u, p, ret, i = args
                    if i == len(adj[u]):
                        continue
                    v = adj[u][i]
                    stk.append((2, (u, p, ret, i+1)))
                    if v == p:
                        continue
                    new_ret = [0]*3
                    stk.append((3, (u, p, new_ret, ret, i)))
                    stk.append((1, (v, u, new_ret)))
                elif step == 3:
                    u, p, new_ret, ret, i = args
                    ret[0] += new_ret[0]
                    ret[1] += new_ret[1]
                    ret[2] += new_ret[2]
                elif step == 4:
                    u, p, ret = args
                    ret[1] = max(ret[1], dp[-1][1]-2*ret[0])
                    ret[2] = max(ret[2], dp[-1][0]+2*ret[0])
                    dp.pop()
                    if len(dp)-k >= 0:
                        dp[len(dp)-k][0] += ret[1]
                        dp[len(dp)-k][1] += ret[2]
            return ret[0]+ret[1]

        adj = [[] for _ in xrange(len(nums))]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        return iter_dfs()


# Time:  O(n)
# Space: O(n)
# dfs, tree dp
class Solution2(object):
    def subtreeInversionSum(self, edges, nums, k):
        """
        :type edges: List[List[int]]
        :type nums: List[int]]
        :type k: int
        :rtype: int
        """
        def dfs(u, p):
            dp.append([0]*2)
            total, pos, neg = nums[u], 0, 0
            for v in adj[u]:
                if v == p:
                    continue
                new_total, new_pos, new_neg = dfs(v, u)
                total += new_total
                pos += new_pos
                neg += new_neg
            pos = max(pos, dp[-1][1]-2*total)
            neg = max(neg, dp[-1][0]+2*total)
            dp.pop()
            if len(dp)-k >= 0:
                dp[len(dp)-k][0] += pos
                dp[len(dp)-k][1] += neg
            return total, pos, neg

        adj = [[] for _ in xrange(len(nums))]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        dp = []
        total, pos, neg = dfs(0, -1)
        return total+pos


if __name__ == "__main__":
    tests = [
        ([], [7], 1),
        ([[0,1],[1,2],[2,3],[3,4]], [3,-1,4,-2,1], 1),
        ([[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], [-5,-4,-3,2,1,0,7], 2),
        ([[0,1],[0,2],[0,3],[0,4],[0,5]], [10,-10,5,-5,2,-2], 3),
        ([[0,1],[1,2],[1,3],[3,4],[3,5],[5,6],[6,7]], [1,2,3,4,5,6,7,8], 2),
        ([[0,1],[0,2],[2,3],[2,4],[4,5],[4,6],[1,7],[7,8],[8,9]], [0,-1,-2,-3,0,3,2,1,-4,5], 4),
        ([[0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[3,7],[3,8],[4,9],[4,10],[5,11],[5,12],[6,13],[6,14]], [-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7], 5),
        ([[0,1],[1,2],[2,3],[2,4],[4,5],[5,6],[3,7],[7,8]], [100,200,300,400,500,600,700,800,900], 3),
        ([[0,1],[1,2],[1,3]], [-1000,0,1000,-500], 1),
        ([[0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[4,7],[4,8],[6,9],[9,10],[10,11]], [5,-3,8,-2,7,0,-1,4,-4,6,-6,2], 6),
    ]

    solver = Solution()
    sink = 0
    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for t in tests:
            edges, nums, k = t
            r = solver.subtreeInversionSum(edges, nums, k)
            checksum += int(r)
        sink += checksum
    print(sink)
    # print sink