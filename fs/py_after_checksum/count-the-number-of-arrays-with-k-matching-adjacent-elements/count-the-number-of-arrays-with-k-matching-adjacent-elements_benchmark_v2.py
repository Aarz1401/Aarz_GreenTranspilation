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
    tests = [
        (1, 1, 0),
        (2, 1, 1),
        (2, 1, 0),
        (5, 2, 0),
        (5, 2, 4),
        (7, 100, 3),
        (10, 3, 5),
        (50, 1000000007, 0),
        (200000, 100000, 99999),
        (200000, 1, 199999)
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            res = sol.countGoodArrays(t[0], t[1], t[2])
            checksum ^= res
        sink += checksum
    print(sink)
    # print sink