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
    import time

    tests = []

    tc = {}
    tc['N'] = 1
    tc['edges'] = []
    tests.append(tc)

    tc = {}
    tc['N'] = 2
    tc['edges'] = [[0, 1]]
    tests.append(tc)

    tc = {}
    tc['N'] = 10
    tc['edges'] = []
    for i in xrange(tc['N'] - 1):
        tc['edges'].append([i, i + 1])
    tests.append(tc)

    tc = {}
    tc['N'] = 10
    tc['edges'] = []
    for i in xrange(1, tc['N']):
        tc['edges'].append([0, i])
    tests.append(tc)

    tc = {}
    tc['N'] = 15
    tc['edges'] = []
    for i in xrange(tc['N']):
        if 2 * i + 1 >= tc['N']:
            break
        tc['edges'].append([i, 2 * i + 1])
        if 2 * i + 2 < tc['N']:
            tc['edges'].append([i, 2 * i + 2])
    tests.append(tc)

    tc = {}
    tc['N'] = 20
    tc['edges'] = []
    for i in xrange(1, tc['N']):
        p = (i * 7 + 3) % i
        tc['edges'].append([p, i])
    tests.append(tc)

    tc = {}
    tc['N'] = 12
    tc['edges'] = []
    for i in xrange(1, 6 + 1 - 1):  # i = 1..5
        tc['edges'].append([0, i])
    for i in xrange(7, 11 + 1):
        tc['edges'].append([6, i])
    tc['edges'].append([0, 6])
    tests.append(tc)

    tc = {}
    tc['N'] = 15
    tc['edges'] = []
    for i in xrange(1, 5 + 1):
        tc['edges'].append([0, i])
    tc['edges'].append([1, 6])
    tc['edges'].append([2, 7]); tc['edges'].append([7, 8])
    tc['edges'].append([3, 9]); tc['edges'].append([9, 10]); tc['edges'].append([10, 11])
    tc['edges'].append([4, 12])
    tc['edges'].append([5, 13]); tc['edges'].append([13, 14])
    tests.append(tc)

    tc = {}
    tc['N'] = 25
    tc['edges'] = []
    for i in xrange(19):
        tc['edges'].append([i, i + 1])
    tc['edges'].append([10, 20])
    tc['edges'].append([10, 21])
    tc['edges'].append([15, 22])
    tc['edges'].append([18, 23])
    tc['edges'].append([18, 24])
    tests.append(tc)

    tc = {}
    tc['N'] = 100
    tc['edges'] = []
    for i in xrange(1, tc['N']):
        p = (i * i + 31) % i
        tc['edges'].append([p, i])
    tests.append(tc)

    checksum = 0
    start = time.time()
    iterations = 1000
    for iter_idx in xrange(iterations):
        sol = Solution()
        for tc in tests:
            edges = [list(e) for e in tc['edges']]
            result = sol.sumOfDistancesInTree(tc['N'], edges)
            local = 0
            for v in result:
                local += v
            checksum += local + iter_idx
    end = time.time()

    elapsed_ms = (end - start) * 1000.0
    print 'Checksum: %d' % int(checksum)
    print 'Elapsed time (ms): %f' % elapsed_ms