# Time:  O(logtx + logty)
# Space: O(1)

# backward simulation
class Solution(object):
    def minMoves(self, sx, sy, tx, ty):
        """
        :type sx: int
        :type sy: int
        :type tx: int
        :type ty: int
        :rtype: int
        """
        result = 0
        while (sx, sy) != (tx, ty):
            if not (sx <= tx and sy <= ty):
                return -1
            if tx < ty:
                if tx > ty-tx:
                    ty -= tx
                else:
                    if ty%2:
                        return -1
                    ty -= ty//2
            elif tx > ty:
                if ty > tx-ty:
                    tx -= ty
                else:
                    if tx%2:
                        return -1
                    tx -= tx//2
            else:
                if sx == 0:
                    tx -= ty
                elif sy == 0:
                    ty -= tx
                else:
                    return -1
            result += 1
        return result

if __name__ == '__main__':
    tests = [
        (0, 1, 0, 1),
        (0, 1, 2, 3),
        (0, 3, 6, 9),
        (5, 0, 20, 25),
        (0, 7, 56, 63),
        (1, 1, 3, 5),
        (2, 2, 4, 6),
        (0, 1, 536870912, 805306368),
        (7, 0, 112, 119),
        (1, 2, 1, 1)
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for sx, sy, tx, ty in tests:
            r = sol.minMoves(sx, sy, tx, ty)
        #sink = checksum

    # print sink