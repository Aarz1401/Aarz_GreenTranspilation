
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
    tests = [
        [[5, 5]],
        [[0, 0], [3, 4]],
        [[0, 0], [1, 1], [2, 2], [3, 3], [4, 4]],
        [[0, 0], [0, 10], [10, 10], [10, 0]],
        [[0, 0], [2, 0], [4, 0], [4, 2], [4, 4], [2, 4], [0, 4], [0, 2], [2, 2], [2, 0], [0, 4]],
        [[50, 60], [57, 57], [60, 50], [57, 43], [50, 40], [43, 43], [40, 50], [43, 57], [50, 50], [55, 50]],
        [[0, 0], [2, 0], [4, 0], [6, 0], [8, 0], [10, 0], [0, 5], [5, 7], [10, 5], [5, 0]],
        [[1, 3], [2, 8], [3, 3], [5, 5], [7, 2], [6, 9], [10, 10], [12, 1], [9, 4], [4, 7]],
        [[10, 0], [20, 5], [20, 15], [10, 20], [0, 15], [0, 5], [10, 10], [5, 10], [15, 10], [10, 5]],
        [[0, 0], [20, 0], [40, 0], [60, 0], [80, 0], [100, 0], [100, 10], [80, 10], [60, 10], [40, 10], [20, 10], [0, 10], [50, 0], [50, 10]]
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for i in xrange(len(tests)):
            pts = [p[:] for p in tests[i]]
            out = sol.outerTrees(pts)
            for p in out:
                checksum += p[0] + p[1]
        sink += checksum
    print(sink)

    # print sink
