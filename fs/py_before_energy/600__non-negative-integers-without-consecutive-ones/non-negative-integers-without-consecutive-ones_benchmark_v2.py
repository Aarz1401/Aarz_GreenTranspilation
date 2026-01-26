# Time:  O(1)
# Space: O(1)

class Solution(object):
    def findIntegers(self, num):
        """
        :type num: int
        :rtype: int
        """
        dp = [0] * 32
        dp[0], dp[1] = 1, 2
        for i in xrange(2, len(dp)):
            dp[i] = dp[i-1] + dp[i-2]
        result, prev_bit = 0, 0
        for i in reversed(xrange(31)):
            if (num & (1 << i)) != 0:
                result += dp[i]
                if prev_bit == 1:
                    result -= 1
                    break
                prev_bit = 1
            else:
                prev_bit = 0
        return result + 1

if __name__ == "__main__":
    s = Solution()
    tests = [0, 1, 2, 3, 5, 8, 21, 144, 1000, 1000000000]

    iterations = 1000
    sink = 0
    for iter in xrange(iterations):
        #checksum = 0
        for x in tests:
            r = s.findIntegers(x)
        #sink = checksum
    # print sink