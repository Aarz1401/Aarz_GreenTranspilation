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
    tests = [
        [1, 2, 3, 4],
        [1, 1, 1, 2],
        [1, 3, 5, 7],
        [1, 3, 2, 6, 5, 4],
        [0, 2, 4, 3, 1],
        [9998, 10000, 9999],
        [10, 100, 1000, 10000],
        [1, 4, 7, 2, 3, 5, 6],
        [5, 5, 7, 9, 8, 6],
        [42]
    ]

    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for tc in tests:
            sr = SummaryRanges()
            for v in tc:
                sr.addNum(v)
            res = sr.getIntervals()
            #checksum += int(len(res))
        #     for r in res:
        #         checksum += r.start + r.end
        # sink = checksum