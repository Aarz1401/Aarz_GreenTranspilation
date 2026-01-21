
# Time:  O(n + logm)
# Space: O(n)

# combinatorics, fast exponentiation
MOD = 10**9+7
FACT, INV, INV_FACT = [[1]*2 for _ in xrange(3)]
def nCr(n, k):
    while len(INV) <= n:  # lazy initialization
        FACT.append(FACT[-1]*len(INV) % MOD)
        INV.append(INV[MOD%len(INV)]*(MOD-MOD//len(INV)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
        INV_FACT.append(INV_FACT[-1]*INV[-1] % MOD)
    return (FACT[n]*INV_FACT[n-k] % MOD) * INV_FACT[k] % MOD


class Solution(object):
    def countGoodArrays(self, n, m, k):
        """
        :type n: int
        :type m: int
        :type k: int
        :rtype: int
        """
        return (nCr(n-1, k)*(m*pow(m-1, (n-1)-k, MOD)))%MOD


if __name__ == "__main__":
    from timeit import default_timer as timer

    # Define 10 diverse test inputs (n, m, k)
    tests = [
        (1, 1, 0),             # minimal case
        (5, 3, 2),             # small typical
        (10, 1000, 0),         # k = 0
        (50, 2, 49),           # k = n - 1
        (1000, 1000000000, 500),  # large m, medium n
        (200000, 100000, 100000), # large n
        (2, 1000000007, 1),    # m = MOD
        (100000, 1, 0),        # m = 1
        (3, 2, 1),             # small mixed
        (7, 5, 7)              # k > n - 1 -> zero combinations
    ]

    sol = Solution()
    checksum = 0

    start = timer()
    iterations = 1000
    mask = (1 << 64) - 1
    for iter in xrange(iterations):
        for t in tests:
            n, m, k = t
            try:
                res = sol.countGoodArrays(n, m, k)
            except Exception:
                res = 0
            v = ((res & mask) + 0x9e3779b97f4a7c15 + ((checksum << 6) & mask) + ((checksum >> 2) & mask)) & mask
            checksum = (checksum ^ v) & mask
    end = timer()

    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us
