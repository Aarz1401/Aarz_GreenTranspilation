# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Prepare dynamic parts from C++ test 9
    edges9 = []
    for i in xrange(1, 15):
        edges9.append([(i - 1) / 2, i])
    nums9 = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8]

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([], [5], 1),
        ([[0, 1]], [1, -1], 1),
        ([[0, 1], [1, 2], [2, 3], [3, 4]], [1, 2, 3, 4, 5], 2),
        ([[0, 1], [0, 2], [0, 3], [0, 4], [0, 5]], [-1, 0, 1, -2, 2, 3], 3),
        ([[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6]], [3, -2, 5, 1, -4, 2, 0], 2),
        ([[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [6, 9]],
         [1000000, -2000000, 1500000, -1500000, 500000, -500000, 3000000, -1000000, 2000000, -2500000], 4),
        ([[0, 1], [1, 2], [1, 3], [3, 4], [4, 5], [5, 6], [2, 7]], [-5, -3, -2, 0, -1, -4, -6, -7], 3),
        ([[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6]], [100, -100, 200, -200, 300, -300, 400], 1),
        (edges9, nums9, 5),
        ([[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [1, 10], [10, 11]],
         [9, -8, 7, -6, 5, -4, 3, -2, 1, 0, 2, -1], 6),
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.subtreeInversionSum(*test)
        else:
            sol.subtreeInversionSum(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.subtreeInversionSum(*test)
            else:
                result = sol.subtreeInversionSum(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()