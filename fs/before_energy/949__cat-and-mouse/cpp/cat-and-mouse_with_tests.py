# Time:  O(n^3)
# Space: O(n^2)

import collections


class Solution(object):
    def catMouseGame(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        HOLE, MOUSE_START, CAT_START = range(3)
        DRAW, MOUSE, CAT = range(3)
        def parents(m, c, t):
            if t == CAT:
                for nm in graph[m]:
                    yield nm, c, MOUSE^CAT^t
            else:
                for nc in graph[c]:
                    if nc != HOLE:
                        yield m, nc, MOUSE^CAT^t

        degree = {}
        ignore = set(graph[HOLE])
        for m in xrange(len(graph)):
            for c in xrange(len(graph)):
                degree[m, c, MOUSE] = len(graph[m])
                degree[m, c, CAT] = len(graph[c])-(c in ignore)
        color = collections.defaultdict(int)
        q = collections.deque()
        for i in xrange(len(graph)):
            if i == HOLE:
                continue
            color[HOLE, i, CAT] = MOUSE
            q.append((HOLE, i, CAT, MOUSE))
            for t in [MOUSE, CAT]:
                color[i, i, t] = CAT
                q.append((i, i, t, CAT))
        while q:
            i, j, t, c = q.popleft()
            for ni, nj, nt in parents(i, j, t):
                if color[ni, nj, nt] != DRAW:
                    continue
                if nt == c:
                    color[ni, nj, nt] = c
                    q.append((ni, nj, nt, c))
                    continue
                degree[ni, nj, nt] -= 1
                if not degree[ni, nj, nt]:
                    color[ni, nj, nt] = c
                    q.append((ni, nj, nt, c))
        return color[MOUSE_START, CAT_START, MOUSE]

    
# Time:  O(n^3)
# Space: O(n^2)
import collections


class Solution2(object):
    def catMouseGame(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        HOLE, MOUSE_START, CAT_START = range(3)
        DRAW, MOUSE, CAT = range(3)
        def parents(m, c, t):
            if t == CAT:
                for nm in graph[m]:
                    yield nm, c, MOUSE^CAT^t
            else:
                for nc in graph[c]:
                    if nc != HOLE:
                        yield m, nc, MOUSE^CAT^t

        color = collections.defaultdict(int)
        degree = {}
        ignore = set(graph[HOLE])
        for m in xrange(len(graph)):
            for c in xrange(len(graph)):
                degree[m, c, MOUSE] = len(graph[m])
                degree[m, c, CAT] = len(graph[c])-(c in ignore)
        q1 = collections.deque()
        q2 = collections.deque()
        for i in xrange(len(graph)):
            if i == HOLE:
                continue
            color[HOLE, i, CAT] = MOUSE
            q1.append((HOLE, i, CAT))
            for t in [MOUSE, CAT]:
                color[i, i, t] = CAT
                q2.append((i, i, t))
        while q1:
            i, j, t = q1.popleft()
            for ni, nj, nt in parents(i, j, t):
                if color[ni, nj, nt] != DRAW:
                    continue
                if t == CAT:
                    color[ni, nj, nt] = MOUSE
                    q1.append((ni, nj, nt))
                    continue
                degree[ni, nj, nt] -= 1
                if not degree[ni, nj, nt]:
                    color[ni, nj, nt] = MOUSE
                    q1.append((ni, nj, nt))
        while q2:
            i, j, t = q2.popleft()
            for ni, nj, nt in parents(i, j, t):
                if color[ni, nj, nt] != DRAW:
                    continue
                if t == MOUSE:
                    color[ni, nj, nt] = CAT
                    q2.append((ni, nj, nt))
                    continue
                degree[ni, nj, nt] -= 1
                if not degree[ni, nj, nt]:
                    color[ni, nj, nt] = CAT
                    q2.append((ni, nj, nt))
        return color[MOUSE_START, CAT_START, MOUSE]


if __name__ == "__main__":
    import time

    # 10 diverse test graphs
    tests = [
        # G1: triangle
        [[1, 2], [0, 2], [0, 1]],
        # G2: chain of 4
        [[1], [0, 2], [1, 3], [2]],
        # G3: star centered at 0 (hole)
        [[1, 2, 3, 4], [0], [0], [0], [0]],
        # G4: complete graph of 5
        [[1, 2, 3, 4], [0, 2, 3, 4], [0, 1, 3, 4], [0, 1, 2, 4], [0, 1, 2, 3]],
        # G5: LeetCode-like example (often a draw)
        [[2, 5], [3], [0, 4, 5], [1, 4, 5], [2, 3], [0, 2, 3]],
        # G6: ring of 6
        [[1, 5], [0, 2], [1, 3], [2, 4], [3, 5], [4, 0]],
        # G7: two components, one isolated node
        [[1], [0], [3], [2], []],
        # G8: chain of 3
        [[1], [0, 2], [1]],
        # G9: small star - cat adjacent only to hole
        [[1, 2], [0], [0]],
        # G10: dense irregular graph of 7
        [[1, 2, 3], [0, 4, 5], [0, 4, 6], [0, 5, 6], [1, 2, 5, 6], [1, 3, 4, 6], [2, 3, 4, 5]],
    ]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for g in tests:
            checksum += sol.catMouseGame(g)

    elapsed_ms = (time.time() - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %f" % elapsed_ms