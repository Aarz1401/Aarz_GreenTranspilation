
# Time:  O(n + k^2)
# Space: O(n + k)

# dp, prefix sum
class Solution(object):
    def possibleStringCount(self, word, k):
        MOD = 10**9+7
        cnt = [0]
        for i in xrange(len(word)):
            cnt[-1] += 1
            if i+1 == len(word) or word[i+1] != word[i]:
                cnt.append(0)
        cnt.pop()
        result = reduce(lambda accu, x: accu*x%MOD, cnt, 1)
        if k <= len(cnt):
            return result
        dp = [0]*(k-len(cnt))
        dp[0] = 1
        for l in cnt:
            for i in xrange(len(dp)-1):
                dp[i+1] = (dp[i+1]+dp[i])%MOD
            for i in reversed(xrange(l, len(dp))):
                dp[i] = (dp[i]-dp[i-l])%MOD
        return reduce(lambda accu, x: (accu-x)%MOD, dp, result)

if __name__ == "__main__":
    import time

    tests = []
    tests.append(("", 0))
    tests.append(("a", 1))
    tests.append(("aaaaaa", 3))
    tests.append(("ababababab", 5))
    tests.append(("aaabbbcccddd", 4))
    tests.append(("zzzzzyxxxx", 7))
    tests.append(("a1a1a1bbbccddeeee", 12))
    tests.append(("abcdef", 3))
    base = "abcdefghijklmnopqrstuvwxyz"
    longPattern = ""
    for i in range(20):
        longPattern += base
    tests.append((longPattern, 100))
    tests.append(("b" * 300 + "c" * 200, 50))

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    psc = sol.possibleStringCount
    for iter in range(iterations):
        for tc in tests:
            checksum += psc(tc[0], tc[1])

    end = time.time()
    elapsed = int((end - start) * 1000000.0)

    print "Checksum: {}".format(checksum)
    print "Elapsed time (microseconds): {}".format(elapsed)
