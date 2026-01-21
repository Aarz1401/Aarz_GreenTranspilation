
# Time:  O(d * n)
# Space: O(d)

# case works, math, freq table
class Solution(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        result = 0
        # digit 1, 2, 5
        for i in xrange(len(s)):
            if s[i] in ('1', '2', '5'):
                result += i+1
        # digit 3, 6
        remain = 0
        cnt = [0]*3
        cnt[0] = 1
        for i in xrange(len(s)):
            remain = (remain+(ord(s[i])-ord('0')))%3
            if s[i] in ('3', '6'):
                result += cnt[remain]
            cnt[remain] += 1
        # digit 9
        remain = 0
        cnt = [0]*9
        cnt[0] = 1
        for i in xrange(len(s)):
            remain = (remain+(ord(s[i])-ord('0')))%9
            if s[i] == '9':
                result += cnt[remain]
            cnt[remain] += 1
        # digit 4
        for i in xrange(len(s)):
            if s[i] == '4':
                result += 1
                if i-1 >= 0 and int(s[i-1:i+1])%4 == 0:
                    result += i
        # digit 8
        for i in xrange(len(s)):
            if s[i] == '8':
                result += 1
                if i-1 >= 0 and int(s[i-1:i+1])%8 == 0:
                    result += 1
                if i-2 >= 0 and int(s[i-2:i+1])%8 == 0:
                    result += i-1
        # digit 7
        base = 1
        remain = 0
        cnt = [0]*7
        for i in xrange(len(s)):
            remain = (remain+base*(ord(s[~i])-ord('0')))%7
            result += cnt[remain]
            if s[~i] == '7':
                result += 1
                cnt[remain] += 1
            base = (base*10)%7
        return result


# Time:  O(d * n)
# Space: O(d)
# case works, math, freq table
class Solution2(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        result = 0
        # digit 4
        for i in xrange(len(s)):
            if s[i] == '4':
                result += 1
                if i-1 >= 0 and int(s[i-1:i+1])%4 == 0:
                    result += i
        # digit 8
        for i in xrange(len(s)):
            if s[i] == '8':
                result += 1
                if i-1 >= 0 and int(s[i-1:i+1])%8 == 0:
                    result += 1
                if i-2 >= 0 and int(s[i-2:i+1])%8 == 0:
                    result += i-1
        for d in xrange(1, 9+1):
            if d in (4, 8):
                continue
            base = 1
            remain = 0
            cnt = [0]*d
            c = 0
            for i in xrange(len(s)):
                remain = (remain+base*(ord(s[~i])-ord('0')))%d
                c += cnt[remain]
                if s[~i] == str(d):
                    c += d != 8
                    cnt[remain] += 1
                base = (base*10)%d
            result += c
        return result


# Time:  O(d^2 * n)
# Space: O(d^2)
# dp
class Solution3(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        result = 0
        dp = [[0]*10 for _ in xrange(10)]
        for i in xrange(1, len(s)+1):
            new_dp = [[0]*10 for _ in xrange(10)]
            x = ord(s[i-1])-ord('0')
            for d in xrange(1, 9+1):
                new_dp[d][x%d] += 1
                for r in xrange(d):
                    new_dp[d][(r*10+x)%d] += dp[d][r]
            dp = new_dp
            result += dp[x][0]
        return result


if __name__ == "__main__":
    import time

    def repeatPattern(pat, times):
        return pat * times

    def genLCGDigits(n, seed):
        x = seed & 0xFFFFFFFF
        res = []
        for _ in xrange(n):
            x = (x * 1664525 + 1013904223) & 0xFFFFFFFF
            res.append(chr(ord('0') + (x % 10)))
        return ''.join(res)

    # Prepare 10 diverse test inputs (strings of digits)
    tests = []
    tests.append("")                                   # 1) empty
    tests.append("0")                                  # 2) single zero
    tests.append("9")                                  # 3) single nine
    tests.append("27")                                 # 4) small mixed digits
    tests.append("1234567890")                         # 5) all digits once
    tests.append("7" * 100)                            # 6) many 7s
    tests.append(repeatPattern("31415926", 32))        # 7) length 256
    tests.append(repeatPattern("0123456789", 100))     # 8) length 1000
    tests.append(genLCGDigits(2000, 123456789))        # 9) length 2000 pseudo-random digits
    tests.append("8" * 4096)                           # 10) many 8s

    sol = Solution()

    checksum = 0

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for s in tests:
            ans = sol.countSubstrings(s)
            checksum += ans

    elapsed_us = int(round((time.time() - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us
