# Time:  O(n)
# Space: O(1)

class Solution(object):
    def numDecodings(self, s):
        """
        :type s: str
        :rtype: int
        """
        M, W = 1000000007, 3
        dp = [0] * W
        dp[0] = 1
        dp[1] = 9 if s[0] == '*' else dp[0] if s[0] != '0' else 0
        for i in xrange(1, len(s)):
            if s[i] == '*':
                dp[(i + 1) % W] = 9 * dp[i % W]
                if s[i - 1] == '1':
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 9 * dp[(i - 1) % W]) % M
                elif s[i - 1] == '2':
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 6 * dp[(i - 1) % W]) % M
                elif s[i - 1] == '*':
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 15 * dp[(i - 1) % W]) % M
            else:
                dp[(i + 1) % W] = dp[i % W] if s[i] != '0' else 0
                if s[i - 1] == '1':
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M
                elif s[i - 1] == '2' and s[i] <= '6':
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M
                elif s[i - 1] == '*':
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + (2 if s[i] <= '6' else 1) * dp[(i - 1) % W]) % M
        return dp[len(s) % W]


if __name__ == "__main__":
    import timeit

    # Assuming a class Solution with method numDecodings(s) is defined elsewhere
    tests = []
    tests.append("12")             # simple digits
    tests.append("*")              # single wildcard
    tests.append("1*")             # '1' followed by wildcard
    tests.append("2*")             # '2' followed by wildcard
    tests.append("**")             # double wildcard
    tests.append("0")              # invalid single zero
    tests.append("10*")            # zero handling with valid prefix
    tests.append("26*")            # boundary with '2' and wildcard
    tests.append("230")            # invalid zero after '3'
    tests.append("*" * 100)        # long all-wildcards

    sol = Solution()
    checksum = 0

    start = timeit.default_timer()
    iterations = 1000
    for iter in xrange(iterations):
        for s in tests:
            checksum += sol.numDecodings(s)
    end = timeit.default_timer()

    elapsed_ns = long((end - start) * 1000000000.0)
    print "Checksum: {}".format(checksum)
    print "Elapsed time (ns): {}".format(elapsed_ns)