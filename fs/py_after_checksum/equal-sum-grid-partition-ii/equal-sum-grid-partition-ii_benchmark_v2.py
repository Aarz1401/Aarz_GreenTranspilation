
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

if __name__ == '__main__':
    tests = [
        [[0]],
        [[5]],
        [[1, 2]],
        [[1], [2]],
        [[1, 2], [3, 4]],
        [[1, 1, 1], [1, 1, 1]],
        [[3, 1, 2], [4, 0, 5], [6, 7, 8]],
        [[10, 20, 30, 40]],
        [[2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2]],
        [[9, 8, 7, 6], [5, 4, 3, 2], [1, 0, 1, 0]]
    ]

    s = Solution()
    sink = 0

    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for grid in tests:
            checksum += s.canPartitionGrid(grid)
        sink += checksum
    print(sink)

    # print sink
