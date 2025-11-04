# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n * (2^10)^2)
# Space: O(2^10)

import collections


# bitmasks, iterative dfs, tree dp
class Solution(object):
    def goodSubtreeSum(self, vals, par):
        """
        :type vals: List[int]
        :type par: List[int]
        :rtype: int
        """
        MOD = 10**9+7
        def get_mask(x):
            mask = 0
            while x:
                x, d = divmod(x, 10)
                if mask&(1<<d):
                    return -1
                mask |= 1<<d
            return mask

        def iter_dfs():
            result = 0
            ret = collections.defaultdict(int)
            stk = [(1, (0, ret))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u, ret = args
                    ret[0] = 0
                    mask = get_mask(vals[u])
                    if mask != -1:
                        ret[mask] = vals[u]
                    stk.append((4, (u, ret)))
                    stk.append((2, (u, 0, ret)))
                elif step == 2:
                    u, i, ret = args
                    if i == len(adj[u]):
                        continue
                    v = adj[u][i]
                    stk.append((2, (u, i+1, ret)))
                    new_ret = collections.defaultdict(int)
                    stk.append((3, (new_ret, ret)))
                    stk.append((1, (v, new_ret)))
                elif step == 3:
                    new_ret, ret = args
                    for m1, v1 in ret.items():
                        for m2, v2 in new_ret.iteritems():
                            if m1&m2:
                                continue
                            ret[m1|m2] =  max(ret[m1|m2], v1+v2)
                elif step == 4:
                    u, ret = args
                    result = (result+max(ret.itervalues()))%MOD
            return result

        adj = [[] for _ in xrange(len(vals))]
        for u in xrange(1, len(par)):
            adj[par[u]].append(u)
        return iter_dfs()


# Time:  O(n * (2^10)^2)
# Space: O(2^10)
import collections


# bitmasks, dfs, tree dp
class Solution2(object):
    def goodSubtreeSum(self, vals, par):
        """
        :type vals: List[int]
        :type par: List[int]
        :rtype: int
        """
        MOD = 10**9+7
        def get_mask(x):
            mask = 0
            while x:
                x, d = divmod(x, 10)
                if mask&(1<<d):
                    return -1
                mask |= 1<<d
            return mask

        def dfs(u):
            dp = collections.defaultdict(int)
            dp[0] = 0
            mask = get_mask(vals[u])
            if mask != -1:
                dp[mask] = vals[u]
            for v in adj[u]:
                new_dp = dfs(v)
                for m1, v1 in dp.items():
                    for m2, v2 in new_dp.iteritems():
                        if m1&m2:
                            continue
                        dp[m1|m2] =  max(dp[m1|m2], v1+v2)
            result[0] = (result[0]+max(dp.itervalues()))%MOD
            return dp

        adj = [[] for _ in xrange(len(vals))]
        for u in xrange(1, len(par)):
            adj[par[u]].append(u)
        result = [0]
        dfs(0)
        return result[0]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([0], [-1]),               # zero value
        ([5], [-1]),               # single-digit unique
        ([11], [-1]),              # repeated digit -> invalid mask
        ([101], [-1]),             # repeated digit '1' -> invalid mask
        ([1023456789], [-1]),      # 10 unique digits including 0
        ([123456789], [-1]),       # 9 unique digits
        ([1000000000], [-1]),      # repeated zero -> invalid mask
        ([222222], [-1]),          # repeated digit -> invalid mask
        ([13579], [-1]),           # unique odd digits
        ([24680], [-1]),           # unique even digits including 0
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.goodSubtreeSum(*test)
        else:
            sol.goodSubtreeSum(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.goodSubtreeSum(*test)
            else:
                result = sol.goodSubtreeSum(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()