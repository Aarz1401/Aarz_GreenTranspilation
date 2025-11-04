# Time:  O((|E| + |V|) * log|V|) = O(|E| * log|V|),
#        if we can further to use Fibonacci heap, it would be O(|E| + |V| * log|V|)
# Space: O(|E| + |V|) = O(|E|)

import collections
import heapq

class Solution(object):
    def reachableNodes(self, edges, M, N):
        """
        :type edges: List[List[int]]
        :type M: int
        :type N: int
        :rtype: int
        """
        adj = [[] for _ in xrange(N)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        min_heap = [(0, 0)]
        best = collections.defaultdict(lambda: float("inf"))
        best[0] = 0
        count = collections.defaultdict(lambda: collections.defaultdict(int))
        result = 0
        while min_heap:
            curr_total, u = heapq.heappop(min_heap)  # O(|V|*log|V|) in total
            if best[u] < curr_total:
                continue
            result += 1
            for v, w in adj[u]:
                count[u][v] = min(w, M-curr_total)
                next_total = curr_total+w+1
                if next_total <= M and next_total < best[v]:
                    best[v] = next_total
                    heapq.heappush(min_heap, (next_total, v))  # binary heap O(|E|*log|V|) in total
                                                               # Fibonacci heap O(|E|) in total
        for u, v, w in edges:
            result += min(w, count[u][v]+count[v][u])
        return result


if __name__ == "__main__":
    import time

    # Define 10 diverse test cases
    tests = []

    # 1) Simple single edge, limited M
    edges1 = [[0, 1, 10]]
    tests.append((edges1, 6, 2))

    # 2) Triangle graph with varying weights
    edges2 = [[0, 1, 4], [1, 2, 6], [0, 2, 8]]
    tests.append((edges2, 10, 3))

    # 3) Linear chain
    edges3 = []
    for i in range(4):
        edges3.append([i, i + 1, 1])
    tests.append((edges3, 3, 5))

    # 4) Star graph centered at 0
    edges4 = [
        [0, 1, 2], [0, 2, 3], [0, 3, 1], [0, 4, 5], [0, 5, 7], [0, 6, 0]
    ]
    tests.append((edges4, 5, 7))

    # 5) Zero moves, only node 0 reachable
    edges5 = [[0, 1, 3], [1, 2, 3]]
    tests.append((edges5, 0, 3))

    # 6) Dense graph with 10 nodes
    edges6 = []
    N6 = 10
    for i in range(N6):
        for j in range(i + 1, N6):
            w = ((i * 7 + j * 11) % 5) + 1  # weights in [1,5]
            edges6.append([i, j, w])
    tests.append((edges6, 20, N6))

    # 7) Disjoint components
    edges7 = [
        [0, 1, 2], [1, 2, 2],
        [4, 5, 1], [5, 6, 1], [6, 7, 1]
    ]
    tests.append((edges7, 3, 8))

    # 8) Very large weights and M to test 64-bit handling
    edges8 = [
        [0, 1, 1000000000], [1, 2, 1000000000]
    ]
    tests.append((edges8, 1000000000, 3))

    # 9) Single node, no edges
    edges9 = []
    tests.append((edges9, 10, 1))

    # 10) Cycle with zero-weight edges
    edges10 = [
        [0, 1, 0], [1, 2, 0], [2, 3, 0], [3, 0, 0], [0, 2, 0]
    ]
    tests.append((edges10, 2, 4))

    checksum = 0

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        sol = Solution()
        for t in tests:
            edges, M, N = t
            edges_local = [e[:] for e in edges]
            res = sol.reachableNodes(edges_local, M, N)
            checksum += res
    end = time.time()

    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (ns): %d" % (elapsed_ns,)