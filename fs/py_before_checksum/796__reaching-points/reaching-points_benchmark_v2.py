# Time:  O(log(max(m, n)))
# Space: O(1)

class Solution(object):
    def reachingPoints(self, sx, sy, tx, ty):
        """
        :type sx: int
        :type sy: int
        :type tx: int
        :type ty: int
        :rtype: bool
        """
        while tx >= sx and ty >= sy:
            if tx < ty:
                sx, sy = sy, sx
                tx, ty = ty, tx
            if ty > sy:
                tx %= ty
            else:
                return (tx - sx) % ty == 0

        return False

if __name__ == "__main__":
    sol = Solution()
    tests = [
        (1, 1, 3, 5),           # true
        (1, 1, 2, 2),           # false
        (1, 3, 10, 3),          # true
        (3, 1, 3, 10),          # true
        (1, 1, 1000000000, 1),  # true
        (2, 3, 1000000000, 1000000000), # false
        (5, 7, 33, 7),          # true
        (9, 5, 58, 37),         # false
        (3, 7, 2, 100),         # false
        (2, 4, 30, 4)           # true
    ]

    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += 1 if sol.reachingPoints(t[0], t[1], t[2], t[3]) else 0
        sink += checksum
    print(sink)
    # print sink