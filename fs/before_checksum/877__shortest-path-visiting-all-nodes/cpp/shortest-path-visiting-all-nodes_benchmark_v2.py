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
    tests = [
        [ [] ],                                         # n=1
        [ [1], [0] ],                                   # n=2
        [ [1], [0,2], [1] ],                            # n=3 path
        [ [1,3], [0,2], [1,3], [0,2] ],                 # n=4 cycle
        [ [1,2,3,4], [0], [0], [0], [0] ],              # n=5 star
        [ [1,2,3,4,5], [0,2,3,4,5], [0,1,3,4,5],        # n=6 complete
          [0,1,2,4,5], [0,1,2,3,5], [0,1,2,3,4] ],
        [ [1,2], [0,2,4], [0,1,3,6], [2,4],             # n=7 mixed
          [1,3,5], [4,6], [5,2] ],
        [ [1,4], [0,2,5], [1,3,6], [2,7],               # n=8 grid 2x4
          [0,5], [1,4,6], [2,5,7], [3,6] ],
        [ [1,3], [0,2,4], [1,5],                        # n=9 grid 3x3
          [0,4,6], [1,3,5,7], [2,4,8],
          [3,7], [4,6,8], [5,7] ],
        [ [1,4], [0,2], [1,3], [2,4],                   # n=10 two 5-cycles + bridge
          [3,0,5], [6,9,4], [5,7], [6,8], [7,9], [8,5] ]
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for i in xrange(len(tests)):
            checksum += sol.shortestPathLength(tests[i])
        sink += checksum
    print(sink)
    # print sink