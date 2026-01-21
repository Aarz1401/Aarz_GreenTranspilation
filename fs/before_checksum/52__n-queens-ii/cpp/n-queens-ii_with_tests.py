# Time:  O(n!)
# Space: O(n)

class Solution(object):
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        def dfs(row):
            if row == n:
                return 1
            result = 0
            for i in xrange(n):
                if cols[i] or main_diag[row+i] or anti_diag[row-i+(n-1)]:
                    continue
                cols[i] = main_diag[row+i] = anti_diag[row-i+(n-1)] = True
                result += dfs(row+1)
                cols[i] = main_diag[row+i] = anti_diag[row-i+(n-1)] = False
            return result

        result = []
        cols, main_diag, anti_diag = [False]*n, [False]*(2*n-1), [False]*(2*n-1)
        return dfs(0)


if __name__ == "__main__":
    import time

    sol = Solution()

    tests = [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8]

    checksum = 0

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for n in tests:
            checksum += sol.totalNQueens(n)

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (us): %d" % (elapsed_us,)