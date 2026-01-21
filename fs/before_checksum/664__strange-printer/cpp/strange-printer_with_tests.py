# Time:  O(n^3)
# Space: O(n^2)

class Solution(object):
    def strangePrinter(self, s):
        """
        :type s: str
        :rtype: int
        """
        def dp(s, i, j, lookup):
            if i > j:
                return 0
            if (i, j) not in lookup:
                lookup[(i, j)]  = dp(s, i, j-1, lookup) + 1
                for k in xrange(i, j):
                    if s[k] == s[j]:
                        lookup[(i, j)] = min(lookup[(i, j)], \
                                             dp(s, i, k, lookup) + dp(s, k+1, j-1, lookup))
            return lookup[(i, j)]

        lookup = {}
        return dp(s, 0, len(s)-1, lookup)

if __name__ == "__main__":
    from time import time

    tests = [
        "",
        "a",
        "aaaaaa",
        "ababababa",
        "abcde",
        "aaabbbccc",
        "aba",
        "abcbaabcba",
        "bacbacbacb",
        "zzzyxyzzxxyyzz"
    ]

    sol = Solution()
    checksum = 0

    start = time()

    iterations = 1
    for _ in xrange(iterations):
        for s in tests:
            checksum += sol.strangePrinter(s)

    elapsed_ms = (time() - start) * 1000.0

    print "Checksum: {}".format(checksum)
    print "Elapsed ms: {}".format(elapsed_ms)