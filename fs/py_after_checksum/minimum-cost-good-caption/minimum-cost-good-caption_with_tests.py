# Time:  O(26 * n)
# Space: O(26 * n)

# dp, backtracing
class Solution(object):
    def minCostGoodCaption(self, caption):
        """
        :type caption: str
        :rtype: str
        """
        L = 3
        n = len(caption)
        if n < L:
            return ""
        dp = [[[0]*2 for _ in xrange(26)] for _ in xrange(n-L+1)]
        mn = [[0]*2 for _ in xrange(n-L+1)]
        cap = map(lambda x: ord(x)-ord('a'), caption)
        for i in reversed(xrange(n-L+1)):
            for j in xrange(26):
                if i == n-L:
                    dp[i][j][:] = [sum(abs(cap[k]-j) for k in xrange(i, i+L)), L]
                    continue
                dp[i][j][:] = [dp[i+1][j][0]+abs(cap[i]-j), 1]
                if i+L < n-2:
                    curr, c = mn[i+L]
                    curr += sum(abs(cap[k]-j) for k in xrange(i, i+L))
                    if curr < dp[i][j][0] or (curr == dp[i][j][0] and c < j):
                        dp[i][j][:] = [curr, L]
            mn[i] = min([dp[i][j][0], j] for j in xrange(26))
        result = []
        i, j, l = 0, mn[0][1], 1
        while i != n:
            if l == L:
                j = mn[i][1]
            l = dp[i][j][1]
            result.append(chr(ord('a')+j)*l)
            i += l
        return "".join(result)


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs (strings as required by the solution)
    tests = [
        "",    # empty
        "a",   # single lowercase
        "z",   # single lowercase end
        "A",   # single uppercase
        "ab",  # two lowercase ascending
        "ba",  # two lowercase descending
        "zz",  # two same end chars
        "aa",  # two same start chars
        "Az",  # mixed case
        "mm"   # two middle letters
    ]

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    start = time.time()

    iterations = 1
    for iter in range(iterations):
        for i in range(len(tests)):
            out = sol.minCostGoodCaption(tests[i])
            if out is None:
                out = ""
            try:
                # Ensure byte-string for consistent ord() behavior
                if isinstance(out, unicode):
                    out = out.encode('utf-8')
            except NameError:
                pass  # unicode type may not exist in some environments

            checksum = (checksum + len(out)) & mask
            for c in out:
                checksum = (checksum * 1315423911 + ord(c)) & mask
            checksum = (checksum + len(tests[i])) & mask
            if tests[i]:
                checksum = (checksum ^ ord(tests[i][0])) & mask

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (us): %d" % elapsed_us