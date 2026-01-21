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
    tests = [
        {'n': 2, 'edges': [[0, 1, 5, 0]], 'k': 0},
        {'n': 3, 'edges': [[0, 1, 7, 1], [1, 2, 6, 0], [0, 2, 4, 0]], 'k': 1},
        {'n': 3, 'edges': [[0, 1, 5, 1], [1, 2, 4, 1], [0, 2, 3, 1]], 'k': 0},
        {'n': 4, 'edges': [[0, 1, 10, 1], [2, 3, 9, 0]], 'k': 0},
        {'n': 3, 'edges': [[0, 1, 3, 0], [1, 2, 2, 0]], 'k': 5},
        {'n': 4, 'edges': [[0, 1, 10, 0], [1, 2, 9, 0], [2, 3, 8, 0], [0, 2, 7, 0]], 'k': 0},
        {'n': 4, 'edges': [[0, 1, 50, 1], [1, 2, 40, 0], [2, 3, 20, 0]], 'k': 1},
        {'n': 3, 'edges': [[0, 1, 0, 1], [1, 2, 0, 0]], 'k': 0},
        {'n': 5, 'edges': [[0, 1, 1, 0], [1, 2, 1, 0], [2, 3, 1, 0], [3, 4, 1, 0]], 'k': 10},
        {'n': 6, 'edges': [[0, 1, 9, 1], [2, 3, 8, 1], [1, 2, 7, 0], [3, 4, 6, 0], [4, 5, 5, 0], [0, 2, 4, 0], [5, 0, 3, 0]], 'k': 2}
    ]

    sol = Solution()
    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for tc in tests:
            edgesCopy = [edge[:] for edge in tc['edges']]
            res = sol.maxStability(tc['n'], edgesCopy, tc['k'])
        #     checksum += res
        # sink = checksum