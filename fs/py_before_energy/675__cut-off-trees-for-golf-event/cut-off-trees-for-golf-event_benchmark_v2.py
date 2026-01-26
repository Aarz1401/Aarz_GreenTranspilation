# Time:  O(t * (logt + m * n)), t is the number of trees
# Space: O(t + m * n)

import collections
import heapq


class Solution(object):
    def cutOffTree(self, forest):
        """
        :type forest: List[List[int]]
        :rtype: int
        """
        def dot(p1, p2):
            return p1[0]*p2[0]+p1[1]*p2[1]

        def minStep(p1, p2):
            min_steps = abs(p1[0]-p2[0])+abs(p1[1]-p2[1])
            closer, detour = [p1], []
            lookup = set()
            while True:
                if not closer:  # cannot find a path in the closer expansions
                    if not detour:  # no other possible path
                        return -1
                    # try other possible paths in detour expansions with extra 2-step cost
                    min_steps += 2
                    closer, detour = detour, closer
                i, j = closer.pop()
                if (i, j) == p2:
                    return min_steps
                if (i, j) not in lookup:
                    lookup.add((i, j))
                    for I, J in (i+1, j), (i-1, j), (i, j+1), (i, j-1):
                        if 0 <= I < m and 0 <= J < n and forest[I][J] and (I, J) not in lookup:
                            is_closer = dot((I-i, J-j), (p2[0]-i, p2[1]-j)) > 0
                            (closer if is_closer else detour).append((I, J))
            return min_steps

        m, n = len(forest), len(forest[0])
        min_heap = []
        for i in xrange(m):
            for j in xrange(n):
                if forest[i][j] > 1:
                    heapq.heappush(min_heap, (forest[i][j], (i, j)))

        start = (0, 0)
        result = 0
        while min_heap:
            tree = heapq.heappop(min_heap)
            step = minStep(start, tree[1])
            if step < 0:
                return -1
            result += step
            start = tree[1]
        return result


# Time:  O(t * (logt + m * n)), t is the number of trees
# Space: O(t + m * n)
class Solution_TLE(object):
    def cutOffTree(self, forest):
        """
        :type forest: List[List[int]]
        :rtype: int
        """
        def minStep(p1, p2):
            min_steps = 0
            lookup = {p1}
            q = collections.deque([p1])
            while q:
                size = len(q)
                for _ in xrange(size):
                    (i, j) = q.popleft()
                    if (i, j) == p2:
                        return min_steps
                    for i, j in (i+1, j), (i-1, j), (i, j+1), (i, j-1):
                        if not (0 <= i < m and 0 <= j < n and forest[i][j] and (i, j) not in lookup):
                            continue
                        q.append((i, j))
                        lookup.add((i, j))
                min_steps += 1
            return -1

        m, n = len(forest), len(forest[0])
        min_heap = []
        for i in xrange(m):
            for j in xrange(n):
                if forest[i][j] > 1:
                    heapq.heappush(min_heap, (forest[i][j], (i, j)))

        start = (0, 0)
        result = 0
        while min_heap:
            tree = heapq.heappop(min_heap)
            step = minStep(start, tree[1])
            if step < 0:
                return -1
            result += step
            start = tree[1]
        return result


if __name__ == "__main__":
    tests = [
        [[1]],
        [[1, 2]],
        [[1, 0], [3, 2]],
        [[1, 2, 3], [0, 0, 0], [7, 6, 5]],
        [[1, 2, 3, 4], [0, 0, 5, 0], [8, 7, 6, 9], [0, 0, 0, 10]],
        [[1, 1, 1, 1, 1], [0, 0, 0, 0, 1], [1, 2, 3, 4, 5], [1, 0, 0, 0, 0], [6, 7, 8, 9, 10]],
        [[1, 1], [1, 1]],
        [[1, 3, 5], [2, 8, 4], [7, 6, 9]],
        [[1, 2, 3, 4, 5, 6], [0, 0, 0, 0, 0, 7], [12, 11, 10, 9, 8, 14], [13, 0, 0, 0, 0, 15], [16, 17, 18, 19, 20, 21], [0, 0, 0, 0, 0, 22]],
        [[1, 0, 2, 0, 3], [4, 5, 6, 0, 7], [0, 0, 8, 9, 10]]
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for forest in tests:
            r= sol.cutOffTree(forest)
        #sink = checksum