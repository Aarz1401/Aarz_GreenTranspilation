# Time:  O(n^2)
# Space: O(n^2)

class Solution(object):
    def canCross(self, stones):
        """
        :type stones: List[int]
        :rtype: bool
        """
        if stones[1] != 1:
            return False

        last_jump_units = {s: set() for s in stones}
        last_jump_units[1].add(1)
        for s in stones[:-1]:
            for j in last_jump_units[s]:
                for k in (j-1, j, j+1):
                    if k > 0 and s+k in last_jump_units:
                        last_jump_units[s+k].add(k)
        return bool(last_jump_units[stones[-1]])


if __name__ == "__main__":
    import time

    tests = [
        [0],
        [0, 1],
        [0, 2],
        [0, 1, 3, 5, 6, 8, 12, 17],
        [0, 1, 2, 3, 4, 8, 9, 11],
        [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
        [0, 1, 3, 4, 5, 7, 9, 10, 12],
        [0, 1, 3, 6, 10, 13, 14],
        [0, 1, 4, 5, 9, 10, 13, 17],
        [0, 1, 2, 4, 7, 11, 16, 22, 29, 37]
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            try:
                res = sol.canCross(tests[i])
            except Exception:
                res = False
            if res:
                checksum += (len(tests[i]) + iter + i)
            else:
                checksum += i
    end = time.time()

    elapsed = int(round((end - start) * 1000000.0))

    print 'Checksum:', checksum
    print 'Elapsed time (microseconds):', elapsed