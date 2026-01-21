
# Time:  precompute: O(rlogr), r = max_nums
#        runtime:    O(mx + nlogr * (log(nlogr) + logn)), mx = max(nums)
# Space: O(rlogr)

# number theory, bit, fenwick tree
MOD = 10**9+7
class BIT(object):  # 0-indexed.
    def __init__(self, n):
        self.__bit = [0]*(n+1)  # Extra one for dummy node.

    def add(self, i, val):
        i += 1  # Extra one for dummy node.
        while i < len(self.__bit):
            self.__bit[i] = (self.__bit[i]+val) % MOD
            i += (i & -i)

    def query(self, i):
        i += 1  # Extra one for dummy node.
        ret = 0
        while i > 0:
            ret = (ret+self.__bit[i]) % MOD
            i -= (i & -i)
        return ret


def factors(n):  # Time: O(nlogn)
    result = [[] for _ in xrange(n+1)]
    for i in xrange(1, n+1):
        for j in range(i, n+1, i):
            result[j].append(i)
    return result


def phi_sieve(n):  # Time: O(nlog(logn))
    phi = range(n+1)
    for i in xrange(2, n+1):
        if phi[i] != i:
            continue
        for j in xrange(i, n+1, i):
            phi[j] -= phi[j]//i
    return phi


MAX_NUM = 7 * 10**4
FACTORS = factors(MAX_NUM)
PHI = phi_sieve(MAX_NUM)
class Solution(object):
    def totalBeauty(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def count(arr):
            for i, x in enumerate(sorted(arr)):  # coordinate compression
                val_to_idx[x] = i
            bit = BIT(len(arr))
            for x in arr:
                bit.add(val_to_idx[x], bit.query(val_to_idx[x]-1)+1)
            return bit.query(len(arr)-1)

        mx = max(nums)
        val_to_idx = [0]*(mx+1)
        lookup = [[] for _ in xrange(mx+1)]
        for x in nums:
            for d in FACTORS[x]:
                lookup[d].append(x)
        return reduce(lambda accu, x: (accu+x)%MOD, (PHI[g]*count(lookup[g]) for g in reversed(xrange(1, mx+1))), 0)


# Time:  precompute: O(rlogr), r = max_nums
#        runtime:    O(mx * log(mx) + nlogr * (log(nlogr) + logn)), mx = max(nums)
# Space: O(rlogr)
# number theory, bit, fenwick tree
class Solution2(object):
    def totalBeauty(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def count(arr):
            val_to_idx = {x:i for i, x in enumerate(sorted(set(arr)))}  # coordinate compression
            bit = BIT(len(val_to_idx))
            for x in arr:
                bit.add(val_to_idx[x], bit.query(val_to_idx[x]-1)+1)
            return bit.query(len(val_to_idx)-1)

        mx = max(nums)
        lookup = [[] for _ in xrange(mx+1)]
        for x in nums:
            for d in FACTORS[x]:
                lookup[d].append(x)
        result = 0
        cnt = [0]*(mx+1)
        for g in reversed(xrange(1, mx+1)):
            cnt[g] = count(lookup[g])
            for ng in xrange(g+g, mx+1, g):
                cnt[g] -= cnt[ng]
            result = (result+g*cnt[g])%MOD
        return result


if __name__ == "__main__":
    from time import time

    MAX_NUM = 70000

    tests = []

    # 1) Small increasing sequence
    tests.append([1, 2, 3, 4, 5, 6])

    # 2) All equal numbers
    tests.append([7] * 20)

    # 3) Primes
    tests.append([2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53])

    # 4) Powers of two
    tests.append([1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768])

    # 5) Multiples of 12
    v = []
    for i in range(1, 16):
        v.append(12 * i)
    tests.append(v)

    # 6) Descending sequence
    tests.append([50, 40, 30, 20, 10, 1])

    # 7) Mixed with near-maximum values
    tests.append([70000, 35000, 23333, 46666, 69999, 7000, 56000, 14000, 10000, 1])

    # 8) Single element
    tests.append([70000])

    # 9) Range 1..200
    v = []
    for i in range(1, 201):
        v.append(i)
    tests.append(v)

    # 10) Larger deterministic sequence of length 1000 within [1, 70000]
    v = []
    for i in range(1, 1001):
        x = (i * 12345) % MAX_NUM + 1
        if x > MAX_NUM:
            x = MAX_NUM
        v.append(x)
    tests.append(v)

    sol = Solution()
    checksum = 0

    start = time()
    iterations = 1
    for iter in range(iterations):
        for tc in tests:
            checksum += sol.totalBeauty(tc)
            checksum %= 1000000007
    end = time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: " + str(checksum)
    print "Elapsed time (ms): " + str(elapsed_ms)
