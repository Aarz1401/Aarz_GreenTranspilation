
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
        return binary_search_right(1, 4*side//k, check)


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
        return binary_search_right(1, 4*side//k, check)


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
            result = binary_search_right(result+1, 4*side//k, lambda x: check(i, x))
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
        return binary_search_right(1, 4*side//k, check)


if __name__ == "__main__":
    import time

    tests = []

    # 1. Corners of a 10x10 square, moderate k
    tests.append({
        'side': 10,
        'points': [(0,0),(0,10),(10,10),(10,0)],
        'k': 2
    })

    # 2. Small side=1, all four corners/edges, higher k
    tests.append({
        'side': 1,
        'points': [(0,0),(0,1),(1,1),(1,0)],
        'k': 3
    })

    # 3. Mixed positions on all edges, side=50
    tests.append({
        'side': 50,
        'points': [(0,17),(12,50),(50,49),(33,0),(50,1),(0,25),(25,50),(50,25)],
        'k': 4
    })

    # 4. Single point, k=1
    tests.append({
        'side': 5,
        'points': [(0,3)],
        'k': 1
    })

    # 5. Many points on bottom edge, larger side and k
    tests.append({
        'side': 100,
        'points': [(0,0),(10,0),(20,0),(30,0),(40,0),(50,0),(60,0),(70,0),(80,0),(90,0),(100,0)],
        'k': 5
    })

    # 6. Duplicates and corners on side=7
    tests.append({
        'side': 7,
        'points': [(0,0),(0,0),(7,7),(7,7),(3,7),(7,3),(0,7)],
        'k': 3
    })

    # 7. Mixed across edges, side=12
    tests.append({
        'side': 12,
        'points': [(0,6),(4,12),(12,8),(8,0),(12,4),(0,0)],
        'k': 4
    })

    # 8. Large side, sparse points
    tests.append({
        'side': 1000,
        'points': [(0,0),(0,1000),(1000,1000),(1000,0),(500,1000),(1000,500)],
        'k': 2
    })

    # 9. Dense small square, many perimeter points
    tests.append({
        'side': 2,
        'points': [(0,0),(0,1),(0,2),(1,2),(2,2),(2,1),(2,0),(1,0)],
        'k': 4
    })

    # 10. Empty points with k=0 (early return path)
    tests.append({
        'side': 3,
        'points': [],
        'k': 0
    })

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            t = tests[i]
            try:
                res = sol.maxDistance(t['side'], t['points'], t['k'])
            except Exception:
                res = 0
            checksum += (int(res) ^ int(i) ^ int(iter))

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: " + str(checksum)
    print "Elapsed time (ms): " + str(elapsed_ms)
