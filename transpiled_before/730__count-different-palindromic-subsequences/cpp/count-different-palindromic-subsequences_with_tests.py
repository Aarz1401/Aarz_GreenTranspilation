# Time:  O(n^2)
# Space: O(n^2)

class Solution(object):
    def countPalindromicSubsequences(self, S):
        """
        :type S: str
        :rtype: int
        """
        def dp(i, j, prv, nxt, lookup):
            if lookup[i][j] is not None:
                return lookup[i][j]
            result = 1
            if i <= j:
                for x in xrange(4):
                    i0 = nxt[i][x]
                    j0 = prv[j][x]
                    if i <= i0 <= j:
                        result = (result + 1) % P
                    if None < i0 < j0:
                        result = (result + dp(i0+1, j0-1, prv, nxt, lookup)) % P
            result %= P
            lookup[i][j] = result
            return result

        prv = [None] * len(S)
        nxt = [None] * len(S)

        last = [None] * 4
        for i in xrange(len(S)):
            last[ord(S[i])-ord('a')] = i
            prv[i] = tuple(last)

        last = [None] * 4
        for i in reversed(xrange(len(S))):
            last[ord(S[i])-ord('a')] = i
            nxt[i] = tuple(last)

        P = 10**9 + 7
        lookup = [[None] * len(S) for _ in xrange(len(S))]
        return dp(0, len(S)-1, prv, nxt, lookup) - 1


if __name__ == "__main__":
    import timeit

    tests = [
        "",
        "a",
        "aa",
        "ab",
        "abcd",
        "dcba",
        "aaaabbbbccccdddd",
        "ababababcdcdcdcd",
        "abccbaabccba",
        "dacabadacabadacaba"
    ]

    sol = Solution()
    checksum = 0L

    start = timeit.default_timer()
    iterations = 1000
    for iter in xrange(iterations):
        for s in tests:
            if s:
                checksum += long(sol.countPalindromicSubsequences(s))
            else:
                checksum += 0L
    end = timeit.default_timer()

    elapsed_ns = long((end - start) * 1e9)
    print "Checksum:", checksum
    print "Elapsed time (ns):", elapsed_ns