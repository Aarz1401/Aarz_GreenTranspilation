# Time:  O(n)
# Space: O(1)

class Solution(object):
    def isSelfCrossing(self, x):
        """
        :type x: List[int]
        :rtype: bool
        """
        if len(x) >= 5 and x[3] == x[1] and x[4] + x[0] >= x[2]:
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
    tests = [
        [2, 1, 1, 2],
        [1, 2, 3, 4],
        [1, 1, 1, 1],
        [1, 1, 2, 1, 1],
        [1, 2, 3, 4, 2, 2],
        [2, 2, 3, 3, 2, 2],
        [100000000, 200000000, 300000000, 400000000, 500000000, 600000000],
        [3, 4, 5, 6, 7, 8],
        [1, 2, 3, 2],
        [2, 1, 3, 2, 4, 3]
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += 1 if sol.isSelfCrossing(t) else 0
        sink += checksum
    print(sink)