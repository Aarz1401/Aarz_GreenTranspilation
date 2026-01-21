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
    import time

    tests = []

    # Test 1: Basic add and queries with adjacency merge
    tests.append([
        ('Add', 10, 20),
        ('Query', 10, 15),
        ('Query', 15, 25),
        ('Add', 20, 25),
        ('Query', 18, 22),
    ])

    # Test 2: Overlapping adds forming a chain and a split by remove
    tests.append([
        ('Add', 5, 7),
        ('Add', 1, 3),
        ('Add', 2, 6),
        ('Query', 1, 7),
        ('Remove', 3, 4),
        ('Query', 3, 4),
        ('Query', 2, 3),
    ])

    # Test 3: Remove entire coverage and re-add
    tests.append([
        ('Add', 0, 100),
        ('Remove', 0, 100),
        ('Query', 0, 1),
        ('Add', 50, 60),
        ('Query', 55, 56),
    ])

    # Test 4: Non-merging adjacency then bridging add and split remove
    tests.append([
        ('Add', 30, 40),
        ('Add', 41, 50),
        ('Query', 40, 41),
        ('Add', 40, 41),
        ('Query', 30, 50),
        ('Remove', 35, 45),
        ('Query', 34, 36),
        ('Query', 30, 35),
    ])

    # Test 5: Empty structure queries and zero-length intervals behavior
    tests.append([
        ('Query', 1, 2),
        ('Add', 1, 1),
        ('Query', 1, 1),
        ('Remove', 1, 1),
        ('Query', 1, 1),
    ])

    # Test 6: Extreme integer boundaries and small removals
    INT_MIN = -2147483648
    INT_MAX = 2147483647
    tests.append([
        ('Add', INT_MIN + 10, INT_MIN + 20),
        ('Add', INT_MAX - 20, INT_MAX - 10),
        ('Query', INT_MIN + 11, INT_MIN + 19),
        ('Query', INT_MAX - 15, INT_MAX - 10),
        ('Remove', INT_MIN + 15, INT_MIN + 16),
        ('Query', INT_MIN + 15, INT_MIN + 16),
    ])

    # Test 7: Many small disjoint adds, then a large merge, then a split
    t7 = []
    for i in range(0, 20, 2):
        t7.append(('Add', i, i + 1))
    t7.append(('Add', 0, 20))
    t7.append(('Remove', 5, 15))
    t7.append(('Query', 0, 5))
    t7.append(('Query', 15, 20))
    t7.append(('Query', 10, 12))
    tests.append(t7)

    # Test 8: Bridging add across a removed gap and complete removal
    tests.append([
        ('Add', 100, 200),
        ('Remove', 120, 180),
        ('Add', 110, 190),
        ('Query', 150, 160),
        ('Remove', 90, 210),
        ('Query', 100, 101),
    ])

    # Test 9: Nibbling edges via multiple removes
    tests.append([
        ('Add', 0, 100),
        ('Remove', 0, 10),
        ('Remove', 90, 100),
        ('Remove', 50, 60),
        ('Remove', 10, 11),
        ('Query', 11, 50),
        ('Query', 59, 61),
        ('Query', 60, 90),
    ])

    # Test 10: Duplicate adds, nested add, and middle removal
    tests.append([
        ('Add', 5, 10),
        ('Add', 5, 10),
        ('Add', 6, 9),
        ('Query', 5, 10),
        ('Remove', 7, 8),
        ('Query', 7, 8),
        ('Query', 6, 7),
        ('Query', 8, 9),
    ])

    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for test in tests:
            rm = RangeModule()
            for op in test:
                typ, l, r = op
                if typ == 'Add':
                    rm.addRange(l, r)
                elif typ == 'Remove':
                    rm.removeRange(l, r)
                elif typ == 'Query':
                    if rm.queryRange(l, r):
                        checksum += 1

    end = time.time()
    elapsed_ns = long((end - start) * 1e9)

    print "Checksum:", checksum
    print "Elapsed time (ns):", elapsed_ns