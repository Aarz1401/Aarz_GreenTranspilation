# Time:  O(n^2)
# Space: O(n)

class Solution(object):
    def numPermsDISequence(self, S):
        """
        :type S: str
        :rtype: int
        """
        dp = [1]*(len(S)+1)
        for c in S:
            if c == "I":
                dp = dp[:-1]
                for i in xrange(1, len(dp)):
                    dp[i] += dp[i-1]
            else:
                dp = dp[1:]
                for i in reversed(xrange(len(dp)-1)):
                    dp[i] += dp[i+1]
        return dp[0] % (10**9+7)


if __name__ == "__main__":
    from time import time

    tests = []
    tests.append("")                 # 0-length
    tests.append("I")                # single I
    tests.append("D")                # single D
    tests.append("ID")               # simple mixed
    tests.append("DI")               # simple mixed reversed
    tests.append("IIDDD")            # clustered I then D
    tests.append("D" * 10)           # all D
    tests.append("I" * 10)           # all I
    tests.append("IDIDIDIDID")       # alternating length 10

    s10_chars = []
    for i in range(80):
        s10_chars.append('I' if ((i * 37 + 13) % 5) < 2 else 'D')
    s10 = ''.join(s10_chars)
    tests.append(s10)

    sol = Solution()
    checksum = 0

    start = time()

    iterations = 1000
    for _ in range(iterations):
        for s in tests:
            res = sol.numPermsDISequence(s)
            checksum += res

    end = time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us