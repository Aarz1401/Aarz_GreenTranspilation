from bisect import bisect_left, bisect_right

# Time:  O(nlogn * logr), r = max(nums)
# Space: O(n + logr)

# number theory, suffix-gcd states, dp, binary search
class Solution(object):
    def maxGCDScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a
    
        lookup = [0]*len(nums)
        for i in xrange(len(nums)):
            while nums[i]&1 == 0:
                nums[i] >>= 1
                lookup[i] += 1
        lookup2 = [[] for _ in xrange(max(lookup)+1)]
        for i, e in enumerate(lookup):
            lookup2[e].append(i)
        result = 0
        dp = {}
        for i, x in enumerate(nums):
            new_dp = {}
            new_dp[x, lookup[i]] = [i]*2
            for (g, e), v in dp.iteritems():  # |g * e| = O(logr)
                ng = gcd(g, x)
                ne = min(e, lookup[i])
                if (ng, ne) not in new_dp:
                    new_dp[ng, ne] = [float("inf")]*2
                new_dp[ng, ne][0] = min(new_dp[ng, ne][0], v[0])
                left = bisect_left(lookup2[ne], v[0])  # Time: O(logn)
                right = bisect_right(lookup2[ne], i)-1  # Time: O(logn)
                new_dp[ng, ne][1] = min(new_dp[ng, ne][1], v[0] if right-left+1 <= k else lookup2[ne][right-k]+1)
            dp = new_dp
            for (g, e), v in dp.iteritems():  # |g * e| = O(logr)
                result = max(result, g*(i-v[0]+1)<<e, g*(i-v[1]+1)<<(e+1))
        return result


# Time:  O(n^2 + n * logr), r = max(nums)
# Space: O(1)
# number theory, brute force
class Solution2(object):
    def maxGCDScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        def lower_bit(x):
            return x&-x

        result = 0
        for i in xrange(len(nums)):
            mn = float("inf")
            g = cnt = 0
            for j in xrange(i, len(nums)):
                g = gcd(g, nums[j])
                bit = lower_bit(nums[j])
                if bit < mn:
                    mn = bit
                    cnt = 0
                if bit == mn:
                    cnt += 1
                result = max(result, g*(j-i+1)*(2 if cnt <= k else 1))
                if g*(len(nums)-i)*2 <= result:
                    break
        return result

if __name__ == "__main__":
    import time

    # Generate 10 diverse test inputs
    tests = []
    ks = []

    # 0: Empty array
    tests.append([])
    ks.append(0)

    # 1: Single element
    tests.append([1])
    ks.append(0)

    # 2: Small odds
    tests.append([3, 5, 7, 9, 11, 13, 15, 17])
    ks.append(1)

    # 3: Powers of two
    v = []
    for i in xrange(1, 16 + 1):
        v.append(1 << i)
    tests.append(v)
    ks.append(4)

    # 4: Mixed even composites
    tests.append([6, 10, 14, 22, 26, 30, 42, 60, 84, 98, 126, 150, 210, 330, 510, 1022])
    ks.append(3)

    # 5: Repeated elements with same 2-exponent
    v = [12] * 24  # 12 = 3 * 2^2
    tests.append(v)
    ks.append(2)

    # 6: Sequential numbers
    v = []
    for i in xrange(1, 40 + 1):
        v.append(i)
    tests.append(v)
    ks.append(5)

    # 7: Deterministic pseudo-random with variable 2-exponent
    v = []
    for i in xrange(1, 64 + 1):
        val = (i * 97) ^ (i * 131)
        base = int(val % 1000000) + 1
        base <<= (i % 3)
        v.append(base)
    tests.append(v)
    ks.append(0)

    # 8: Primes (including 2)
    tests.append([2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71])
    ks.append(2)

    # 9: Larger structured array with varying 2-exponents
    v = []
    for i in xrange(1, 96 + 1):
        val = (i + 1) * (i % 7 + 1) * (1 << (i % 5)) + (i % 3)
        if val <= 0:
            val = i + 1
        v.append(val)
    tests.append(v)
    ks.append(7)

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        # Run all test cases each iteration
        for t in xrange(len(tests)):
            nums = list(tests[t])  # copy because function mutates nums
            if len(nums) == 0:
                checksum += 0
            else:
                checksum += sol.maxGCDScore(nums, ks[t])
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms