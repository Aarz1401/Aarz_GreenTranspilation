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
    tests = [
        # 1) Single rectangle (true)
        [[0, 0, 2, 3]],
        # 2) 2x2 covered by four 1x1 tiles (true)
        [[0, 0, 1, 1], [1, 0, 2, 1], [0, 1, 1, 2], [1, 1, 2, 2]],
        # 3) Overlapping rectangles (false)
        [[0, 0, 2, 2], [1, 1, 3, 3]],
        # 4) Gap: three of the four tiles (false)
        [[0, 0, 1, 1], [1, 0, 2, 1], [0, 1, 1, 2]],
        # 5) Duplicate rectangle (false)
        [[0, 0, 1, 1], [0, 0, 1, 1]],
        # 6) Mixed tiling covering [0,0,3,2] (true)
        [[0, 0, 1, 2], [1, 0, 2, 1], [1, 1, 2, 2], [2, 0, 3, 2]],
        # 7) Negative coordinates perfect cover [-3,-1,2,3] (true)
        [[-3, -1, -1, 3], [-1, -1, 2, 1], [-1, 1, 2, 3]],
        # 8) Large coordinates within typical constraints (true)
        [[10000, 10000, 15000, 15000], [15000, 10000, 20000, 15000],
         [10000, 15000, 15000, 20000], [15000, 15000, 20000, 20000]],
        # 9) Another perfect cover [0,0,4,3] (true)
        [[0, 0, 1, 3], [1, 0, 4, 1], [1, 1, 4, 3]],
        # 10) Gap near edge in [0,0,3,2] (false)
        [[0, 0, 2, 2], [2, 0, 3, 1]],
    ]

    sol = Solution()

    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for recs in tests:
            checksum += sol.isRectangleCover(recs)
        sink += checksum
    print(sink)