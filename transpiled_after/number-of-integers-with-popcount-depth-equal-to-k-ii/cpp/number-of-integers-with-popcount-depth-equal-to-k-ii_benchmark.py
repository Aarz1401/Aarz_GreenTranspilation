# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Helper to fetch MAX_K from Solution if available
    def get_max_k():
        max_k_candidates = []
        try:
            max_k_candidates.append(getattr(Solution, 'MAX_K'))
        except Exception:
            pass
        try:
            max_k_candidates.append(getattr(getattr(Solution, 'PRE'), 'MAX_K'))
        except Exception:
            pass
        try:
            s = Solution()
            try:
                max_k_candidates.append(getattr(s, 'MAX_K'))
            except Exception:
                pass
            try:
                max_k_candidates.append(getattr(getattr(s, 'PRE'), 'MAX_K'))
            except Exception:
                pass
        except Exception:
            pass
        for v in max_k_candidates:
            if isinstance(v, (int, long)):
                return v
        return 0

    # Prepare sample data (converted from C++)
    N = 32
    nums = []
    for idx in xrange(N):
        nums.append(((idx + 1) * 1234567) % 1000000000000000 + 1)

    # Prepare queries (converted from C++)
    Q = 16
    max_k = get_max_k()
    queries = []
    for qidx in xrange(Q):
        if qidx % 3 == 2:
            index = (qidx * 7) % N
            x = (((index + 1) * 1234567) + qidx) % 1000000000000000 + 1
            queries.append([2, index, x])
        else:
            l = qidx % N
            r = l + (qidx % 5)
            if r >= N:
                r = N - 1
            k = qidx % (max_k + 1)
            queries.append([1, l, r, k])

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        (nums, queries)
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            args = list(test)
            # Solution mutates nums on type-2 queries; pass a copy
            if isinstance(args[0], list):
                args[0] = args[0][:]
            sol.popcountDepth(*args)
        else:
            arg = test
            if isinstance(arg, list):
                arg = arg[:]
            sol.popcountDepth(arg)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                args = list(test)
                if isinstance(args[0], list):
                    args[0] = args[0][:]
                result = sol.popcountDepth(*args)
            else:
                arg = test
                if isinstance(arg, list):
                    arg = arg[:]
                result = sol.popcountDepth(arg)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()