# Time:  O(nlogn)
# Space: O(n)

# Monotone Chain Algorithm
# Template: https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#Python
class Solution(object):
    def outerTrees(self, points):
        """
        :type points: List[List[int]]
        :rtype: List[List[int]]
        """
        # Sort the points lexicographically (tuples are compared lexicographically).
        # Remove duplicates to detect the case we have just one unique point.
        points = sorted(set(tuple(x) for x in points))

        # Boring case: no points or a single point, possibly repeated multiple times.
        if len(points) <= 1:
            return points

        # 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
        # Returns a positive value, if OAB makes a counter-clockwise turn,
        # negative for clockwise turn, and zero if the points are collinear.
        def cross(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

        # Build lower hull 
        lower = []
        for p in points:
            while len(lower) >= 2 and cross(lower[-2], lower[-1], p) < 0:  # modified
                lower.pop()
            lower.append(p)

        # Build upper hull
        upper = []
        for p in reversed(points):
            while len(upper) >= 2 and cross(upper[-2], upper[-1], p) < 0:  # modified
                upper.pop()
            upper.append(p)

        # Concatenation of the lower and upper hulls gives the convex hull.
        # Last point of each list is omitted because it is repeated at the beginning of the other list. 
        result = lower[:-1] + upper[:-1]
        return result if result[1] != result[-1] else result[:len(result)//2+1]  # modified

if __name__ == "__main__":
    from time import time

    t1 = [
        [0,0], [1,1], [2,0]
    ]

    t2 = [
        [0,0], [0,5], [5,5], [5,0], [2,0], [3,5], [0,2], [5,3], [2,2], [0,0], [5,5]
    ]

    t3 = [
        [0,0], [1,1], [2,2], [3,3], [4,4], [5,5], [6,6], [3,3], [2,2]
    ]

    t4 = [
        [42,-7]
    ]

    t5 = [
        [-1,-1], [-3,-3]
    ]

    t6 = [
        [0,10], [2,2], [10,0], [2,-2], [0,-10], [-2,-2], [-10,0], [-2,2], [0,0], [4,0], [-4,0]
    ]

    t7 = [
        [10,0], [8,6], [6,8], [0,10], [-6,8], [-8,6], [-10,0], [-8,-6], [-6,-8], [0,-10],
        [6,-8], [8,-6], [7,7], [-7,7], [-7,-7], [7,-7], [0,0], [3,4], [-3,-4]
    ]

    t8 = [
        [-100,-100], [-110,-90], [-120,-110], [-90,-120], [-95,-105], [-105,-95],
        [-130,-100], [-100,-130], [-80,-100], [-100,-80], [-90,-90], [-110,-110]
    ]

    t9 = []
    for x in range(0, 11):
        t9.append([x, 0])
        t9.append([x, 10])
    for y in range(1, 10):
        t9.append([0, y])
        t9.append([10, y])
    t9.append([5,5])
    t9.append([3,7])
    t9.append([7,3])
    t9.append([5,5])  # duplicate

    t10 = [
        [1,1], [1,1], [1,1], [0,0], [0,0], [2,2], [2,2], [2,2], [0,2], [2,0], [-1,-1], [-1,2], [2,-1]
    ]

    tests = [t1, t2, t3, t4, t5, t6, t7, t8, t9, t10]

    sol = Solution()

    checksum = 0L
    start = time()
    iterations = 1000
    for iter in range(iterations):
        for base in tests:
            input_pts = [p[:] for p in base]
            hull = sol.outerTrees(input_pts)
            for p in hull:
                checksum += (long(p[0]) * 1000003L) ^ (long(p[1]) * 911L + 1L)
            checksum += long(len(hull))
    end = time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms