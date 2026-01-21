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
    from time import time

    # Define 10 diverse test inputs
    tests = []

    tests.append(([1], [1]))                                               # Case 1: trivial
    tests.append(([2, 3, 4], [2, 3]))                                      # Case 2: small mix
    tests.append(([5, 7, 11], [6, 10, 15]))                                # Case 3: co-prime targets
    tests.append(([8, 16, 24, 40], [4, 8, 2, 4]))                          # Case 4: duplicates in target
    tests.append(([1000000000, 999999937, 500000003], [97, 89, 83, 79]))   # Case 5: large numbers/primes
    tests.append(([12, 18, 30, 42, 60], [6, 12, 18, 24, 30]))              # Case 6: increasing multiples
    tests.append(([1,2,3,4,5,6,7,8,9,10], [2,3,5,7,11]))                   # Case 7: more nums, 5 targets
    tests.append(([0, 0, 0], [0, 1, 2]))                                   # Case 8: includes zeroes
    tests.append(([123, 456, 789, 101112], [9, 12, 27, 36]))               # Case 9: composite targets
    tests.append(([13, 26, 39, 52, 65, 78], [13, 26, 52, 104]))            # Case 10: powers/multiples

    sol = Solution()
    checksum = 0

    start = time()

    iterations = 1
    for _ in xrange(iterations):
        for nums, target in tests:
            try:
                checksum += sol.minimumIncrements(nums, target)
            except Exception:
                pass

    end = time()
    elapsed_us = int(round((end - start) * 1000000))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us