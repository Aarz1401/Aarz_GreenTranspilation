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
    tests = [
        ("1", "1"),
        ("2", "3"),
        ("4", "9"),
        ("1", "1000"),
        ("10", "10000"),
        ("100", "100000"),
        ("400", "500"),
        ("121", "484"),
        ("1000000", "100000000"),
        ("5000000000", "6000000000"),
    ]

    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        sol = Solution()
        for pr in tests:
            checksum += sol.superpalindromesInRange(pr[0], pr[1])
        sink += checksum
    print(sink)