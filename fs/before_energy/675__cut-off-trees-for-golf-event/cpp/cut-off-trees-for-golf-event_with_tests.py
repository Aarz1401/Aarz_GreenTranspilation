
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
    from time import time

    # 10 diverse test inputs
    f1 = []  # empty -> -1
    f2 = [[]]  # n == 0 -> -1
    f3 = [[0]]  # start blocked -> -1
    f4 = [[1,1], [1,1]]  # no trees -> 0
    f5 = [[1,2]]  # single tree -> reachable
    f6 = [
        [1,2,3],
        [0,0,4],
        [7,6,5]
    ]  # reachable classic
    f7 = [
        [1,2,3],
        [0,0,0],
        [4,5,6]
    ]  # unreachable later -> -1
    f8 = [
        [1,0,2,0,3],
        [0,4,0,5,0],
        [6,0,7,0,8],
        [0,9,0,10,0],
        [11,0,12,0,13]
    ]  # unreachable early -> -1
    f9 = [
        [1,1,1,1,1,1],
        [1,0,0,0,0,1],
        [1,1,2,3,0,1],
        [1,1,4,5,0,1],
        [1,1,6,7,0,1],
        [1,1,1,1,1,1]
    ]  # reachable with corridor
    f10 = [
        [1,2,3,4,5,6,7],
        [0,0,0,0,0,0,8],
        [15,14,13,12,11,10,9],
        [16,0,0,0,0,0,0],
        [17,18,19,20,21,22,23]
    ]  # zigzag path reachable

    def safe_run(sol, f):
        try:
            if not f or not f[0]:
                return -1
            if f[0][0] == 0:
                return -1
            return sol.cutOffTree(f)
        except Exception:
            return -1

    checksum = 0

    iterations = 1000
    begin = time()
    for iter in xrange(iterations):
        sol = Solution()
        checksum += safe_run(sol, f1)
        checksum += safe_run(sol, f2)
        checksum += safe_run(sol, f3)
        checksum += safe_run(sol, f4)
        checksum += safe_run(sol, f5)
        checksum += safe_run(sol, f6)
        checksum += safe_run(sol, f7)
        checksum += safe_run(sol, f8)
        checksum += safe_run(sol, f9)
        checksum += safe_run(sol, f10)
        # minor dependency on iter to avoid over-aggressive optimization
        checksum += iter & 1
    end = time()

    elapsed_us = int((end - begin) * 1000000)

    print "Checksum:", checksum
    print "Elapsed time:", elapsed_us, "us"
