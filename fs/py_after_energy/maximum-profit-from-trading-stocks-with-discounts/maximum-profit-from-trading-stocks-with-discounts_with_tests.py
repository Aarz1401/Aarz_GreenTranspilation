# Time:  O(n * b)
# Space: O(n + b)

import collections


# iterative dfs, tree dp
class Solution(object):
    def maxProfit(self, n, present, future, hierarchy, budget):
        """
        :type n: int
        :type present: List[int]
        :type future: List[int]
        :type hierarchy: List[List[int]]
        :type budget: int
        :rtype: int
        """
        def iter_dfs():
            ret = []
            stk = [(1, (0, ret))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u, ret = args
                    ret[:] = [collections.defaultdict(int) for _ in xrange(2)]
                    ret[0][0] = ret[1][0] = 0
                    stk.append((4, (u, ret)))
                    stk.append((2, (u, 0, ret)))
                elif step == 2:
                    u, i, ret = args
                    if i == len(adj[u]):
                        continue
                    v = adj[u][i]
                    stk.append((2, (u, i+1, ret)))
                    new_ret = []
                    stk.append((3, (new_ret, ret)))
                    stk.append((1, (v, new_ret)))
                elif step == 3:
                    new_ret, ret = args
                    for i in xrange(2):
                        for j1, v1 in ret[i].items():
                            for j2, v2 in new_ret[i].iteritems():
                                if j1+j2 <= budget:
                                    ret[i][j1+j2] = max(ret[i][j1+j2], v1+v2)
                elif step == 4:
                    u, ret = args
                    new_ret = [collections.defaultdict(int) for _ in xrange(2)]
                    for i in xrange(2):
                        for j, v in ret[0].iteritems():
                            new_ret[i][j] = max(new_ret[i][j], v)
                        cost = present[u]>>i
                        if cost > budget:
                            continue
                        profit = future[u]-cost
                        for j, v in ret[1].iteritems():
                            if j+cost <= budget:
                                new_ret[i][j+cost] = max(new_ret[i][j+cost], v+profit)
                    ret[:] = new_ret
            return max(ret[0].itervalues())

        adj = [[] for _ in xrange(n)]
        for u, v in hierarchy:
            adj[u-1].append(v-1)
        return iter_dfs()


# Time:  O(n * b)
# Space: O(n + b)
import collections


# dfs, tree dp
class Solution2(object):
    def maxProfit(self, n, present, future, hierarchy, budget):
        """
        :type n: int
        :type present: List[int]
        :type future: List[int]
        :type hierarchy: List[List[int]]
        :type budget: int
        :rtype: int
        """
        def dfs(u):
            dp = [collections.defaultdict(int) for _ in xrange(2)]
            dp[0][0] = dp[1][0] = 0
            for v in adj[u]:
                new_dp = dfs(v)
                for i in xrange(2):
                    for j1, v1 in dp[i].items():
                        for j2, v2 in new_dp[i].iteritems():
                            if j1+j2 <= budget:
                                dp[i][j1+j2] = max(dp[i][j1+j2], v1+v2)
            result = [collections.defaultdict(int) for _ in xrange(2)]
            for i in xrange(2):
                for j, v in dp[0].iteritems():
                    result[i][j] = max(result[i][j], v)
                cost = present[u]>>i
                if cost > budget:
                    continue
                profit = future[u]-cost
                for j, v in dp[1].iteritems():
                    if j+cost <= budget:
                        result[i][j+cost] = max(result[i][j+cost], v+profit)
            return result  # result[i][j]: max profit for budget j with i discount

        adj = [[] for _ in xrange(n)]
        for u, v in hierarchy:
            adj[u-1].append(v-1)
        return max(dfs(0)[0].itervalues())


if __name__ == "__main__":
    import time

    tests = []

    # 1) Single node
    tests.append({
        'n': 1,
        'present': [3],
        'future': [9],
        'hierarchy': [],
        'budget': 3
    })

    # 2) Chain of 5
    n = 5
    h = []
    for i in range(1, n):
        h.append([i, i + 1])
    tests.append({
        'n': n,
        'present': [1, 2, 3, 4, 5],
        'future': [2, 3, 7, 8, 12],
        'hierarchy': h,
        'budget': 7
    })

    # 3) Star with 1 as root
    n = 7
    h = []
    for i in range(2, n + 1):
        h.append([1, i])
    tests.append({
        'n': n,
        'present': [2, 2, 3, 3, 4, 5, 1],
        'future': [3, 5, 4, 6, 7, 7, 2],
        'hierarchy': h,
        'budget': 10
    })

    # 4) Balanced binary tree (7 nodes)
    n = 7
    h = [[1,2],[1,3],[2,4],[2,5],[3,6],[3,7]]
    tests.append({
        'n': n,
        'present': [5,4,4,3,2,6,1],
        'future': [9,7,5,5,4,7,4],
        'hierarchy': h,
        'budget': 12
    })

    # 5) Random tree 10 nodes
    n = 10
    h = [[1,2],[1,3],[2,4],[2,5],[3,6],[3,7],[4,8],[5,9],[7,10]]
    tests.append({
        'n': n,
        'present': [3,6,2,5,8,4,7,3,6,5],
        'future': [7,9,5,9,10,7,12,5,9,9],
        'hierarchy': h,
        'budget': 15
    })

    # 6) Zero budget (should select none)
    n = 6
    h = [[1,2],[2,3],[3,4],[4,5],[5,6]]
    tests.append({
        'n': n,
        'present': [5,4,3,6,7,8],
        'future': [6,5,5,8,9,10],
        'hierarchy': h,
        'budget': 0
    })

    # 7) Zero profit everywhere (future == present)
    n = 5
    h = [[1,2],[2,3],[3,4],[4,5]]
    tests.append({
        'n': n,
        'present': [2,3,4,5,6],
        'future': [2,3,4,5,6],
        'hierarchy': h,
        'budget': 20
    })

    # 8) Negative profits (future < present)
    n = 4
    h = [[1,2],[1,3],[1,4]]
    tests.append({
        'n': n,
        'present': [5,6,7,8],
        'future': [1,2,3,2],
        'hierarchy': h,
        'budget': 30
    })

    # 9) High budget to take many
    n = 8
    h = [[1,2],[1,3],[2,4],[2,5],[3,6],[3,7],[6,8]]
    tests.append({
        'n': n,
        'present': [2,3,4,5,6,7,3,2],
        'future': [6,7,8,9,10,12,6,4],
        'hierarchy': h,
        'budget': 100
    })

    # 10) Medium tree 12 nodes mixed
    n = 12
    h = [[1,2],[1,3],[2,4],[2,5],[3,6],[3,7],[4,8],[4,9],[5,10],[7,11],[7,12]]
    tests.append({
        'n': n,
        'present': [4,7,3,6,5,8,2,3,4,6,5,7],
        'future': [8,10,7,10,9,12,5,6,7,9,8,11],
        'hierarchy': h,
        'budget': 25
    })

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in range(iterations):
        for tc in tests:
            p = list(tc['present'])
            f = list(tc['future'])
            h = [list(edge) for edge in tc['hierarchy']]
            res = sol.maxProfit(tc['n'], p, f, h, tc['budget'])
            checksum += res

    end = time.time()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum:", checksum
    print "Elapsed (ns):", elapsed_ns