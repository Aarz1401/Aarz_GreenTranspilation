# Time:  O(nlogn)
# Space: O(k), k is the number of courses you can take

import collections
import heapq


class Solution(object):
    def scheduleCourse(self, courses):
        """
        :type courses: List[List[int]]
        :rtype: int
        """
        courses.sort(key=lambda t_end: t_end[1])
        max_heap = []
        now = 0
        for t, end in courses:
            now += t
            heapq.heappush(max_heap, -t)
            if now > end:
                now += heapq.heappop(max_heap)
        return len(max_heap)


if __name__ == "__main__":
    import time

    tests = []

    # 1. Empty input
    tests.append([])

    # 2. Single feasible course
    tests.append([[1, 2]])

    # 3. Single infeasible course
    tests.append([[3, 2]])

    # 4. Typical sample set
    tests.append([[100, 200], [200, 1300], [1000, 1250], [2000, 3200]])

    # 5. Identical deadlines, varying durations
    tests.append([[5, 5], [4, 5], [3, 5], [2, 5], [1, 5]])

    # 6. Tight and overlapping deadlines
    tests.append([[2, 2], [2, 2], [3, 3], [1, 2], [2, 3]])

    # 7. All feasible: deadlines are prefix sums
    t = []
    for i in range(1, 11):
        t.append([i, i * (i + 1) / 2])
    tests.append(t)

    # 8. Larger mixed set (50 items) with varying durations and deadlines
    t = []
    for i in range(50):
        dur = (i * 7) % 10 + 1
        ddl = (i * 13) % 50 + dur + 5
        t.append([dur, ddl])
    tests.append(t)

    # 9. Heavy durations close to deadlines (30 items)
    t = []
    for i in range(30):
        dur = 90 + (i % 21)
        ddl = 100 + ((i * 17) % 21)
        t.append([dur, ddl])
    tests.append(t)

    # 10. Decreasing deadlines (20 items)
    t = []
    for i in range(20):
        dur = (i % 10) + 1
        ddl = 100 - i * 3
        t.append([dur, ddl])
    tests.append(t)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in range(iterations):
        for i in range(len(tests)):
            courses = [c[:] for c in tests[i]]  # copy, since scheduleCourse sorts in-place
            result = sol.scheduleCourse(courses)
            checksum += result * (i + 1)

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us