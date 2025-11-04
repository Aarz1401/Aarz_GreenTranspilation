# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn)
# Space: O(1)

# fast exponentiation
class Solution(object):
    def hasSameDigits(self, s):
        """
        :type s: str
        :rtype: bool
        """
        def check(mod):
            def decompose(x, mod):  # x = a * mod^cnt
                cnt = 0
                while x > 1 and x%mod == 0:
                    x //= mod
                    cnt += 1
                return x, cnt

            result = cnt = 0
            curr = 1
            for i in xrange(len(s)-1):
                if cnt == 0:
                    result = (result+curr*(ord(s[i])-ord(s[i+1])))%mod
                x, c = decompose(len(s)-2-i, mod)
                curr = (curr*x)%mod
                cnt += c
                x, c = decompose(i+1, mod)
                curr = (curr*pow(x, mod-2, mod))%mod
                cnt -= c
            return result == 0

        return check(2) and check(5)


# Time:  O(nlogn)
# Space: O(1)
LOOKUP = [[-1]*(5+1) for _ in xrange(5+1)]


# lucas's theorem
class Solution2(object):
    def hasSameDigits(self, s):
        """
        :type s: str
        :rtype: bool
        """
        def nCr(n, r):
            if n-r < r:
                r = n-r
            if LOOKUP[n][r] == -1:
                c = 1
                for k in xrange(1, r+1):
                    c *= n-k+1
                    c //= k
                LOOKUP[n][r] = c
            return LOOKUP[n][r]

        # https://en.wikipedia.org/wiki/Lucas%27s_theorem
        def nCr_mod(n, r, mod):
            result = 1
            while n > 0 or r > 0:
                n, ni = divmod(n, mod)
                r, ri = divmod(r, mod)
                if ni < ri:
                    return 0
                result = (result*nCr(ni, ri))%mod
            return result

        def nC10(n, k):
            return lookup[nCr_mod(n, k, 2)][nCr_mod(n, k, 5)]

        lookup = [[0]*5 for _ in xrange(2)]
        for i in xrange(10):
            lookup[i%2][i%5] = i
        total = 0
        for i in xrange(len(s)-1):
            total = (total+nC10(len(s)-2, i)*(ord(s[i])-ord(s[i+1])))%10
        return total == 0

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        "",                 # empty string
        "7",                # single digit
        "00",               # same digits
        "01",               # increasing adjacent
        "10",               # decreasing adjacent
        "0123456789",       # ascending sequence
        "9876543210",       # descending sequence
        "1212121212",       # repeating pattern
        "9999999999",       # all same digit
        "31415926"          # mixed digits
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.hasSameDigits(*test)
        else:
            sol.hasSameDigits(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.hasSameDigits(*test)
            else:
                result = sol.hasSameDigits(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()