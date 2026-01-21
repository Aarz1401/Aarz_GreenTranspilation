# Time:  O(n)
# Space: O(1)

class Solution(object):
    def isSelfCrossing(self, x):
        """
        :type x: List[int]
        :rtype: bool
        """
        if len(x) >= 5 and x[3] == x[1] and x[4] + x[0] >= x[2]:
            # Crossing in a loop:
            #     2
            # 3 ┌────┐
            #   └─══>┘1
            #   4  0  (overlapped)
            return True

        for i in xrange(3, len(x)):
            if x[i] >= x[i - 2] and x[i - 3] >= x[i - 1]:
                # Case 1:
                #    i-2
                # i-1┌─┐
                #    └─┼─>i
                #     i-3
                return True
            elif i >= 5 and x[i - 4] <= x[i - 2] and x[i] + x[i - 4] >= x[i - 2] and \
                            x[i - 1] <= x[i - 3] and x[i - 5] + x[i - 1] >= x[i - 3]:
                # Case 2:
                #    i-4
                #    ┌──┐
                #    │i<┼─┐
                # i-3│ i-5│i-1
                #    └────┘
                #      i-2
                return True
        return False


if __name__ == "__main__":
    from time import time

    tests = [
        [2, 1, 1, 2],
        [1, 2, 3, 4, 5, 6],
        [1, 1, 2, 1, 1],
        [1, 1, 2, 2, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 2, 3, 4, 5],
        [],
        [5],
        [0, 0, 0, 0],
        [1500000000, 1500000000, 1, 1500000000, 1500000000]
    ]

    solver = Solution()

    checksum = 0L

    start = time()

    iterations = 1000
    for iter in xrange(iterations):
        for i, t in enumerate(tests):
            res = solver.isSelfCrossing(t)
            if res:
                checksum += i + 1

    elapsed_us = int((time() - start) * 1000000.0)

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us