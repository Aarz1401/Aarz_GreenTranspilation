
# Time:  precompute: O(max_r^2 * log(max_r))
#        runtime:    O(n + r^2)
# Space: O(max_r^2)

# number theory, mobius function, principle of inclusion-exclusion
MOD = 10**9+7
MAX_NUM = 200
def gcd(a, b):
    while b:
        a, b = b, a%b
    return a

def lcm(a, b):
    return a//gcd(a, b)*b

POW2 = [1]*(MAX_NUM+1)  # Time: O(max_r)
for i in xrange(len(POW2)-1):
    POW2[i+1] = (POW2[i]*2)%MOD
POW3 = [1]*(MAX_NUM+1)
for i in xrange(len(POW3)-1):  # Time: O(max_r)
    POW3[i+1] = (POW3[i]*3)%MOD
LCM = [[0]*(MAX_NUM+1) for _ in xrange(MAX_NUM+1)]
for i in xrange(1, MAX_NUM+1):  # Time: O(max_r^2 * log(max_r))
    for j in xrange(i, MAX_NUM+1):
        LCM[i][j] = LCM[j][i] = lcm(i, j)
MU = [0]*(MAX_NUM+1)
MU[1] = 1
for i in xrange(1, MAX_NUM+1):  # Time: O(max_r * log(max_r))
    for j in xrange(i+i, MAX_NUM+1, i):
        MU[j] -= MU[i] 
class Solution(object):
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def count(g):
            return reduce(lambda accu, x: (accu+x)%MOD, (MU[i]*MU[j]*f[i*g][j*g] for i in xrange(1, mx//g+1) for j in xrange(1, mx//g+1)), 0)
            
        mx = max(nums)
        cnt = [0]*(mx+1)
        for x in nums:
            cnt[x] += 1
        for i in xrange(1, mx+1):
            for j in xrange(i+i, mx+1, i):
                cnt[i] += cnt[j]
        f = [[0]*(mx+1) for _ in xrange(mx+1)]
        for g1 in xrange(1, mx+1):
            for g2 in xrange(g1, mx+1):
                l = LCM[g1][g2]
                c = cnt[l] if l < len(cnt) else 0
                c1, c2 = cnt[g1], cnt[g2]
                f[g1][g2] = f[g2][g1] = (POW3[c]*POW2[(c1-c)+(c2-c)]-POW2[c1]-POW2[c2]+1)%MOD
        return reduce(lambda accu, x: (accu+x)%MOD, (count(g) for g in xrange(1, mx+1)), 0)  # Time: O(mx^2 * (1 + 1/4 + 1/9 + ... + (1/mx)^2))) = O(mx^2 * pi^2/6), see https://en.wikipedia.org/wiki/Basel_problem


# Time:  O(n * r^2 * logr)
# Space: O(r^2)
import collections


# dp, number theory
class Solution2(object):
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9+7
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        dp = collections.defaultdict(int)
        dp[(0, 0)] = 1
        for x in nums:
            new_dp = collections.defaultdict(int)
            for (g1, g2), cnt in dp.items():
                ng1, ng2 = gcd(g1, x), gcd(g2, x)
                new_dp[(g1, g2)] = (new_dp[(g1, g2)]+cnt)%MOD
                new_dp[(ng1, g2)] = (new_dp[(ng1, g2)]+cnt)%MOD
                new_dp[(g1, ng2)] = (new_dp[(g1, ng2)]+cnt)%MOD
            dp = new_dp
        return reduce(lambda accu, x: (accu+x)%MOD, (cnt for (g1, g2), cnt in dp.iteritems() if g1 == g2 > 0), 0)


# Time:  O(n * r^2 * logr)
# Space: O(r^2)
import collections


# dp, number theory
class SolutionTLE(object):
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9+7
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        mx = max(nums)
        dp = [[0]*(mx+1) for _ in xrange(mx+1)]
        dp[0][0] = 1
        for x in nums:
            new_dp = [row[:] for row in dp]
            for g1 in reversed(xrange(mx+1)):
                for g2 in reversed(xrange(mx+1)):
                    ng1, ng2 = gcd(g1, x), gcd(g2, x)
                    new_dp[ng1][g2] = (new_dp[ng1][g2]+dp[g1][g2])%MOD
                    new_dp[g1][ng2] = (new_dp[g1][ng2]+dp[g1][g2])%MOD
            dp = new_dp
        return reduce(lambda accu, x: (accu+x)%MOD, (dp[g][g] for g in xrange(1, mx+1)), 0)


if __name__ == "__main__":
    import time

    # Implement MT19937 and uniform_int_distribution equivalent to C++ std::mt19937 and std::uniform_int_distribution<int>
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

            self.mt = [0] * self.n
            self.index = self.n
            self.seed(seed)

        def seed(self, seed):
            self.index = self.n
            self.mt[0] = seed & 0xFFFFFFFF
            for i in range(1, self.n):
                x = self.mt[i-1]
                self.mt[i] = (self.f * (x ^ (x >> (self.w - 2))) + i) & 0xFFFFFFFF

        def _twist(self):
            for i in range(self.n):
                x = (self.mt[i] & self.upper_mask) + (self.mt[(i + 1) % self.n] & self.lower_mask)
                xA = x >> 1
                if (x & 1) != 0:
                    xA ^= self.a
                self.mt[i] = self.mt[(i + self.m) % self.n] ^ xA
            self.index = 0

        def extract_number(self):
            if self.index >= self.n:
                self._twist()
            y = self.mt[self.index]
            self.index += 1

            y ^= (y >> self.u) & self.d
            y ^= (y << self.s) & self.b
            y ^= (y << self.t) & self.c
            y ^= (y >> self.l)
            return y & 0xFFFFFFFF

        def __call__(self):
            return self.extract_number()

        def min(self):
            return 0

        def max(self):
            return 0xFFFFFFFF

    def uniform_int_distribution(rng, a, b):
        urm = rng.max() - rng.min() + 1  # 2^32
        urn = (b - a + 1)
        uceil = (urm // urn) * urn
        while True:
            r = rng() - rng.min()
            if r < uceil:
                break
        r //= urn
        return int(r) + a

    # Prepare 10 diverse test inputs
    tests = []

    # 1) Empty
    tests.append([])

    # 2) Single element
    tests.append([1])

    # 3) All ones
    tests.append([1] * 8)

    # 4) Primes
    tests.append([2, 3, 5, 7, 11, 13, 17, 19])

    # 5) Even numbers up to 20
    tests.append([2, 4, 6, 8, 10, 12, 14, 16, 18, 20])

    # 6) Mixed with repeats and multiples
    tests.append([6, 6, 3, 9, 12, 15, 30, 45, 60])

    # 7) Deterministic random in [1, 60], size 50
    _rng = MT19937(123456789)
    _v = []
    for _i in range(50):
        _v.append(uniform_int_distribution(_rng, 1, 60))
    tests.append(_v)

    # 8) Powers of two with duplicates
    tests.append([1, 2, 4, 8, 16, 32, 64, 64, 32, 16, 8, 4, 2, 1])

    # 9) Multiples of 6 up to 60, duplicated sequence
    tests.append([6, 12, 18, 24, 30, 36, 42, 48, 54, 60,
                  6, 12, 18, 24, 30, 36, 42, 48, 54, 60])

    # 10) Sequence 1..80
    _v2 = []
    for _i in range(1, 81):
        _v2.append(_i)
    tests.append(_v2)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _iter in range(iterations):
        for tc in tests:
            if tc:
                checksum += sol.subsequencePairCount(tc)
            else:
                checksum += 0

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (microseconds): %d" % (elapsed_us,)
