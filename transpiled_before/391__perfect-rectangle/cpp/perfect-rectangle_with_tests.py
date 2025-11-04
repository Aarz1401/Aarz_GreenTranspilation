# Time:  O(n)
# Space: O(n)

from collections import defaultdict

class Solution(object):
    def isRectangleCover(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        left = min(rec[0] for rec in rectangles)
        bottom = min(rec[1] for rec in rectangles)
        right = max(rec[2] for rec in rectangles)
        top = max(rec[3] for rec in rectangles)

        points = defaultdict(int)
        for l, b, r, t in rectangles:
            for p, q in zip(((l, b), (r, b), (l, t), (r, t)), (1, 2, 4, 8)):
                if points[p] & q:
                    return False
                points[p] |= q

        for px, py in points:
            if left < px < right or bottom < py < top:
                if points[(px, py)] not in (3, 5, 10, 12, 15):
                    return False

        return True


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    tests = []

    # 0: Two rectangles forming a perfect 2x2 rectangle vertically
    tests.append([
        [1, 1, 3, 2],
        [1, 2, 3, 3]
    ])

    # 1: Complex valid tiling (LeetCode-style valid example)
    tests.append([
        [1,1,3,3],
        [3,1,4,2],
        [3,2,4,4],
        [1,3,2,4],
        [2,3,3,4],
        [1,1,2,2],
        [2,2,3,3],
        [1,2,2,3],
        [2,1,3,2]
    ])

    # 2: Overlapping rectangles (invalid)
    tests.append([
        [1,1,2,3],
        [1,3,2,4],
        [3,1,4,2],
        [2,2,4,4]
    ])

    # 3: Hole in the middle (invalid)
    tests.append([
        [1,1,3,3],
        [3,1,4,2],
        [3,2,4,4],
        [1,3,2,4],
        [2,3,3,4],
        [1,1,2,2],
        [1,2,2,3],
        [2,1,3,2]
    ])

    # 4: Four rectangles forming a 2x2 square (valid)
    tests.append([
        [0,0,1,1],
        [1,0,2,1],
        [0,1,1,2],
        [1,1,2,2]
    ])

    # 5: Single rectangle (valid)
    tests.append([
        [5,5,10,10]
    ])

    # 6: Duplicate identical rectangles (invalid)
    tests.append([
        [0,0,1,1],
        [0,0,1,1]
    ])

    # 7: Negative coordinates, two rectangles side-by-side (valid)
    tests.append([
        [-3,-1,-1,1],
        [-1,-1,1,1]
    ])

    # 8: Disjoint rectangles (likely invalid)
    tests.append([
        [0,0,1,1],
        [2,0,3,1]
    ])

    # 9: Large coordinates tiling a big rectangle with 10 vertical stripes (valid)
    big = []
    x0 = 100000000
    y0 = 200000000
    for i in range(10):
        big.append([x0 + i, y0, x0 + i + 1, y0 + 5])
    tests.append(big)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    MASK64 = (1 << 64) - 1
    for iter in range(iterations):
        for i in range(len(tests)):
            res = sol.isRectangleCover(tests[i])
            val = (1 if res else 0) + i + len(tests[i])
            checksum = ((checksum * 1315423911) ^ (val & MASK64)) & MASK64

    end = time.time()
    ns = int((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % ns