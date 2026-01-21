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


if __name__ == "__main__":
    from timeit import default_timer as timer

    sol = Solution()

    tests = [
        {'sx': 5, 'sy': 7, 'tx': 5, 'ty': 7},                 # already at target
        {'sx': 0, 'sy': 1, 'tx': 4, 'ty': 4},                 # reachable via sx == 0 path
        {'sx': 3, 'sy': 0, 'tx': 12, 'ty': 12},               # reachable via sy == 0 path
        {'sx': 5, 'sy': 2, 'tx': 4, 'ty': 5},                 # unreachable: source > target in x
        {'sx': 1, 'sy': 1, 'tx': 2, 'ty': 3},                 # likely unreachable due to parity/equality constraints
        {'sx': 0, 'sy': 2, 'tx': 32, 'ty': 32},               # reachable via halving y to source
        {'sx': 8, 'sy': 0, 'tx': 32, 'ty': 32},               # reachable via halving x to source
        {'sx': 1, 'sy': 2, 'tx': 1000000, 'ty': 1000001},     # large values, expected -1 eventually
        {'sx': 2, 'sy': 2, 'tx': 50, 'ty': 100},              # general case
        {'sx': 0, 'sy': 0, 'tx': 0, 'ty': 0}                  # trivial
    ]

    checksum = 0

    start = timer()
    iterations = 1
    for _ in xrange(iterations):
        for tc in tests:
            checksum += sol.minMoves(tc['sx'], tc['sy'], tc['tx'], tc['ty'])
    end = timer()

    elapsed_ns = int(round((end - start) * 1e9))

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns