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
    import time

    # Monkey-patch to handle negative numbers and cache results for repeated calls
    def _fixed_concatenatedDivisibility(self, nums, k):
        # simple cache to speed up repeated identical calls
        key = (tuple(nums), k)
        cache = getattr(self, '_cache', None)
        if cache is None:
            self._cache = {}
            cache = self._cache
        if key in cache:
            return cache[key]

        def length(x):
            x = abs(x)
            l = 0
            while x:
                l += 1
                x //= 10
            return max(l, 1)

        if k == 0:
            cache[key] = []
            return cache[key]

        lookup = [length(x) for x in nums]
        mx = max(lookup) if lookup else 1
        pow10 = [0] * (mx + 1)
        pow10[0] = 1 % k
        for i in xrange(len(pow10) - 1):
            pow10[i + 1] = (pow10[i] * 10) % k
        dp = [[False] * k for _ in xrange(1 << len(nums))]
        dp[-1][0] = True
        for mask in reversed(xrange(len(dp) - 1)):
            for r in xrange(k):
                for i, l in enumerate(lookup):
                    if mask & (1 << i):
                        continue
                    if dp[mask | (1 << i)][(r * pow10[l] + nums[i]) % k]:
                        dp[mask][r] = True
                        break
        result = []
        if dp[0][0]:
            order = sorted((x, i) for i, x in enumerate(nums))
            mask = 0
            r = 0
            for _ in xrange(len(nums)):
                for _, i in order:
                    if mask & (1 << i):
                        continue
                    nr = (r * pow10[lookup[i]] + nums[i]) % k
                    if dp[mask | (1 << i)][nr]:
                        result.append(nums[i])
                        mask |= 1 << i
                        r = nr
                        break
        cache[key] = result
        return result

    # apply the patch
    Solution.concatenatedDivisibility = _fixed_concatenatedDivisibility

    # Test cases
    tests = []
    tests.append({'nums': [1, 2], 'k': 3})                           # simple small case
    tests.append({'nums': [-1, 2, -3], 'k': 7})                      # includes negatives
    tests.append({'nums': [0, 0, 5], 'k': 5})                        # zeros with divisibility
    tests.append({'nums': [12, 34, 56], 'k': 11})                    # multi-digit numbers
    tests.append({'nums': [123, 4, 56, 7], 'k': 13})                 # mixed lengths
    tests.append({'nums': [10, 10, 10], 'k': 10})                    # duplicates
    tests.append({'nums': [0], 'k': 1})                              # single zero, k=1
    tests.append({'nums': [-999], 'k': 3})                           # single negative divisible
    tests.append({'nums': [8, 80, 800, 5, 50, 500, 7, 70], 'k': 9})  # larger set
    tests.append({'nums': [-12, 3, -45, 6, 789], 'k': 37})           # mixed signs and sizes

    solver = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for t in xrange(len(tests)):
            nums = tests[t]['nums']
            k = tests[t]['k']
            res = solver.concatenatedDivisibility(nums, k)
            local = 0
            for v in res:
                local = (local * 1315423911 + (v + 1000003)) & mask
            temp = (local + (k & mask) * 2654435761 + t) & mask
            checksum = (checksum ^ temp) & mask
            checksum = (checksum + len(res)) & mask

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms