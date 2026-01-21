# Time:  O(nlogr + k * n * 2^n)
# Space: O(logr + k * 2^n)

# dp, backtracing
class Solution(object):
    def concatenatedDivisibility(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        def length(x):
            l = 0
            while x:
                l += 1
                x //= 10
            return max(l, 1)

        lookup = [length(x) for x in nums]
        mx = max(lookup)
        pow10 = [0]*(mx+1)
        pow10[0] = 1%k
        for i in xrange(len(pow10)-1):
            pow10[i+1] = (pow10[i]*10)%k
        dp = [[False]*k for _ in xrange(1<<len(nums))]
        dp[-1][0] = True
        for mask in reversed(xrange(len(dp)-1)):
            for r in xrange(k):
                for i, l in enumerate(lookup):
                    if mask&(1<<i):
                        continue
                    if dp[mask|(1<<i)][(r*pow10[l]+nums[i])%k]:
                        dp[mask][r] = True
                        break
        result = []
        if not dp[0][0]:
            return result
        order = sorted((x, i) for i, x in enumerate(nums))
        mask = r = 0
        for _ in xrange(len(nums)):
            for _, i in order:
                if mask&(1<<i):
                    continue
                if dp[mask|(1<<i)][(r*pow10[lookup[i]]+nums[i])%k]:
                    result.append(nums[i])
                    mask |= 1<<i
                    r = (r*pow10[lookup[i]]+nums[i])%k
                    break
        return result


if __name__ == "__main__":
    tests = [
        {'nums': [1], 'k': 1},
        {'nums': [10, 2], 'k': 2},
        {'nums': [12, 34, 5], 'k': 3},
        {'nums': [0, 0, 5], 'k': 5},
        {'nums': [7, 70, 700], 'k': 7},
        {'nums': [3, 30, 34, 5, 9], 'k': 3},
        {'nums': [12, 45, 78], 'k': 9},
        {'nums': [2, 22, 222, 2222], 'k': 37},
        {'nums': [9, 99, 999, 9999], 'k': 9},
        {'nums': [1, 2, 12, 123, 1234], 'k': 97}
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for t in tests:
            res = sol.concatenatedDivisibility(t['nums'], t['k'])
            for x in res:
                checksum += x
            checksum += len(res)
        sink += checksum
    print(sink)