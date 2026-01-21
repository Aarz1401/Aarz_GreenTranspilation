
# Time:  O(logr * 2 * 10 * s)
# Space: O(s) ~= O(2026), s = len(states)

import collections


# dp
class Solution(object):
    def beautifulNumbers(self, l, r):
        """
        :type l: int
        :type r: int
        :rtype: int
        """
        def count(x):
            s = map(lambda x: ord(x)-ord('0'), str(x))
            dp = [collections.defaultdict(int) for _ in xrange(2)]
            dp[1][1, 0] = 1
            for c in s:
                new_dp = [collections.defaultdict(int) for _ in xrange(2)]
                for b in xrange(2):
                    for (mul, total), cnt in dp[b].iteritems():
                        for x in xrange((c if b else 9)+1):
                            new_dp[b and x == c][mul*(1 if total == 0 == x else x), total+x] += cnt
                dp = new_dp
            result = 0
            for b in xrange(2):
                for (mul, total), cnt in dp[b].iteritems():
                    if total and mul%total == 0:
                        result += cnt
            return result

        return count(r)-count(l-1)


if __name__ == "__main__":
    import time

    tests = [
        (0, 0),
        (1, 9),
        (10, 99),
        (100, 1000),
        (1, 1000000),
        (123456789, 987654321),
        (999999000000, 1000000000000),
        (555555555555555, 555555555555999),
        (1000000000000000, 1000000000010000),
        (314159265358979, 314159265359000)
    ]

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for t in tests:
            l, r = t
            if l == 0:
                res = sol.beautifulNumbers(1, r)
            else:
                res = sol.beautifulNumbers(l, r)
            x = ((res & mask) ^ ((iter + 1) & mask)) & mask
            checksum = (checksum + x) & mask

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % (checksum & mask)
    print "Elapsed time (microseconds): %d" % elapsed_us
