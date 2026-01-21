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
    import time

    testInputs = [
        0,              # edge case: zero
        1,              # minimal positive
        9,              # single digit max
        10,             # transition to two digits
        11,             # multiple ones
        19,             # teen boundary
        20,             # no ones in tens place
        99,             # just before 100
        1000000,        # large power-of-10 boundary
        2000000000      # very large within int range
    ]

    solver = Solution()
    checksum = 0L

    start = time.time()
    iterations = 1
    for _ in xrange(iterations):
        for n in testInputs:
            checksum += solver.countDigitOne(n)
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms