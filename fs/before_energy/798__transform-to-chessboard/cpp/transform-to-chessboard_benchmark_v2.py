
# Time:  O(n^2)
# Space: O(n^2), used by Counter, this could be reduced to O(n) by skipping invalid input

import collections
import itertools


class Solution(object):
    def movesToChessboard(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        N = len(board)
        result = 0
        for count in (collections.Counter(map(tuple, board)), \
                      collections.Counter(itertools.izip(*board))):
            if len(count) != 2 or \
               sorted(count.values()) != [N/2, (N+1)/2]:
                return -1

            seq1, seq2 = count
            if any(x == y for x, y in itertools.izip(seq1, seq2)):
                return -1
            begins = [int(seq1.count(1) * 2 > N)] if N%2 else [0, 1]
            result += min(sum(int(i%2 != v) for i, v in enumerate(seq1, begin)) \
                          for begin in begins) / 2
        return result


if __name__ == "__main__":
    def makeChess(N, start):
        b = [[0 for _ in range(N)] for _ in range(N)]
        for i in range(N):
            for j in range(N):
                b[i][j] = (i + j + start) % 2
        return b

    def permuteCols(b, p):
        N = len(b)
        r = [[0 for _ in range(N)] for _ in range(N)]
        for i in range(N):
            for j in range(N):
                r[i][j] = b[i][p[j]]
        return r

    def permuteRows(b, p):
        N = len(b)
        r = [[0 for _ in range(N)] for _ in range(N)]
        for i in range(N):
            r[i] = b[p[i]][:]
        return r

    tests = []

    # 1) 2x2 valid chessboard
    tests.append([[0,1],[1,0]])

    # 2) 2x2 invalid due to column counts mismatch
    tests.append([[1,1],[0,0]])

    # 3) 3x3 valid chessboard
    tests.append(makeChess(3, 0))

    # 4) 3x3 invalid row not matching s1/s2
    tests.append([[1,0,1],[0,1,0],[1,1,0]])

    # 5) 4x4 solvable needing swaps
    tests.append([[0,0,1,1],[1,1,0,0],[0,0,1,1],[1,1,0,0]])

    # 6) 5x5 valid chessboard starting with 1
    tests.append(makeChess(5, 1))

    # 7) 5x5 invalid due to row count imbalance
    tests.append([[1,0,1,0,1],[1,0,1,0,1],[1,0,1,0,1],[1,0,1,0,1],[1,0,1,0,1]])

    # 8) 6x6 solvable after permutations
    b = makeChess(6, 0)
    pc = [2,0,3,5,1,4]
    pr = [3,0,5,2,1,4]
    tests.append(permuteRows(permuteCols(b, pc), pr))

    # 9) 7x7 solvable after permutations
    b = makeChess(7, 0)
    pc = [1,0,3,2,5,4,6]
    pr = [6,0,2,1,3,5,4]
    tests.append(permuteRows(permuteCols(b, pc), pr))

    # 10) 8x8 solvable after permutations
    b = makeChess(8, 1)
    pc = [7,0,5,2,3,1,6,4]
    pr = [4,2,7,0,6,1,5,3]
    tests.append(permuteRows(permuteCols(b, pc), pr))

    sol = Solution()
    sink = 0
    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for i in range(10):
            r = sol.movesToChessboard(tests[i])
        #sink = checksum
    #print(sink)
