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
    sol = Solution()
    tests = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for n in tests:
            r = sol.totalNQueens(n)
        #sink = checksum