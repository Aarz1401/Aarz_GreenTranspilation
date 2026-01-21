# Time:  O(logn)
# Space: O(1)

class Solution(object):
    def countDigitOne(self, n):
        """
        :type n: int
        :rtype: int
        """
        DIGIT = 1
        is_zero = int(DIGIT == 0)
        result = is_zero
        base = 1
        while n >= base:
            result += (n//(10*base)-is_zero)*base + \
                      min(base, max(n%(10*base) - DIGIT*base + 1, 0))
            base *= 10
        return result

if __name__ == "__main__":
    tests = [0, 1, 9, 10, 11, 19, 99, 101, 1000, 1000000000]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for n in tests:
            checksum += sol.countDigitOne(n)
        sink += checksum
    print(sink)