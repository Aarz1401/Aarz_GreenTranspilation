
# Time:  O(n^2)
# Space: O(n)

import collections


# dp
class Solution(object):
    def countWinningSequences(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9+7
        lookup = {x:i for i, x in enumerate("FWE")}
        dp = [collections.defaultdict(int) for _ in xrange(3)]
        for i, c in enumerate(s):
            new_dp = [collections.defaultdict(int) for _ in xrange(3)]
            x = lookup[c]
            for j in xrange(3):
                diff = (j-x+1)%3-1
                if i == 0:
                    new_dp[j][diff] = 1
                    continue
                for k in xrange(3):
                    if k == j:
                        continue
                    for v, c in dp[k].iteritems():
                        new_dp[j][v+diff] = (new_dp[j][v+diff]+c)%MOD
            dp = new_dp
        return reduce(lambda accu, x: (accu+x)%MOD, (c for j in xrange(3) for v, c in dp[j].iteritems() if v >= 1), 0)
    

if __name__ == "__main__":
    import time

    tests = []
    tests.append("")
    tests.append("F")
    tests.append("FW")
    tests.append("FWE")
    tests.append("FFWEW")
    tests.append("FWEFWEFW")
    tests.append("FFWWEEFFWWEE")

    s7 = []
    for i in range(20):
        s7.append("FWE"[i % 3])
    tests.append("".join(s7))

    s8 = []
    for i in range(30):
        s8.append("FEW"[i % 3])
    tests.append("".join(s8))

    s9 = []
    seed = 7
    map_chars = ['F', 'W', 'E']
    for i in range(40):
        seed = (seed * 37 + 11) % 3
        s9.append(map_chars[seed])
    tests.append("".join(s9))

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for s in tests:
            checksum += sol.countWinningSequences(s)
            checksum ^= (iter + len(s))

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us
