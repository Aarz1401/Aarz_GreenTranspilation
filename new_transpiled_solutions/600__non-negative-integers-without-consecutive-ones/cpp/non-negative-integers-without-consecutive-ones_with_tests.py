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
    import timeit

    inputs = [
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        8,
        21,
        1073741824
    ]

    sol = Solution()
    checksum = 0

    start = timeit.default_timer()

    iterations = 1000
    for _ in xrange(iterations):
        for x in inputs:
            checksum += sol.findIntegers(x)

    end = timeit.default_timer()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns