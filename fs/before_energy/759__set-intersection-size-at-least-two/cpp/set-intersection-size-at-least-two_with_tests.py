# Time:  O(nlogn)
# Space: O(n)

class Solution(object):
    def intersectionSizeTwo(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key = lambda s_e: (s_e[0], -s_e[1]))
        cnts = [2] * len(intervals)
        result = 0
        while intervals:
            (start, _), cnt = intervals.pop(), cnts.pop()
            for s in xrange(start, start+cnt):
                for i in xrange(len(intervals)):
                    if cnts[i] and s <= intervals[i][1]:
                        cnts[i] -= 1
            result += cnt
        return result


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs
    tests = []

    # 1) Small overlapping intervals
    tests.append([
        [1, 3], [1, 4], [2, 5], [3, 5], [2, 3]
    ])

    # 2) Overlapping chain of intervals
    t = []
    for i in range(20):
        t.append([i, i + 2])
    tests.append(t)

    # 3) Disjoint intervals (each needs its own two points)
    t = []
    for i in range(15):
        start = i * 3
        t.append([start, start + 1])
    tests.append(t)

    # 4) Nested intervals (descending ends)
    t = []
    for e in range(20, 9, -1):
        t.append([1, e])
    tests.append(t)

    # 5) Many identical intervals
    t = []
    for i in range(30):
        t.append([5, 15])
    tests.append(t)

    # 6) Patterned intervals using modular arithmetic
    t = []
    for i in range(50):
        start = (i * 7) % 60
        length = (i % 5) + 2
        t.append([start, start + length])
    tests.append(t)

    # 7) High value intervals (to test large numbers)
    t = []
    base = 1000000000
    for i in range(30):
        s = base + i * 3
        e = s + 5
        t.append([int(s), int(e)])
    tests.append(t)

    # 8) Intervals with negative starts
    t = []
    for i in range(20):
        start = -50 + i * 3
        t.append([start, start + 10])
    tests.append(t)

    # 9) Single interval
    tests.append([
        [10, 20]
    ])

    # 10) Mixed assorted intervals
    tests.append([
        [0, 100], [20, 30], [25, 35], [40, 90], [85, 95],
        [50, 51], [60, 70], [65, 66], [67, 80], [10, 12], [11, 13], [12, 14]
    ])

    sol = Solution()
    checksum = 0

    start_time = time.time()
    iterations = 1000
    for _ in range(iterations):
        for i in range(len(tests)):
            intervals = [pair[:] for pair in tests[i]]  # deep copy since the function may mutate input
            checksum += sol.intersectionSizeTwo(intervals)
    end_time = time.time()

    elapsed_us = int(round((end_time - start_time) * 1000000.0))
    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us