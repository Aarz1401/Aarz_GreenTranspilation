
# Time:  O(n^2)
# Space: O(n)

# dp
cnt = [0]*2
class Solution(object):
    def countKReducibleNumbers(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        def popcount(x):
            return bin(x).count('1')

        while len(s)-1 >= len(cnt):  # cached
            cnt.append(cnt[popcount(len(cnt))]+1)
        dp = [0]*len(s)
        curr = 0
        for i in xrange(len(s)):
            for j in reversed(range(i)):
                dp[j+1] = (dp[j+1]+dp[j])%MOD
            if s[i] != '1':
                continue
            dp[curr] = (dp[curr]+1)%MOD
            curr += 1
        return reduce(lambda accu, x: (accu+x)%MOD, (dp[i] for i in xrange(1, len(s)) if cnt[i] < k), 0)


# Time:  O(n^2)
# Space: O(n)
# dp, combinatorics
cnt = [0]*2
class Solution2(object):
    def countKReducibleNumbers(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9+7
        fact, inv, inv_fact = [[1]*2 for _ in xrange(3)]  
        def nCr(n, k):
            while len(inv) <= n:  # lazy initialization
                fact.append(fact[-1]*len(inv) % MOD)
                inv.append(inv[MOD%len(inv)]*(MOD-MOD//len(inv)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
                inv_fact.append(inv_fact[-1]*inv[-1] % MOD)
            return (fact[n]*inv_fact[n-k] % MOD) * inv_fact[k] % MOD

        def popcount(x):
            return bin(x).count('1')
      
        while len(s)-1 >= len(cnt):  # cached
            cnt.append(cnt[popcount(len(cnt))]+1)
        result = curr = 0
        for i in xrange(len(s)):
            if s[i] != '1':
                continue
            for c in xrange((len(s)-(i+1))+1):
                if cnt[curr+c] < k:
                    result = (result+nCr(len(s)-(i+1), c))%MOD
            curr += 1
        return (result-1)%MOD


if __name__ == "__main__":
    import time

    def makeAlternating(n):
        return ''.join('0' if i % 2 == 0 else '1' for i in xrange(n))

    def makeAll(n, ch):
        return ch * n

    def makePattern100(n):
        return ''.join('1' if i % 3 == 0 else '0' for i in xrange(n))

    def makePrimeOnes(n):
        if n <= 0:
            return ''
        is_prime = [False] * n
        if n >= 2:
            for i in xrange(2, n):
                is_prime[i] = True
            limit = int(n ** 0.5) + 1
            for p in xrange(2, limit):
                if is_prime[p]:
                    step = p
                    start = p * p
                    for multiple in xrange(start, n, step):
                        is_prime[multiple] = False
        return ''.join('1' if is_prime[i] else '0' for i in xrange(n))

    def makeDeterministicPseudo(n):
        seed = 123456789
        a = 1103515245
        c = 12345
        m = 1 << 31
        out = []
        for _ in xrange(n):
            seed = (seed * a + c) % m
            bit = (seed >> 16) & 1
            out.append('1' if bit else '0')
        return ''.join(out)

    # Generate 10 diverse test inputs (string s, int k)
    tests = []
    tests.append(("", 0))                               # 1) empty string
    tests.append(("0", 1))                              # 2) single zero
    tests.append(("1", 1))                              # 3) single one
    tests.append((makeAlternating(10), 2))              # 4) alternating length 10
    tests.append((makeAll(32, '1'), 3))                 # 5) all ones length 32
    tests.append((makeAll(64, '0'), 4))                 # 6) all zeros length 64
    tests.append((makePattern100(75), 2))               # 7) "1" every 3rd position length 75
    tests.append((makeAlternating(128), 5))             # 8) alternating length 128
    tests.append((makePrimeOnes(200), 4))               # 9) ones at prime indices length 200
    tests.append((makeDeterministicPseudo(256), 6))     # 10) deterministic pseudo-random length 256

    sol = Solution()

    checksum = 0

    start = time.time()
    iterations = 1
    for _ in xrange(iterations):
        for s, k in tests:
            checksum += sol.countKReducibleNumbers(s, k)
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum: " + str(checksum)
    print "Elapsed time (ms): " + str(elapsed_ms)
