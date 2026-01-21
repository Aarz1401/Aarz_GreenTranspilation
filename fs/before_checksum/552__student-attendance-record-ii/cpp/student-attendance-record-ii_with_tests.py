# Time:  O(n)
# Space: O(1)

class Solution(object):
    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        M = 1000000007
        a0l0, a0l1, a0l2, a1l0, a1l1, a1l2 = 1, 0, 0, 0, 0, 0
        for i in xrange(n+1):
            a0l2, a0l1, a0l0 = a0l1, a0l0, (a0l0 + a0l1 + a0l2) % M
            a1l2, a1l1, a1l0 = a1l1, a1l0, (a0l0 + a1l0 + a1l1 + a1l2) % M
        return a1l0


if __name__ == "__main__":
    import time

    inputs = [0, 1, 2, 3, 4, 5, 10, 50, 100, 5000]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for n in inputs:
            checksum += sol.checkRecord(n)

    end = time.time()
    elapsed_us = int((end - start) * 1000000)

    print "Checksum: {}".format(checksum)
    print "Elapsed time (microseconds): {}".format(elapsed_us)