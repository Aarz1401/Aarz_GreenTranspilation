
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
    sol = Solution()
    tests = []
    tests.append([1,2,3,4,5,6,7,8,9,10])
    tests.append([7] * 20)
    tests.append([2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97])
    tests.append([1,2,4,8,16,32,64,128,256,512])
    tests.append([12,18,6,3,9,15,21,27,24,30,36,42,45,48,54,60])
    tests.append([999,1000,996,972,945,930,875,840,768,720,660,648,600,588,576])
    tests.append([60,59,58,57,56,55,54,53,52,51,50])
    tests.append([2000,1995,1980,1920,1800,1600,1500,1400,1350,1300])
    tests.append([101,103,107,109,113,127,131,137,139,149])
    tests.append([2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3])

    sink = 0
    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for i in range(10):
            res = sol.totalBeauty(tests[i])
        #     checksum += res
        #     if checksum >= MOD:
        #         checksum -= MOD
        # #sink = checksum
    # print sink
