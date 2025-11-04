```python
# Time:  addNum: O(n), getIntervals: O(n), n is the number of disjoint intervals.
# Space: O(n)

class Interval(object):
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e


class SummaryRanges(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.__intervals = []

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        def upper_bound(nums, target):
            left, right = 0, len(nums) - 1
            while left <= right:
                mid = left + (right - left) / 2
                if nums[mid].start > target:
                    right = mid - 1
                else:
                    left = mid + 1
            return left

        i = upper_bound(self.__intervals, val)
        start, end = val, val
        if i != 0 and self.__intervals[i-1].end + 1 >= val:
            i -= 1
        while i != len(self.__intervals) and \
              end + 1 >= self.__intervals[i].start:
            start = min(start, self.__intervals[i].start)
            end = max(end, self.__intervals[i].end)
            del self.__intervals[i]
        self.__intervals.insert(i, Interval(start, end))

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        return self.__intervals


if __name__ == "__main__":
    import time

    INT_MIN = -2147483648
    INT_MAX = 2147483647

    # Define 10 diverse test inputs
    tests = [
        [1,2,3,4,5,6,7,8,9,10],                 # increasing consecutive
        [1,3,7,2,6],                             # random with gaps and merges
        [5,5,6,4,4,7],                           # duplicates and merges
        [10,9,8,7,6,5],                          # decreasing order
        [INT_MIN, INT_MIN+1, INT_MAX-1, INT_MAX],# extremes
        [1,2,4,5,3],                             # connect two intervals into one
        [100,101,102,101,100,102],               # insert within existing interval and duplicates
        [0,0,1000,1000,-1,-1,1,1],               # scattered with duplicates
        [2,4,6,8,10,12],                         # multiple non-overlapping singles
        [50,52,54,53,51,55,49,48,47]             # merges into a large interval in mixed order
    ]

    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for seq in tests:
            sr = SummaryRanges()
            half = len(seq) // 2
            for i in xrange(len(seq)):
                sr.addNum(seq[i])
                if i == half:
                    ivs_mid = sr.getIntervals()
                    checksum += len(ivs_mid)
                    if ivs_mid:
                        checksum += (ivs_mid[0].start ^ ivs_mid[-1].end)
            ivs = sr.getIntervals()
            for iv in ivs:
                checksum += ((iv.start * 1315423911) ^ iv.end)
            checksum += len(ivs)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (microseconds): %d" % (elapsed_us,)
```