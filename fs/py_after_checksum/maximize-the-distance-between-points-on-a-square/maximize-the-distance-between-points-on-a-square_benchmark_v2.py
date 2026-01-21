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
    tests = [
        {'side': 10, 'points': [(0,0),(0,5),(0,10),(4,10),(10,10),(10,7),(10,3),(6,0),(3,0),(10,0)], 'k': 1},
        {'side': 10, 'points': [(0,0),(10,0)], 'k': 2},
        {'side': 5,  'points': [(0,0),(0,5),(5,5),(5,0),(0,3),(2,5),(5,2),(3,0)], 'k': 3},
        {'side': 1000, 'points': [(0,500),(250,1000),(1000,250),(500,0),(1000,999),(1,0),(0,1),(999,1000)], 'k': 4},
        {'side': 7,  'points': [(3,0,)], 'k': 2},
        {'side': 12, 'points': [(1,0),(3,0),(6,0),(8,0),(11,0)], 'k': 3},
        {'side': 9,  'points': [(0,0),(0,9),(9,9),(9,0)], 'k': 4},
        {'side': 20, 'points': [(0,10),(5,20),(20,15),(10,0),(0,1),(19,20),(20,1),(1,0),(0,19),(15,20),(20,19),(19,0)], 'k': 8},
        {'side': 3,  'points': [(0,0),(3,0),(0,3),(1,0),(3,2)], 'k': 2},
        {'side': 50, 'points': [(0,0),(0,25),(0,50),(25,50),(50,50),(50,25),(50,0),(25,0),(10,50),(40,0),(0,10),(50,40),(5,0),(0,5)], 'k': 5}
    ]

    s = Solution()
    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += s.maxDistance(t['side'], t['points'], t['k'])
        sink += checksum
    print(sink)
    # print sink