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
    import time

    sx_cases = [1, 1, 5, 2, 7, 4, 5, 1, 5, 4]
    sy_cases = [1, 1, 8, 3, 13, 10, 7, 2, 11, 1]
    tx_cases = [3, 2, 5, 5, 1000000008, 1000000009, 20, 999999937, 1000000002, 1000000000]
    ty_cases = [5, 2, 8, 8, 13, 1000000015, 6, 2, 11, 1]

    checksum = 0L

    start = time.time()
    iterations = 1000
    sol = Solution()
    for iter in xrange(iterations):
        for i in xrange(10):
            sx = sx_cases[i]
            sy = sy_cases[i]
            tx = tx_cases[i]
            ty = ty_cases[i]
            res = sol.reachingPoints(sx, sy, tx, ty)
            if res:
                checksum += (i + 1)
    end = time.time()

    elapsed_ms = (end - start) * 1000.0
    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms