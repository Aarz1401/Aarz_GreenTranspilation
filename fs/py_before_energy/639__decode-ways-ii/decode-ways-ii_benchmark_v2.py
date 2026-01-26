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
    tests = [
        "1",
        "12",
        "226",
        "*",
        "10",
        "2101",
        "1*0",
        "2*6",
        "11106",
        "*7"
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for s in tests:
            r = sol.numDecodings(s)
        #sink = checksum