```python
# Time:  O(n^2)
# Space: O(n)

import collections
import random


# Definition for a point
class Point(object):
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b

class Solution(object):
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        max_points = 0
        for i, start in enumerate(points):
            slope_count, same = collections.defaultdict(int), 1
            for j in xrange(i + 1, len(points)):
                end = points[j]
                if start.x == end.x and start.y == end.y:
                    same += 1
                else:
                    slope = float("inf")
                    if start.x - end.x != 0:
                        slope = (start.y - end.y) * 1.0 / (start.x - end.x)
                    slope_count[slope] += 1

            current_max = same
            for slope in slope_count:
                current_max = max(current_max, slope_count[slope] + same)

            max_points = max(max_points, current_max)

        return max_points


def tuples_to_points(tups):
    return [Point(a, b) for (a, b) in tups]

def are_collinear(p1, p2, p3):
    return (p2.y - p1.y) * (p3.x - p1.x) == (p3.y - p1.y) * (p2.x - p1.x)

def brute_max_points(points):
    n = len(points)
    if n == 0:
        return 0
    if n == 1:
        return 1
    maxcnt = 1
    any_distinct_pair = False
    for i in xrange(n):
        for j in xrange(i + 1, n):
            if points[i].x == points[j].x and points[i].y == points[j].y:
                continue
            any_distinct_pair = True
            cnt = 0
            for k in xrange(n):
                if are_collinear(points[i], points[j], points[k]):
                    cnt += 1
            if cnt > maxcnt:
                maxcnt = cnt
    if not any_distinct_pair:
        return n
    return maxcnt

def create_tests():
    tests = []
    # Deterministic tests
    tests.append({'name': 'empty', 'points': [], 'expected': 0})
    tests.append({'name': 'single', 'points': [(0, 0)], 'expected': 1})
    tests.append({'name': 'two_points', 'points': [(0, 0), (1, 1)], 'expected': 2})
    tests.append({'name': 'three_collinear_diag', 'points': [(1, 1), (2, 2), (3, 3)], 'expected': 3})
    tests.append({'name': 'vertical_line', 'points': [(2, 0), (2, 1), (2, 2), (2, -5)], 'expected': 4})
    tests.append({'name': 'horizontal_line', 'points': [(-3, 7), (0, 7), (3, 7), (10, 7)], 'expected': 4})
    tests.append({'name': 'leetcode_example', 'points': [(1, 1), (3, 2), (5, 3), (4, 1), (2, 3), (1, 4)], 'expected': 4})
    tests.append({'name': 'duplicates_only', 'points': [(1, 1), (1, 1), (1, 1)], 'expected': 3})
    tests.append({'name': 'duplicates_with_line', 'points': [(0, 0), (0, 0), (1, 1), (2, 2)], 'expected': 4})
    tests.append({'name': 'mixed_noncollinear', 'points': [(0, 0), (1, 2), (2, 1), (3, 3)], 'expected': 2})

    # Randomized tests
    rng = random.Random(0xC0FFEE)
    for i in xrange(iterations):
        n = rng.randint(0, 8)
        tups = []
        for _ in xrange(n):
            # small range to increase chances of duplicates and collinearity
            x = rng.randint(-5, 5)
            y = rng.randint(-5, 5)
            tups.append((x, y))
        pts = tuples_to_points(tups)
        exp = brute_max_points(pts)
        tests.append({'name': 'random_%d' % i, 'points': tups, 'expected': exp})
    return tests

if __name__ == "__main__":
    iterations = 1000
    tests = create_tests()

    sol = Solution()
    total = len(tests)
    passed = 0
    for idx, t in enumerate(tests):
        pts = tuples_to_points(t['points'])
        expected = t.get('expected', brute_max_points(pts))
        result = sol.maxPoints(pts)
        ok = (result == expected)
        if ok:
            passed += 1
        else:
            print "Test #%d FAILED: %s" % (idx + 1, t.get('name', ''))
            print "  Points:", t['points']
            print "  Expected:", expected
            print "  Got     :", result
    print "Passed %d/%d tests" % (passed, total)
```