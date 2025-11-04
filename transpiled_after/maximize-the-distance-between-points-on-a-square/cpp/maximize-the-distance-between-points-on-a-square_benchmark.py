# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn + nlogs), s = side
# Space: O(n)

# sort, binary search, greedy, two pointers, sliding window
class Solution(object):
    def maxDistance(self, side, points, k):
        """
        :type side: int
        :type points: List[List[int]]
        :type k: int
        :rtype: int
        """
        if k <= 0 or not points:
            return 0
        def binary_search_right(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if not check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return right

        def check(d):
            intervals = [(0, 0, 1)]
            i = 0
            for right in xrange(1, len(p)):
                left, cnt = right, 1
                while i < len(intervals):
                    l, r, c = intervals[i]
                    if p[right]-p[r] < d:
                        break
                    if (p[l]+4*side)-p[right] >= d:
                        if c+1 >= cnt:
                            cnt = c+1
                            left = l
                    i += 1
                intervals.append((left, right, cnt))
            return max(x[2] for x in intervals) >= k

        p = []
        for x, y in points:
            if x == 0:
                p.append(0*side+y)
            elif y == side:
                p.append(1*side+x)
            elif x == side:
                p.append(2*side+(side-y))
            else:
                p.append(3*side+(side-x))
        p.sort()
        upper = 4*side//k if k > 0 else 0
        return binary_search_right(1, upper, check)


# Time:  O(nlogn + nlogs), s = side
# Space: O(n)
# sort, binary search, greedy, two pointers, sliding window
class Solution2(object):
    def maxDistance(self, side, points, k):
        """
        :type side: int
        :type points: List[List[int]]
        :type k: int
        :rtype: int
        """
        if k <= 0 or not points:
            return 0
        def binary_search_right(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if not check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return right

        def check(d):
            intervals = [(0, 0, 1)]
            i = 0
            for right in xrange(1, len(sorted_points)):
                left, cnt = right, 1
                while i < len(intervals):
                    l, r, c = intervals[i]
                    if abs(sorted_points[right][0]-sorted_points[r][0])+abs(sorted_points[right][1]-sorted_points[r][1]) < d:
                        break
                    if abs(sorted_points[right][0]-sorted_points[l][0])+abs(sorted_points[right][1]-sorted_points[l][1]) >= d:
                        if c+1 >= cnt:
                            cnt = c+1
                            left = l
                    i += 1
                intervals.append((left, right, cnt))
            return max(x[2] for x in intervals) >= k

        p = [[] for _ in xrange(4)]
        for x, y in points:
            if x == 0:
                p[0].append((x, y))
            elif y == side:
                p[1].append((x, y))
            elif x == side:
                p[2].append((x, y))
            else:
                p[3].append((x, y))
        p[0].sort()
        p[1].sort()
        p[2].sort(reverse=True)
        p[3].sort(reverse=True)
        sorted_points = [x for i in xrange(4) for x in p[i]]
        upper = 4*side//k if k > 0 else 0
        return binary_search_right(1, upper, check)


# Time:  O(nlogn + n * (k * logn) * logs), s = side
# Space: O(n)
import bisect


# sort, binary search, greedy
class Solution3(object):
    def maxDistance(self, side, points, k):
        """
        :type side: int
        :type points: List[List[int]]
        :type k: int
        :rtype: int
        """
        if k <= 0 or not points:
            return 0
        def binary_search_right(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if not check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return right

        def check(i, d):
            j = i
            for _ in xrange(k-1):
                j = bisect.bisect_left(p, p[j]+d, lo=j+1)
                if j == len(p):
                    return False
            return (p[i]+4*side)-p[j] >= d

        p = []
        for x, y in points:
            if x == 0:
                p.append(0*side+y)
            elif y == side:
                p.append(1*side+x)
            elif x == side:
                p.append(2*side+(side-y))
            else:
                p.append(3*side+(side-x))
        p.sort()
        result = 1
        for i in xrange(len(p)-k+1):
            if p[-1]-p[i] <= result*(k-1):  # to speed up
                break
            upper = 4*side//k if k > 0 else 0
            result = binary_search_right(result+1, upper, lambda x: check(i, x))
        return result


# Time:  O(nlogn + (n * k * logn) * logs), s = side
# Space: O(n)
import bisect


# sort, binary search, greedy
class Solution4(object):
    def maxDistance(self, side, points, k):
        """
        :type side: int
        :type points: List[List[int]]
        :type k: int
        :rtype: int
        """
        if k <= 0 or not points:
            return 0
        def binary_search_right(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if not check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return right

        def check(d):
            for i in xrange(len(points)):
                j = i
                for _ in xrange(k-1):
                    j = bisect.bisect_left(p, p[j]+d, lo=j+1, hi=i+len(points))
                    if j == i+len(points):
                        break
                else:
                    if p[i+len(points)]-p[j] >= d:
                        return True
            return False

        p = []
        for x, y in points:
            if x == 0:
                p.append(0*side+y)
            elif y == side:
                p.append(1*side+x)
            elif x == side:
                p.append(2*side+(side-y))
            else:
                p.append(3*side+(side-x))
        p.sort()
        p += [x+4*side for x in p]
        upper = 4*side//k if k > 0 else 0
        return binary_search_right(1, upper, check)

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Mixed edges and corners
        (10,
         [(0, 0), (0, 5), (10, 10), (10, 5), (5, 10), (5, 0)],
         3),
        # 2) All points on left edge, dense
        (7,
         [(0, 0), (0, 1), (0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (0, 7)],
         4),
        # 3) Bottom edge only
        (12,
         [(1, 0), (5, 0), (6, 0), (11, 0)],
         2),
        # 4) Right edge with duplicates
        (9,
         [(9, 0), (9, 3), (9, 9), (9, 9)],
         3),
        # 5) Spread across all edges
        (100,
         [(0, 20), (0, 80),
          (30, 100), (70, 100),
          (100, 90), (100, 10),
          (90, 0), (10, 0)],
         5),
        # 6) Minimal square with all corners
        (1,
         [(0, 0), (0, 1), (1, 1), (1, 0)],
         2),
        # 7) No points
        (50,
         [],
         4),
        # 8) Mixed edges including a corner
        (8,
         [(0, 2), (0, 7), (3, 8), (8, 6), (4, 0), (8, 0)],
         4),
        # 9) k = 0 edge case
        (13,
         [(0, 0), (13, 0), (0, 13), (13, 13), (6, 13), (13, 6), (7, 0)],
         0),
        # 10) Very large side with few points, large k to keep search range small
        (1000000000,
         [(0, 0), (1000000000, 0), (0, 1000000000), (1000000000, 1000000000), (500000000, 0)],
         1000000000),
    ]

    # Warm-up
    sol = Solution4()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.maxDistance(*test)
        else:
            sol.maxDistance(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution4()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.maxDistance(*test)
            else:
                result = sol.maxDistance(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
