
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
        :type nums: List[int]
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
    import sys
    import time

    tests = []

    # Test 1: Empty tree
    tests.append({'edges': [], 'nums': [], 'k': 1})

    # Test 2: Single node
    tests.append({'edges': [], 'nums': [5], 'k': 1})

    # Test 3: Two nodes
    tests.append({'edges': [(0, 1)], 'nums': [1, -1], 'k': 1})

    # Test 4: Chain of 5 nodes
    t_edges = []
    n = 5
    for i in range(1, n):
        t_edges.append((i - 1, i))
    t_nums = [1, 2, 3, 4, 5]
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 2})

    # Test 5: Star tree with 6 nodes (0 center)
    t_edges = []
    n = 6
    for i in range(1, n):
        t_edges.append((0, i))
    t_nums = [-1, -2, -3, -4, -5, -6]
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 3})

    # Test 6: Balanced binary tree (7 nodes)
    t_edges = []
    n = 7
    for i in range(1, n):
        t_edges.append(((i - 1) // 2, i))
    t_nums = [3, -1, 4, -5, 2, 0, 7]
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 2})

    # Test 7: Custom shaped tree (10 nodes) with mixed values including large
    t_edges = [
        (0, 1), (1, 2), (1, 3), (3, 4), (0, 5), (5, 6), (6, 7), (6, 8), (8, 9)
    ]
    t_nums = [10, -20, 35, -40, 15, 0, 7, 8, -9, 1000000000]
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 4})

    # Test 8: Longer chain (50 nodes) with alternating signs
    t_edges = []
    n = 50
    for i in range(1, n):
        t_edges.append((i - 1, i))
    t_nums = [0] * n
    for i in range(n):
        t_nums[i] = i * 2 if (i % 2 == 0) else (-i)
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 10})

    # Test 9: Random-like tree (100 nodes) with pseudo-random values
    t_edges = []
    n = 100
    seed = [88172645463393265]
    mask = (1 << 64) - 1
    mul = 6364136223846793005

    def nextRand():
        seed[0] = (seed[0] * mul + 1) & mask
        return seed[0]

    for i in range(1, n):
        p = int(nextRand() % i)
        t_edges.append((p, i))
    t_nums = [0] * n
    for i in range(n):
        val = int(nextRand() % 2000001) - 1000000
        t_nums[i] = int(val)
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 7})

    # Test 10: Perfect binary tree (31 nodes) with alternating pattern
    t_edges = []
    n = 31
    for i in range(1, n):
        t_edges.append(((i - 1) // 2, i))
    t_nums = [0] * n
    for i in range(n):
        t_nums[i] = i if (i % 3 == 0) else (-(i % 11))
    tests.append({'edges': t_edges, 'nums': t_nums, 'k': 5})

    # Ensure exactly 10 tests
    if len(tests) != 10:
        print "Failed to prepare 10 tests"
        sys.exit(1)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in range(iterations):
        for t in tests:
            # Handle empty input to avoid indexing errors in solution
            if not t['nums']:
                res = 0
            else:
                res = sol.subtreeInversionSum(t['edges'], t['nums'], t['k'])
            checksum += res

    end = time.time()

    elapsed_ms = int((end - start) * 1000.0)

    print "Checksum: {}".format(checksum)
    print "Elapsed time (ms): {}".format(elapsed_ms)
