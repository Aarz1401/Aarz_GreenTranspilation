# Time:  O(n)
# Space: O(k)

from collections import deque


class Solution(object):
    def maxSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        result, dq = [], deque()
        for i in xrange(len(nums)):
            if dq and i-dq[0] == k:
                dq.popleft()
            while dq and nums[dq[-1]] <= nums[i]:
                dq.pop()
            dq.append(i)
            if i >= k-1:
                result.append(nums[dq[0]])
        return result


if __name__ == "__main__":
    import time

    # Constants for 32-bit int limits
    INT_MIN = -2147483648
    INT_MAX = 2147483647

    # Mersenne Twister MT19937 implementation (32-bit)
    class MT19937(object):
        def __init__(self, seed):
            self.w, self.n, self.m, self.r = 32, 624, 397, 31
            self.a = 0x9908B0DF
            self.u, self.d = 11, 0xFFFFFFFF
            self.s, self.b = 7, 0x9D2C5680
            self.t, self.c = 15, 0xEFC60000
            self.l = 18
            self.f = 1812433253

            self.lower_mask = (1 << self.r) - 1
            self.upper_mask = (0xFFFFFFFF) ^ self.lower_mask

            self.MT = [0] * self.n
            self.index = self.n
            self.seed(seed)

        def seed(self, seed):
            self.index = self.n
            self.MT[0] = seed & 0xFFFFFFFF
            for i in range(1, self.n):
                x = self.MT[i - 1] ^ (self.MT[i - 1] >> 30)
                self.MT[i] = (self.f * x + i) & 0xFFFFFFFF

        def twist(self):
            for i in range(self.n):
                x = (self.MT[i] & self.upper_mask) + (self.MT[(i + 1) % self.n] & self.lower_mask)
                xA = (x >> 1) & 0xFFFFFFFF
                if x & 1:
                    xA ^= self.a
                self.MT[i] = (self.MT[(i + self.m) % self.n] ^ xA) & 0xFFFFFFFF
            self.index = 0

        def rand_uint32(self):
            if self.index >= self.n:
                self.twist()
            y = self.MT[self.index]
            self.index += 1

            y ^= ((y >> self.u) & self.d)
            y ^= ((y << self.s) & self.b)
            y ^= ((y << self.t) & self.c)
            y ^= (y >> self.l)
            return y & 0xFFFFFFFF

    def uniform_int_distribution(mt, a, b):
        # Inclusive range [a, b]
        if a > b:
            a, b = b, a
        k = (b - a + 1)
        r = 1 << 32  # range of mt19937 output (0..2^32-1)
        if k <= 0:
            # Should not happen for given test cases
            return a
        # Rejection sampling to avoid modulo bias
        t = (r // k) * k
        while True:
            u = mt.rand_uint32()
            if u < t:
                return a + (u % k)

    # Test case generation

    # Fixed inputs
    t1 = [1, 2, 3, 4, 5]
    k1 = 3

    t2 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
    k2 = 4

    t3 = [7, 7, 7, 7, 7, 7, 7, 7]
    k3 = 5

    t4 = [1, 100, 2, 99, 3, 98, 4, 97, 5, 96, 6, 95]
    k4 = 3

    t5 = [INT_MIN, -1, INT_MAX, 0, INT_MIN + 1, INT_MAX - 1]
    k5 = 2

    # Random but deterministic inputs
    rng = MT19937(123456)
    def dist_small():
        return uniform_int_distribution(rng, -1000, 1000)

    def dist_large():
        return uniform_int_distribution(rng, -1000000, 1000000)

    t6 = [dist_small() for _ in range(10)]
    k6 = 1

    t7 = [i - 10 for i in range(20)]
    k7 = 20

    t8 = [3, 1, 4, 1, 5]
    k8 = 10  # k > n

    t9 = []
    k9 = 3

    t10 = [dist_large() for _ in range(5000)]
    k10 = 128

    sol = Solution()
    MOD64 = 1 << 64
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        r1 = sol.maxSlidingWindow(t1, k1)
        for v in r1:
            checksum = (checksum + (v % MOD64)) % MOD64

        r2 = sol.maxSlidingWindow(t2, k2)
        for v in r2:
            checksum = (checksum + (v % MOD64)) % MOD64

        r3 = sol.maxSlidingWindow(t3, k3)
        for v in r3:
            checksum = (checksum + (v % MOD64)) % MOD64

        r4 = sol.maxSlidingWindow(t4, k4)
        for v in r4:
            checksum = (checksum + (v % MOD64)) % MOD64

        r5 = sol.maxSlidingWindow(t5, k5)
        for v in r5:
            checksum = (checksum + (v % MOD64)) % MOD64

        r6 = sol.maxSlidingWindow(t6, k6)
        for v in r6:
            checksum = (checksum + (v % MOD64)) % MOD64

        r7 = sol.maxSlidingWindow(t7, k7)
        for v in r7:
            checksum = (checksum + (v % MOD64)) % MOD64

        r8 = sol.maxSlidingWindow(t8, k8)
        for v in r8:
            checksum = (checksum + (v % MOD64)) % MOD64

        r9 = sol.maxSlidingWindow(t9, k9)
        for v in r9:
            checksum = (checksum + (v % MOD64)) % MOD64

        r10 = sol.maxSlidingWindow(t10, k10)
        for v in r10:
            checksum = (checksum + (v % MOD64)) % MOD64

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us