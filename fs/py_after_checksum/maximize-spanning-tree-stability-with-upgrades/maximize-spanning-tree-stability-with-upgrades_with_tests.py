# Time:  O(n + eloge)
# Space: O(n)

# union find, kruskal's algorithm, mst, maximum spanning tree, greedy
class UnionFind(object):  # Time: O(n * alpha(n)), Space: O(n)
    def __init__(self, n):
        self.set = range(n)
        self.rank = [0]*n

    def find_set(self, x):
        stk = []
        while self.set[x] != x:  # path compression
            stk.append(x)
            x = self.set[x]
        while stk:
            self.set[stk.pop()] = x
        return x

    def union_set(self, x, y):
        x, y = self.find_set(x), self.find_set(y)
        if x == y:
            return False
        if self.rank[x] > self.rank[y]:  # union by rank
            x, y = y, x
        self.set[x] = self.set[y]
        if self.rank[x] == self.rank[y]:
            self.rank[y] += 1
        return True


class Solution(object):
    def maxStability(self, n, edges, k):
        """
        :type n: int
        :type edges: List[List[int]]
        :type k: int
        :rtype: int
        """
        uf = UnionFind(n)
        cnt = 0
        result = float("inf")
        for u, v, s, m in edges:
            if not m:
                continue
            if not uf.union_set(u, v):
                return -1
            cnt += 1
            result = min(result, s)
        edges.sort(key=lambda x: -x[2])
        for u, v, s, m in edges:
            if m:
                continue
            if not uf.union_set(u, v):
                continue
            cnt += 1
            if cnt == (n-1)-k:
                result = min(result, s)
            elif cnt == n-1:
                result = min(result, 2*s)
        return result if cnt == n-1 else -1


if __name__ == "__main__":
    import time

    tests = []

    # Test 1: All mandatory edges forming a spanning tree
    tests.append({
        'n': 4,
        'edges': [
            [0, 1, 10, 1],
            [1, 2, 8, 1],
            [2, 3, 12, 1],
            [0, 2, 20, 0],
            [1, 3, 15, 0]
        ],
        'k': 1
    })

    # Test 2: Mandatory edges form a cycle -> -1
    tests.append({
        'n': 3,
        'edges': [
            [0, 1, 5, 1],
            [1, 2, 6, 1],
            [2, 0, 7, 1]
        ],
        'k': 0
    })

    # Test 3: Mix of mandatory and optional, hitting both thresholds
    tests.append({
        'n': 5,
        'edges': [
            [0, 1, 9, 1],
            [2, 3, 7, 1],
            [1, 2, 10, 0],
            [3, 4, 6, 0],
            [0, 4, 11, 0]
        ],
        'k': 1
    })

    # Test 4: No mandatory edges, connected graph, k = 0
    tests.append({
        'n': 5,
        'edges': [
            [0, 1, 4, 0],
            [1, 2, 9, 0],
            [2, 3, 3, 0],
            [3, 4, 8, 0],
            [0, 4, 5, 0],
            [1, 3, 7, 0],
            [0, 2, 6, 0]
        ],
        'k': 0
    })

    # Test 5: Disconnected graph even with optional edges -> -1
    tests.append({
        'n': 4,
        'edges': [
            [0, 1, 5, 0],
            [1, 2, 4, 0]
        ],
        'k': 2
    })

    # Test 6: Larger graph with mix of edges and k = 2
    tests.append({
        'n': 8,
        'edges': [
            [0, 1, 50, 1],
            [1, 2, 40, 1],
            [2, 3, 60, 1],
            [3, 4, 35, 0],
            [4, 5, 30, 0],
            [5, 6, 25, 0],
            [6, 7, 20, 0],
            [0, 2, 45, 0],
            [4, 7, 15, 0],
            [1, 3, 55, 0]
        ],
        'k': 2
    })

    # Test 7: Redundant optionals and bridging edges, k = 2
    tests.append({
        'n': 6,
        'edges': [
            [0, 1, 10, 1],
            [2, 3, 9, 1],
            [0, 2, 8, 0],
            [0, 1, 7, 0],
            [2, 3, 6, 0],
            [3, 4, 5, 0],
            [4, 5, 4, 0]
        ],
        'k': 2
    })

    # Test 8: k >= n - 1, triggers only the 2*s branch at completion
    tests.append({
        'n': 5,
        'edges': [
            [0, 1, 100, 0],
            [1, 2, 90, 0],
            [2, 3, 80, 0],
            [3, 4, 70, 0]
        ],
        'k': 4
    })

    # Test 9: All optional edges with same strength
    tests.append({
        'n': 4,
        'edges': [
            [0, 1, 5, 0],
            [1, 2, 5, 0],
            [2, 3, 5, 0],
            [0, 2, 5, 0],
            [1, 3, 5, 0]
        ],
        'k': 1
    })

    # Test 10: Large strengths around 1e9, safe within int range after operations
    tests.append({
        'n': 6,
        'edges': [
            [0, 1, 1000000000, 1],
            [2, 3, 1000000000, 1],
            [1, 2, 1000000000, 0],
            [3, 4, 1000000000, 0],
            [4, 5, 1000000000, 0]
        ],
        'k': 0
    })

    sol = Solution()

    start = time.time()
    checksum = 0

    iterations = 1
    for _ in xrange(iterations):
        for tc in tests:
            edgesCopy = [e[:] for e in tc['edges']]
            res = sol.maxStability(tc['n'], edgesCopy, tc['k'])
            checksum += res

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (us): %d" % elapsed_us