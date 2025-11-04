# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(m * n)
# Space: O(m * n)

# array, hash table
class Solution(object):
    def canPartitionGrid(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        def check(range1, range2, get):
            curr = 0
            lookup = set()
            begin = -1
            for i in range1:
                if begin == -1:
                    begin = i
                for j in range2:
                    curr += get(i, j)
                    lookup.add(get(i, j))
                diff = curr-(total-curr)
                if diff == 0:
                    return True
                if i != begin and j != 0:
                    if diff in lookup:
                        return True
                elif i == begin:
                    if diff in [get(begin, 0), get(begin, j)]:
                        return True
                else:
                    if diff in [get(begin, 0), (get(i, 0))]:
                        return True
            return False
    
        total = sum(sum(row) for row in grid)
        return check(xrange(len(grid)), xrange(len(grid[0])), lambda i, j: grid[i][j]) or \
               check(reversed(xrange(len(grid))), xrange(len(grid[0])), lambda i, j: grid[i][j]) or \
               check(xrange(len(grid[0])), xrange(len(grid)), lambda i, j: grid[j][i]) or \
               check(reversed(xrange(len(grid[0]))), xrange(len(grid)), lambda i, j: grid[j][i])

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Single element
        [[0]],

        # 2) Single row
        [[1, 2, 3]],

        # 3) Single column
        [[1], [2], [4]],

        # 4) Uniform small matrix (balanced)
        [[1, 1], [1, 1]],

        # 5) Mixed negatives, positives, and zeros
        [[-1, 2, 0], [3, -2, 1], [0, 0, 0]],

        # 6) 4x3 mixed values
        [[5, 7, 2], [4, 9, 1], [6, 3, 8], [0, -2, 4]],

        # 7) Large numbers to test 64-bit accumulation
        [
            [1000000000, 1000000000, 1000000000, 999999999, 999999999],
            [1000000000, 999999999, 1000000000, 1000000000, 999999999]
        ],

        # 8) 4x4 chessboard pattern
        [
            [1, 0, 1, 0],
            [0, 1, 0, 1],
            [1, 0, 1, 0],
            [0, 1, 0, 1]
        ],

        # 9) 3x4 prime numbers
        [
            [2, 3, 5, 7],
            [11, 13, 17, 19],
            [23, 29, 31, 37]
        ],

        # 10) 2x3 symmetric rows
        [
            [1, 2, 3],
            [3, 2, 1]
        ],
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.canPartitionGrid(*test)
        else:
            sol.canPartitionGrid(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.canPartitionGrid(*test)
            else:
                result = sol.canPartitionGrid(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()