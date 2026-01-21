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
    import time

    def makeBoardFromRC(R, C):
        return [[ri ^ cj for cj in C] for ri in R]

    tests = []

    # 1) 1x1 valid (0 moves)
    tests.append([[0]])

    # 2) 2x2 valid chessboard (0 moves)
    tests.append(makeBoardFromRC([0,1], [0,1]))

    # 3) 2x2 valid chessboard starting with 1 (0 moves)
    tests.append(makeBoardFromRC([1,0], [1,0]))

    # 4) 2x2 invalid board (should be -1)
    tests.append([[1,1],[0,0]])

    # 5) 3x3 valid with 1 move
    tests.append(makeBoardFromRC([0,1,1], [1,0,1]))

    # 6) 3x3 invalid (row not matching pattern)
    tests.append([[0,1,0],[1,1,1],[0,1,0]])

    # 7) 4x4 valid with 2 moves
    tests.append(makeBoardFromRC([0,0,1,1], [0,0,1,1]))

    # 8) 4x4 invalid due to row counts mismatch
    tests.append(makeBoardFromRC([0,0,0,1], [0,1,0,1]))

    # 9) 5x5 valid with 2 moves
    tests.append(makeBoardFromRC([0,0,1,1,1], [1,1,0,0,1]))

    # 10) 6x6 valid with 2 moves
    tests.append(makeBoardFromRC([1,1,0,0,1,0], [0,1,1,0,0,1]))

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for board in tests:
            res = sol.movesToChessboard(board)
            checksum += res

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms