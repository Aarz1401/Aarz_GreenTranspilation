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
    tests = [
        "I",
        "D",
        "ID",
        "DI",
        "IID",
        "DDI",
        "IDIDID",
        "DDDDIIII",
        "IIDDDIII",
        "IDDIIDIDID"
    ]

    sol = Solution()

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for s in tests:
            r = sol.numPermsDISequence(s)
        #sink = checksum