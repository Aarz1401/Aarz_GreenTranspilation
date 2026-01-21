# Time:  O(l)
# Space: O(l)

class Solution(object):
    def nearestPalindromic(self, n):
        """
        :type n: str
        :rtype: str
        """
        l = len(n)
        candidates = set((str(10**l + 1), str(10**(l - 1) - 1)))
        prefix = int(n[:(l + 1)/2])
        for i in map(str, (prefix-1, prefix, prefix+1)):
            candidates.add(i + [i, i[:-1]][l%2][::-1])
        candidates.discard(n)
        return min(candidates, key=lambda x: (abs(int(x) - int(n)), int(x)))


if __name__ == "__main__":
    tests = [
        "1",
        "2",
        "10",
        "11",
        "99",
        "123",
        "1283",
        "1000",
        "9999",
        "12345678987654321"
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for s in tests:
            r = sol.nearestPalindromic(s)
            # checksum += len(r)
            # checksum += ord(r[0]) - ord('0')
            # checksum += ord(r[-1]) - ord('0')
        #sink = checksum

    # print sink