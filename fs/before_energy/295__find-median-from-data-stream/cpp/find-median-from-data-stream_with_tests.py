# Time:  O(nlogn) for total n addNums, O(logn) per addNum, O(1) per findMedian.
# Space: O(n), total space

from heapq import heappush, heappop

class MedianFinder(object):
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.__max_heap = []
        self.__min_heap = []

    def addNum(self, num):
        """
        Adds a num into the data structure.
        :type num: int
        :rtype: void
        """
        # Balance smaller half and larger half.
        if not self.__max_heap or num > -self.__max_heap[0]:
            heappush(self.__min_heap, num)
            if len(self.__min_heap) > len(self.__max_heap) + 1:
                heappush(self.__max_heap, -heappop(self.__min_heap))
        else:
            heappush(self.__max_heap, -num)
            if len(self.__max_heap) > len(self.__min_heap):
                heappush(self.__min_heap, -heappop(self.__max_heap))

    def findMedian(self):
        """
        Returns the median of current data stream
        :rtype: float
        """
        return (-self.__max_heap[0] + self.__min_heap[0]) / 2.0 \
               if len(self.__min_heap) == len(self.__max_heap) \
               else self.__min_heap[0]


if __name__ == "__main__":
    from bisect import insort

    # Prepare 10 diverse test inputs
    tests = []

    # 1) Increasing sequence 1..100
    tests.append([i for i in xrange(1, 101)])

    # 2) Decreasing sequence 100..1
    tests.append([i for i in xrange(100, 0, -1)])

    # 3) All zeros (100 elements)
    tests.append([0] * 100)

    # 4) Alternating -1 and 1 (200 elements)
    tests.append([(-1 if (i % 2 == 0) else 1) for i in xrange(200)])

    # 5) Range -50..50 (101 elements)
    tests.append([i for i in xrange(-50, 51)])

    # 6) Predefined mixed values
    tests.append([5, 3, 8, 9, 1, 4, 7, 2, 6, 0, -3, 12, -7, 15, -1, 13, -5, 11, 14, -2,
                  100, -50, 25, -25, 75, -60, 33, -33, 88, -88])

    # 7) Symmetric large magnitudes around zero (200 elements): safe sums
    v = []
    for k in xrange(100):
        v.append(-1000000 + k)
        v.append(1000000 - k)
    tests.append(v)

    # 8) Single element
    tests.append([7])

    # 9) Two elements (even count)
    tests.append([5, 10])

    # 10) Zigzag sequence
    tests.append([10, -10, 20, -20, 30, -30, 40, -40, 50, -50,
                  60, -60, 70, -70, 80, -80, 90, -90, 100, -100])

    iterations = 1000

    total_tests = len(tests)
    for ti, seq in enumerate(tests):
        mf = MedianFinder()
        sorted_list = []
        for idx, x in enumerate(seq):
            mf.addNum(x)
            insort(sorted_list, x)
            n = len(sorted_list)
            if n % 2 == 1:
                expected = sorted_list[n // 2]
            else:
                expected = (sorted_list[n // 2 - 1] + sorted_list[n // 2]) / 2.0
            got = mf.findMedian()
            if isinstance(expected, float) or isinstance(got, float):
                assert abs(got - expected) < 1e-9, 'Mismatch on test %d index %d: expected %r got %r' % (ti + 1, idx, expected, got)
            else:
                assert got == expected, 'Mismatch on test %d index %d: expected %r got %r' % (ti + 1, idx, expected, got)
        print 'Test %d passed (%d elements)' % (ti + 1, len(seq))
    print 'All tests passed!'