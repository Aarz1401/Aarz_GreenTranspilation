
# Time:  O(n^2), n = len(r)
# Space: O(n)

# math, stars and bars, combinatorics
class Solution(object):
    def countNumbers(self, l, r, b):
        """
        :type l: str
        :type r: str
        :type b: int
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

        def nHr(n, k):
            return nCr(n+k-1, k)

        def count(x):
            digits_base = []
            while x:
                x, r = divmod(x, b)
                digits_base.append(r)
            digits_base.reverse()
            if not digits_base:
                digits_base.append(0)
            result = 0
            for i in xrange(len(digits_base)):
                if i-1 >= 0 and digits_base[i-1] > digits_base[i]:
                    break
                for j in xrange(digits_base[i-1] if i-1 >= 0 else 0, digits_base[i]):
                    result = (result + nHr((b-1)-j+1, len(digits_base)-(i+1))) % MOD
            else:
                result = (result+1)%MOD
            return result

        return (count(int(r)) - count(int(l)-1)) % MOD


# Time:  O(n^2), n = len(r)
# Space: O(n)
# math, stars and bars, combinatorics
class Solution2(object):
    def countNumbers(self, l, r, b):
        """
        :type l: str
        :type r: str
        :type b: int
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

        def nHr(n, k):
            return nCr(n+k-1, k)

        def decrease(digits):
            for i in reversed(xrange(len(digits))):
                if digits[i]:
                    digits[i] -= 1
                    break
                digits[i] = 9

        def divide(digits, base):
            result = []
            r = 0
            for d in digits:
                q, r = divmod(r*10+d, base)
                if result or q:
                    result.append(q)
            return result, r

        def to_base(digits, base):
            result = []
            while digits:
                digits, r = divide(digits, base)
                result.append(r)
            result.reverse()
            return result

        def count(digits):
            digits_base = to_base(digits, b)
            result = 0
            for i in xrange(len(digits_base)):
                if i-1 >= 0 and digits_base[i-1] > digits_base[i]:
                    break
                for j in xrange(digits_base[i-1] if i-1 >= 0 else 0, digits_base[i]):
                    result = (result + nHr((b-1)-j+1, len(digits_base)-(i+1))) % MOD
            else:
                result = (result+1)%MOD
            return result

        digits_l = map(int, l)
        decrease(digits_l)
        digits_r = map(int, r)
        return (count(digits_r) - count(digits_l)) % MOD


class SolutionPatched(object):
    def countNumbers(self, l, r, b):
        MOD = 10**9+7
        def is_zero_str(s):
            for ch in s:
                if ch != '0':
                    return False
            return True
        if is_zero_str(l):
            if is_zero_str(r):
                return 1 % MOD
            return (Solution().countNumbers("1", r, b) + 1) % MOD
        return Solution().countNumbers(l, r, b)


if __name__ == "__main__":
    import time

    tests = [
        ("0", "0", 2),                                                    # exact zero in base 2
        ("0000", "0000", 3),                                              # leading zeros, zero range
        ("0", "9", 10),                                                   # small range in base 10
        ("10", "99", 10),                                                 # two-digit range in base 10
        ("1", "100000", 2),                                               # larger range in base 2
        ("12345678901234567890", "12345678901234567999", 10),             # big numbers in base 10
        ("999999999999999999", "1000000000000000000", 16),                # boundary around 1e18 in base 16
        ("123456789", "987654321", 7),                                    # mid-size range in base 7
        ("42", "42", 36),                                                 # single value in base 36
        ("10000000000000000000000000000000000000000000000000",
         "10000000000000000000000000000000000000000000012345", 11)        # very large numbers in base 11
    ]

    sol = SolutionPatched()
    checksum = 0

    start = time.time()

    iterations = 1
    mask = (1 << 64) - 1
    for iter in range(iterations):
        for t in tests:
            l = t[0]
            r = t[1]
            b = t[2]
            res = sol.countNumbers(l, r, b)
            mix = ((res & mask) + 0x9e3779b97f4a7c15 + ((checksum << 6) & mask) + ((checksum >> 2) & mask)) & mask
            checksum = (checksum ^ mix) & mask

    end = time.time()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns
