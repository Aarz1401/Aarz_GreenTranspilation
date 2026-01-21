# Time:  O(n^0.25 * logn)
# Space: O(logn)

class Solution(object):
    def superpalindromesInRange(self, L, R):
        """
        :type L: str
        :type R: str
        :rtype: int
        """
        def is_palindrome(k):
            return str(k) == str(k)[::-1]

        K = int((10**((len(R)+1)*0.25)))
        l, r = int(L), int(R)

        result = 0

        # count odd length
        for k in xrange(K):
            s = str(k)
            t = s + s[-2::-1]
            v = int(t)**2
            if v > r:
                break
            if v >= l and is_palindrome(v):
                result += 1

        # count even length
        for k in xrange(K):
            s = str(k)
            t = s + s[::-1]
            v = int(t)**2
            if v > r:
                break
            if v >= l and is_palindrome(v):
                result += 1

        return result


if __name__ == "__main__":
    import time

    tests = [
        ("0", "0"),
        ("1", "1"),
        ("1", "2"),
        ("4", "4"),
        ("1", "1000"),
        ("100", "1000"),
        ("5", "6"),
        ("400000000000000", "900000000000000"),
        ("1", "99999999999999"),
        ("4000000000000000", "5000000000000000"),
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for pr in tests:
            checksum += sol.superpalindromesInRange(pr[0], pr[1])
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms