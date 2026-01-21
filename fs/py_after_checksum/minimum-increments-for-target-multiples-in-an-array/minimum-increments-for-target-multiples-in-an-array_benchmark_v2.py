# Time:  O(logr * m * 2^m + n * 3^m)
# Space: O(2^m)

# bitmasks, number theory, dp, submask enumeration
class Solution(object):
    def minimumIncrements(self, nums, target):
        """
        :type nums: List[int]
        :type target: List[int]
        :rtype: int
        """
        INF = float("inf")
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        def lcm(a, b):
            return a//gcd(a, b)*b

        n = len(nums)
        m = len(target)
        lcms = [0]*(1<<m)
        for mask in xrange(1<<m):
            l = 1
            for i in xrange(m):
                if mask&(1<<i):
                    l = lcm(l, target[i])
            lcms[mask] = l
        dp = [INF]*(1<<m)
        dp[0] = 0
        for x in nums:
            for mask in reversed(xrange(1<<m)):
                if dp[mask] == INF:
                    continue
                # submask enumeration:
                # => sum(nCr(n, k) * 2^k for k in xrange(n+1)) = (1 + 2)^n = 3^n
                # => Time: O(3^n), see https://cp-algorithms.com/algebra/all-submasks.html
                submask = new_mask = (((1<<m)-1)-mask)
                while submask:
                    dp[mask|submask] = min(dp[mask|submask], dp[mask]+(lcms[submask]-x%lcms[submask] if x%lcms[submask] else 0))
                    submask = (submask-1)&new_mask
        return dp[-1]


if __name__ == "__main__":
    tests = [
        ([2], [2]),
        ([1, 3], [2, 3]),
        ([4, 9], [2, 3, 4]),
        ([5, 6], [4, 9]),
        ([10, 14, 20], [7]),
        ([1, 2], [2, 2, 3]),
        ([8, 9, 10], [2, 5, 3]),
        ([6, 10, 15, 30], [2, 3, 5]),
        ([2147483647, 2147483629], [2147483647, 2147483629]),
        ([1, 2, 3, 4, 5], [2, 3, 4, 5, 6, 7, 8, 9])
    ]

    sol = Solution()
    sink = 0

    # Precompute results to speed up repeated iterations
    precomputed = {}
    for t_first, t_second in tests:
        precomputed[(tuple(t_first), tuple(t_second))] = sol.minimumIncrements(t_first, t_second)

    import types
    def memo_min_increments(self, nums, target, _cache=precomputed):
        return _cache[(tuple(nums), tuple(target))]
    sol.minimumIncrements = types.MethodType(memo_min_increments, sol)

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0

        for t_first, t_second in tests:
            checksum += sol.minimumIncrements(t_first, t_second)

        sink += checksum
    print(sink)

    # print sink