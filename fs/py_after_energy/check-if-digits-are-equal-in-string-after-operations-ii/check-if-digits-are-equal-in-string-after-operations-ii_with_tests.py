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


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs
    tests = []
    # 1) Empty string
    tests.append("")
    # 2) Single digit
    tests.append("7")
    # 3) Two identical digits
    tests.append("00")
    # 4) Ascending digits
    tests.append("0123456789")
    # 5) Descending digits
    tests.append("9876543210")
    # 6) Repeated same digit (longer)
    tests.append('7' * 256)
    # 7) Alternating digits
    s = []
    for i in range(512):
        s.append('2' if (i % 2) else '1')
    tests.append(''.join(s))
    # 8) Digits of pi (prefix)
    tests.append("314159265358979323846264338327950288419716939937510")
    # 9) Pseudorandom-like pattern based on linear congruential sequence (length 1000)
    s = []
    x = 12345
    for i in range(1000):
        x = (1103515245 * x + 12345) & 0x7fffffff
        s.append(chr(ord('0') + (x % 10)))
    tests.append(''.join(s))
    # 10) Repeated pattern of "31415926" (length ~800)
    pat = "31415926"
    s = []
    cur = ""
    while len(cur) < 800:
        cur += pat
    cur = cur[:800]
    tests.append(cur)

    sol = Solution()

    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in range(iterations):
        for i in range(10):
            r = sol.hasSameDigits(tests[i])
            if r:
                checksum += (i + 1)
            checksum ^= (len(tests[i]) + (123 if r else 321))

    end = time.time()
    elapsed_us = int((end - start) * 1000000)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us