# Time:  O(k) ~ O(k * r^2)
# Space: O(r)

import collections


class Solution(object):
    def findRotateSteps(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        lookup = collections.defaultdict(list)
        for i in xrange(len(ring)):
            lookup[ring[i]].append(i)

        dp = [[0] * len(ring) for _ in xrange(2)]
        prev = [0]
        for i in xrange(1, len(key)+1):
            dp[i%2] = [float("inf")] * len(ring)
            for j in lookup[key[i-1]]:
                for k in prev:
                    dp[i%2][j] = min(dp[i%2][j],
                                     min((k+len(ring)-j) % len(ring), \
                                         (j+len(ring)-k) % len(ring)) + \
                                     dp[(i-1) % 2][k])
            prev = lookup[key[i-1]]
        return min(dp[len(key)%2]) + len(key)


if __name__ == "__main__":
    import time

    tests = [
        ("godding", "gd"),
        ("abcde", "ade"),
        ("aaaaa", "aaaaa"),
        ("abcdefghijklmnopqrstuvwxyz", "leetcode"),
        ("ababcababc", "cabba"),
        ("xyz", ""),
        ("zxyxzx", "xzxyzxz"),
        ("a", "aaaaaaa"),
        ("qwertyuiopasdfghjklzxcvbnmqwertyuiop", "pazbycqdxre"),
        ("aaaabaaaacaaaadaaaae", "edcba"),
    ]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            res = sol.findRotateSteps(tests[i][0], tests[i][1])
            checksum += res + int(i) + iter

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms