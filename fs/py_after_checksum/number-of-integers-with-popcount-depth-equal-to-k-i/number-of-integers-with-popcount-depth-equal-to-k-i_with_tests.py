# Time:  precompute: O((logr)^2), r = max(n)
#        runtime:    O((logn)^2)
# Space: O((logr)^2)

# combinatorics
def popcount(x):
    return bin(x).count('1')


MAX_N = 10**15
MAX_BIT_LEN = MAX_N.bit_length()
NCR = [[0]*(MAX_BIT_LEN+1) for _ in xrange(MAX_BIT_LEN+1)]
for i in xrange(MAX_BIT_LEN+1):
    for j in xrange(i+1):
        NCR[i][j] = NCR[i-1][j]+NCR[i-1][j-1] if 0 < j < i else 1
D = [0]*(MAX_BIT_LEN+1)
for i in xrange(2, MAX_BIT_LEN+1):
    D[i] = D[popcount(i)]+1
class Solution(object):
    def popcountDepth(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        def count(c):
            result = cnt = 0
            for i in reversed(xrange(n.bit_length())):
                if not (n&(1<<i)):
                    continue
                if 0 <= c-cnt <= i:
                    result += NCR[i][c-cnt]
                cnt += 1
            if cnt == c:
                result += 1
            return result

        if k == 0:
            return 1
        if k == 1:
            return n.bit_length()-1
        return sum(count(c) for c in xrange(2, n.bit_length()+1) if D[c] == k-1)


if __name__ == "__main__":
    from time import time

    tests = [
        (1, 0),
        (1, 1),
        (1000000000000000, 2),
        (999999999999999, 3),
        (1 << 49, 1),
        ((1 << 49) + 1234567890123, 4),
        ((1 << 20) - 1, 5),
        ((1 << 40) + (1 << 20) + 12345, 2),
        (123456789, 3),
        (500000000000000, 6)
    ]

    sol = Solution()
    checksum = 0

    start = time()
    iterations = 1
    for _ in xrange(iterations):
        for n, k in tests:
            checksum += sol.popcountDepth(n, k)
    end = time()

    elapsed_us = int((end - start) * 1000000.0)
    print "Checksum: %d" % (checksum,)
    print "Elapsed time (microseconds): %d" % (elapsed_us,)