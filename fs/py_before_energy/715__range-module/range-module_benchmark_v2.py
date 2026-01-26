# Time:  addRange:    O(n)
#        removeRange: O(n)
#        queryRange:  O(logn)
# Space: O(n)

import bisect


class RangeModule(object):

    def __init__(self):
        self.__intervals = []

    def addRange(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: void
        """
        tmp = []
        i = 0
        for interval in self.__intervals:
            if right < interval[0]:
                tmp.append((left, right))
                break
            elif interval[1] < left:
                tmp.append(interval)
            else:
                left = min(left, interval[0])
                right = max(right, interval[1])
            i += 1
        if i == len(self.__intervals):
            tmp.append((left, right))
        while i < len(self.__intervals):
            tmp.append(self.__intervals[i])
            i += 1
        self.__intervals = tmp

    def queryRange(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: bool
        """
        i = bisect.bisect_left(self.__intervals, (left, float("inf")))
        if i: i -= 1
        return bool(self.__intervals) and \
               self.__intervals[i][0] <= left and \
               right <= self.__intervals[i][1]

    def removeRange(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: void
        """
        tmp = []
        for interval in self.__intervals:
            if interval[1] <= left or interval[0] >= right:
                tmp.append(interval)
            else:
                if interval[0] < left:
                    tmp.append((interval[0], left))
                if right < interval[1]:
                    tmp.append((right, interval[1]))
        self.__intervals = tmp


if __name__ == "__main__":
    tests = [
        [
            (0, 5, 10), (2, 6, 9), (2, 4, 6), (0, 8, 12),
            (2, 10, 12), (1, 7, 9), (2, 7, 9), (2, 5, 7)
        ],
        [
            (0, 1, 3), (0, 3, 5), (2, 2, 4), (2, 1, 5),
            (1, 2, 3), (2, 2, 3), (2, 1, 2)
        ],
        [
            (0, 10, 20), (0, 30, 40), (2, 15, 35), (2, 30, 40),
            (1, 35, 37), (2, 36, 37), (0, 35, 37), (2, 32, 38)
        ],
        [
            (0, 1, 2), (1, 1, 2), (2, 1, 2), (0, 1, 6),
            (2, 1, 6), (1, 2, 5), (2, 1, 2), (2, 5, 6), (2, 2, 5)
        ],
        [
            (0, 100000000, 200000000), (0, 150000000, 250000000),
            (1, 120000000, 130000000), (2, 110000000, 115000000),
            (2, 120000000, 130000000), (2, 200000000, 250000000)
        ],
        [
            (0, 1, 2), (0, 2, 3), (0, 3, 4), (0, 4, 5),
            (1, 2, 4), (0, 2, 4), (2, 1, 5), (2, 1, 6), (1, 1, 5), (2, 1, 2)
        ],
        [
            (0, 10, 15), (0, 12, 14), (2, 11, 13), (1, 13, 14),
            (2, 13, 14), (0, 13, 14), (2, 10, 15)
        ],
        [
            (0, 50, 60), (1, 40, 45), (2, 50, 60), (1, 55, 65),
            (2, 55, 60), (2, 50, 55)
        ],
        [
            (0, 5, 7), (0, 20, 25), (0, 8, 10), (0, 7, 8),
            (2, 6, 9), (1, 6, 9), (2, 5, 6), (2, 6, 9), (2, 9, 10),
            (0, 15, 18), (2, 15, 20), (0, 10, 15), (2, 12, 17),
            (1, 17, 22), (2, 21, 23), (2, 22, 23)
        ],
        [
            (0, 1, 3), (0, 3, 5), (0, 7, 9), (2, 5, 7),
            (0, 5, 7), (1, 4, 8), (2, 1, 4), (2, 4, 8), (2, 8, 9)
        ]
    ]

    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for test in tests:
            rm = RangeModule()
            for op in test:
                t, l, r = op
                if t == 0:
                    rm.addRange(l, r)
                elif t == 1:
                    rm.removeRange(l, r)
                elif t == 2:
                    rm.queryRange(l, r)
                        # checksum += 1
        #sink = checksum
    # print sink