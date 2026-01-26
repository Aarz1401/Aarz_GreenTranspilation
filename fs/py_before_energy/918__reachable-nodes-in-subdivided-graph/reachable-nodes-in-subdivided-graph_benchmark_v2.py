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
    tests = [
        ([[0,1,10], [0,2,1], [1,2,2]], 6, 3),
        ([[0,1,4], [1,2,3], [2,3,2], [3,4,1]], 0, 5),
        ([[0,1,2], [1,2,2], [2,3,2], [3,4,2], [4,5,2]], 5, 6),
        ([[0,1,3], [0,2,4], [0,3,5], [0,4,1], [0,5,2]], 7, 6),
        ([[0,1,1000000000], [1,2,1000000000], [0,2,1000000000]], 1000000000, 3),
        ([[0,1,1], [2,3,5], [3,4,5], [5,6,5]], 2, 7),
        ([[0,1,1], [1,2,1], [2,3,1], [3,4,1], [4,0,1]], 3, 5),
        ([[0,1,2], [0,2,3], [0,3,4], [1,2,5], [1,3,6], [2,3,7]], 8, 4),
        ([[0,1,1], [1,2,4], [2,3,6], [3,4,8], [4,5,10], [5,6,12], [6,7,14], [0,7,20], [2,6,7]], 15, 8),
        ([[0,1,3], [1,2,3], [2,3,3], [3,4,3], [0,4,10]], 9, 5),
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for edges, M, N in tests:
            r = sol.reachableNodes(edges, M, N)
        #sink = checksum

    # print sink