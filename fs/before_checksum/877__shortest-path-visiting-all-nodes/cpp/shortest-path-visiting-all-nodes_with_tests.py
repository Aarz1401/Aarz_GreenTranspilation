# Time:  O(n * 2^n)
# Space: O(n * 2^n)

import collections


class Solution(object):
    def shortestPathLength(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        dp = [[float("inf")]*(len(graph))
              for _ in xrange(1 << len(graph))]
        q = collections.deque()
        for i in xrange(len(graph)):
            dp[1 << i][i] = 0
            q.append((1 << i, i))
        while q:
            state, node = q.popleft()
            steps = dp[state][node]
            for nei in graph[node]:
                new_state = state | (1 << nei)
                if dp[new_state][nei] == float("inf"):
                    dp[new_state][nei] = steps+1
                    q.append((new_state, nei))
        return min(dp[-1])


if __name__ == "__main__":
    import time

    tests = [
        [],  # 0: empty graph
        [[]],  # 1: single node
        [[1], [0]],  # 2: two nodes connected
        [[1], [0, 2], [1]],  # 3: line of 3
        [[1, 2], [0, 2], [0, 1]],  # 4: triangle
        [[1, 3], [0, 2], [1, 3], [0, 2]],  # 5: 4-cycle
        [[1, 2, 3, 4], [0], [0], [0], [0]],  # 6: star with 5 nodes, center 0
        [[1], [0, 2], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6]],  # 7: line of 8
        [  # 8: complete graph K6
            [1, 2, 3, 4, 5],
            [0, 2, 3, 4, 5],
            [0, 1, 3, 4, 5],
            [0, 1, 2, 4, 5],
            [0, 1, 2, 3, 5],
            [0, 1, 2, 3, 4]
        ],
        [  # 9: 12-node connected mixed graph
            [1, 5],
            [0, 2, 6],
            [1, 3, 7],
            [2, 4, 8],
            [3, 5, 9],
            [4, 0, 10],
            [1, 7, 11],
            [2, 6, 8, 9],
            [3, 7, 9, 10],
            [4, 7, 8, 10, 11],
            [5, 8, 9, 11],
            [6, 9, 10]
        ]
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for _ in xrange(iterations):
        for g in tests:
            if not g:
                res = 0
            else:
                res = sol.shortestPathLength(g)
            checksum += res
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us