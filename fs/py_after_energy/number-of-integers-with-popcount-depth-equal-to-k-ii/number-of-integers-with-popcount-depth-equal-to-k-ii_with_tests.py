
# Time:  precompute: O((logr) * log(logr) + log*(r) * (logr)) = O((logr) * log(logr)), r = max(n)
#        runtime:    O(nlogr + max_k * n + nlogn + qlogn)
# Space: O(logr + max_k * n)

# fenwick tree
def popcount(x):
    return bin(x).count('1')


def ceil_log2(x):
    return (x-1).bit_length()


class BIT(object):  # 0-indexed.
    def __init__(self, n):
        self.__bit = [0]*(n+1)  # Extra one for dummy node.

    def add(self, i, val):
        i += 1  # Extra one for dummy node.
        while i < len(self.__bit):
            self.__bit[i] += val
            i += (i & -i)

    def query(self, i):
        i += 1  # Extra one for dummy node.
        ret = 0
        while i > 0:
            ret += self.__bit[i]
            i -= (i & -i)
        return ret


MAX_N = 10**15
MAX_BIT_LEN = MAX_N.bit_length()
D = [0]*(MAX_BIT_LEN+1)
for i in xrange(2, MAX_BIT_LEN+1):
    D[i] = D[popcount(i)]+1
MAX_K = 0
while MAX_N != 1:  # O(log*(MAX_N)) times
    MAX_N = ceil_log2(MAX_N)
    MAX_K += 1

# Expose precomputed constants via PRE namespace for tests
class PRE(object):
    pass
PRE.MAX_K = MAX_K
PRE.MAX_BIT_LEN = MAX_BIT_LEN

class Solution(object):
    def popcountDepth(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def count(x):
            return D[popcount(x)]+1 if x != 1 else 0
        
        bit = [BIT(len(nums)) for _ in xrange(MAX_K+1)]
        for i in xrange(len(nums)):
            bit[count(nums[i])].add(i, +1)
        result = []
        for q in queries:
            if q[0] == 1:
                _, l, r, k = q
                assert(k < len(bit))
                result.append(bit[k].query(r)-bit[k].query(l-1))
            else:
                _, i, x = q
                old_d = count(nums[i])
                new_d = count(x)
                if new_d != old_d:
                    bit[old_d].add(i, -1)
                    bit[new_d].add(i, +1)
                nums[i] = x
        return result

if __name__ == "__main__":
    import time

    # Constants
    K = PRE.MAX_K  # allowable depth range [0..K]
    MAX_SAFE = 1000000000000000  # 1e15
    ALL50ONES = (1 << 50) - 1  # popcount = 50 (<= MAX_BIT_LEN)

    # Generate 10 diverse test inputs
    tests = []

    # Test 1: Single element array, query all possible k
    t = {}
    t['nums'] = [1]
    t['queries'] = []
    for k in xrange(0, K + 1):
        t['queries'].append([1, 0, 0, k])
    # Update to 0 and query again
    t['queries'].append([2, 0, 0])
    t['queries'].append([1, 0, 0, 1])
    tests.append(t)

    # Test 2: Small array with mixed values, updates and queries
    t = {}
    t['nums'] = [0, 1, 2, 3, 4, 5, 6, 7]
    t['queries'] = [
        [1, 0, 7, 1],
        [2, 3, 10],
        [1, 2, 5, 2],
        [2, 0, ALL50ONES],
        [1, 0, 7, min(K, 3)],
        [2, 7, 1],
        [1, 7, 7, 0]
    ]
    tests.append(t)

    # Test 3: Medium array with large values near 1e15
    t = {}
    n = 12
    t['nums'] = [0] * n
    for i in xrange(n):
        t['nums'][i] = (123456789123 * (i + 1)) % MAX_SAFE
    t['queries'] = [
        [1, 0, n - 1, min(K, 2)],
        [2, 5, MAX_SAFE - 1],
        [1, 3, 8, min(K, 4)],
        [2, 0, 1],
        [1, 0, 0, 0],
        [2, 11, ALL50ONES],
        [1, 9, 11, min(K, 3)]
    ]
    tests.append(t)

    # Test 4: Powers of two
    t = {}
    n = 20
    t['nums'] = [0] * n
    t['nums'][0] = 1
    for i in xrange(1, n):
        t['nums'][i] = (1 << (i % 50))  # keep within 50 bits
    t['queries'] = [
        [1, 0, n - 1, 0],
        [1, 1, 10, min(K, 2)],
        [2, 10, ALL50ONES],
        [1, 10, 10, min(K, 3)],
        [2, 0, 2],
        [1, 0, 0, min(K, 2)]
    ]
    tests.append(t)

    # Test 5: All zeros
    t = {}
    n = 30
    t['nums'] = [0] * n
    t['queries'] = [
        [1, 0, n - 1, min(K, 1)],
        [2, 15, 1],
        [1, 10, 20, 0],
        [2, 29, ALL50ONES],
        [1, 25, 29, min(K, 3)]
    ]
    tests.append(t)

    # Test 6: Alternating small and large values
    t = {}
    n = 25
    t['nums'] = [0] * n
    for i in xrange(n):
        if i % 2 == 0:
            t['nums'][i] = i + 2
        else:
            t['nums'][i] = MAX_SAFE - (i * 99991 % 100000) - 1
    t['queries'] = [
        [1, 0, n - 1, min(K, 4)],
        [2, 12, 1],
        [2, 13, 0],
        [1, 10, 15, min(K, 2)],
        [1, 5, 5, 0]
    ]
    tests.append(t)

    # Test 7: Alternating 1 and (2^50 - 1)
    t = {}
    n = 18
    t['nums'] = [0] * n
    for i in xrange(n):
        t['nums'][i] = 1 if (i % 2 == 0) else ALL50ONES
    t['queries'] = [
        [1, 0, n - 1, 0],
        [1, 0, n - 1, min(K, 4)],
        [2, 1, 1],
        [2, 2, ALL50ONES],
        [1, 1, 2, min(K, 3)]
    ]
    tests.append(t)

    # Test 8: Sequential updates across range then queries
    t = {}
    n = 16
    t['nums'] = [0] * n
    for i in xrange(n):
        t['nums'][i] = i + 1
    t['queries'] = []
    for i in xrange(0, n, 3):
        t['queries'].append([2, i, ALL50ONES if (i % 2 == 0) else 0])
    t['queries'].append([1, 0, n - 1, min(K, 3)])
    t['queries'].append([1, 5, 10, min(K, 2)])
    tests.append(t)

    # Test 9: Many single-index range queries
    t = {}
    n = 22
    t['nums'] = [0] * n
    for i in xrange(n):
        t['nums'][i] = (i * 9876543211 + 12345) % MAX_SAFE
    t['queries'] = []
    for i in xrange(n):
        t['queries'].append([1, i, i, (i % (K + 1))])
    t['queries'].append([2, 0, 1])
    t['queries'].append([1, 0, 0, 0])
    tests.append(t)

    # Test 10: Mixed random-like updates and queries with bounded values
    t = {}
    n = 28
    t['nums'] = [0] * n
    seed = 88172645463393265
    MASK64 = (1 << 64) - 1
    for i in xrange(n):
        seed = (seed ^ ((seed << 7) & MASK64)) & MASK64
        seed = (seed ^ (seed >> 9)) & MASK64
        t['nums'][i] = seed % MAX_SAFE
    t['queries'] = []
    for i in xrange(20):
        idx = (i * 7) % n
        val = (seed + i * 1234567) % MAX_SAFE
        t['queries'].append([2, idx, val])
        l = (i * 3) % n
        r = min(n - 1, l + (i % 5))
        t['queries'].append([1, l, r, (i % (K + 1))])
    tests.append(t)

    # Benchmark loop
    sol = Solution()
    checksum = 0

    iterations = 1000
    start = time.time()
    for it in xrange(iterations):
        for t in tests:
            nums = list(t['nums'])
            queries = [list(q) for q in t['queries']]
            res = sol.popcountDepth(nums, queries)
            for v in res:
                checksum += v
    end = time.time()
    elapsed_ms = int(round((end - start) * 1000.0))

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (ms): %d" % (elapsed_ms,)
