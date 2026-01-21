# Time:  O(n)
# Space: O(n)

import collections


class Solution(object):
    def sumOfDistancesInTree(self, N, edges):
        """
        :type N: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        def dfs(graph, node, parent, count, result):
            for nei in graph[node]:
                if nei != parent:
                    dfs(graph, nei, node, count, result)
                    count[node] += count[nei]
                    result[node] += result[nei]+count[nei]

        def dfs2(graph, node, parent, count, result):
            for nei in graph[node]:
                if nei != parent:
                    result[nei] = result[node]-count[nei] + \
                                  len(count)-count[nei]
                    dfs2(graph, nei, node, count, result)

        graph = collections.defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        count = [1] * N
        result = [0] * N

        dfs(graph, 0, None, count, result)
        dfs2(graph, 0, None, count, result)
        return result


if __name__ == "__main__":
    tests = [
        (2, [[0, 1]]),
        (3, [[0, 1], [1, 2]]),
        (4, [[0, 1], [0, 2], [0, 3]]),
        (5, [[0, 1], [1, 2], [2, 3], [3, 4]]),
        (6, [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5]]),
        (7, [[3, 0], [3, 1], [3, 2], [3, 4], [3, 5], [3, 6]]),
        (8, [[0, 1], [1, 2], [1, 3], [2, 4], [2, 5], [3, 6], [6, 7]]),
        (9, [[0, 1], [0, 2], [2, 3], [2, 4], [4, 5], [5, 6], [6, 7], [6, 8]]),
        (10, [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6], [3, 7], [5, 8], [5, 9]]),
        (12, [[0, 1], [0, 2], [0, 3], [1, 4], [1, 5], [2, 6], [2, 7], [3, 8], [8, 9], [9, 10], [10, 11]])
    ]

    sink = 0
    sol = Solution()

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for N, edges in tests:
            res = sol.sumOfDistancesInTree(N, edges)
            for v in res:
                checksum += v
        sink += checksum
    print(sink)