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
    tests = [
        [1],
        [1, 2],
        [2, 1, 5, 7, 2, 0, 5],
        [-5, -10, -3, -4, -1],
        [100, 100, 100, 100, 100],
        [5, 4, 3, 2, 1, 0],
        [0, -1, 1, -2, 2, -3, 3],
        [10, 20, 30, 40, 50, 60, 70, 80],
        [3, 3, 4, 2, 2, 1, 5, 5, 6],
        [7, 0, 0, 7, -7, 14, -14, 7, -7, 0]
    ]

    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            mf = MedianFinder()
            for x in t:
                mf.addNum(x)
            checksum += int(mf.findMedian())
        sink += checksum
    print(sink)