# Time:  O(n^2 * n!)
# Space: O(n)

class Solution(object):
    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def dfs(row):
            if row == n:
                result.append(map(lambda x: '.'*x + "Q" + '.'*(n-x-1), curr))
                return
            for i in xrange(n):
                if cols[i] or main_diag[row+i] or anti_diag[row-i+(n-1)]:
                    continue
                cols[i] = main_diag[row+i] = anti_diag[row-i+(n-1)] = True
                curr.append(i)
                dfs(row+1)
                curr.pop()
                cols[i] = main_diag[row+i] = anti_diag[row-i+(n-1)] = False

        result, curr = [], []
        cols, main_diag, anti_diag = [False]*n, [False]*(2*n-1), [False]*(2*n-1)
        dfs(0)
        return result


# For any point (x,y), if we want the new point (p,q) don't share the same row, column, or diagonal.
# then there must have ```p+q != x+y``` and ```p-q!= x-y```
# the former focus on eliminate 'left bottom right top' diagonal
# the latter focus on eliminate 'left top right bottom' diagonal

# - col_per_row: the list of column index per row
# - cur_row：current row we are seraching for valid column
# - xy_diff：the list of x-y
# - xy_sum：the list of x+y
class Solution2(object):
    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def dfs(col_per_row, xy_diff, xy_sum):
            cur_row = len(col_per_row)
            if cur_row == n:
                ress.append(col_per_row)
            for col in range(n):
                if col not in col_per_row and cur_row-col not in xy_diff and cur_row+col not in xy_sum:
                    dfs(col_per_row+[col], xy_diff+[cur_row-col], xy_sum+[cur_row+col])
        ress = []
        dfs([], [], [])
        return [['.'*i + 'Q' + '.'*(n-i-1) for i in res] for res in ress]


if __name__ == "__main__":
    import time

    test_inputs = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    solver = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for n in test_inputs:
            res = solver.solveNQueens(n)
            checksum += len(res)
            for board in res:
                for row in board:
                    pos = row.find('Q')
                    if pos != -1:
                        checksum += (pos + 1)

    end = time.time()
    elapsed = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed