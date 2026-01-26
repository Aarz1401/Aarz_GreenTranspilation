# Time:  O(nlog*n) ~= O(n), n is the length of the positions
# Space: O(n)

class UnionFind(object):
    def __init__(self, n):
        self.set = range(n)

    def find_set(self, x):
        if self.set[x] != x:
            self.set[x] = self.find_set(self.set[x])  # path compression.
        return self.set[x]

    def union_set(self, x, y):
        x_root, y_root = map(self.find_set, (x, y))
        if x_root == y_root:
            return False
        self.set[min(x_root, y_root)] = max(x_root, y_root)
        return True


class Solution(object):
    def findRedundantDirectedConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        cand1, cand2 = [], []
        parent = {}
        for edge in edges:
            if edge[1] not in parent:
                parent[edge[1]] = edge[0]
            else:
                cand1 = [parent[edge[1]], edge[1]]
                cand2 = edge

        union_find = UnionFind(len(edges)+1)
        for edge in edges:
            if edge == cand2:
                continue
            if not union_find.union_set(*edge):
                return cand1 if cand2 else edge
        return cand2


if __name__ == "__main__":
    tests = [
        [[1,2],[1,3],[2,3]],                               # two-parent, no cycle
        [[1,2],[2,3],[3,4],[4,1],[1,5]],                   # cycle, no two-parent
        [[2,1],[3,1],[4,2],[1,4]],                         # both: cycle + two-parent
        [[1,2],[1,3],[2,4],[3,4],[4,5]],                   # two-parent, no cycle
        [[1,2],[1,3],[2,4],[3,5],[5,6],[6,1]],             # cycle, no two-parent
        [[1,2],[2,1]],                                     # small cycle
        [[1,2],[1,3],[2,4],[2,5],[3,5],[3,6],[6,7]],       # two-parent, no cycle
        [[4,2],[1,2],[2,3],[3,4],[2,5]],                   # both: cycle + two-parent
        [[1,2],[1,3],[2,4],[3,5],[4,6],[6,1]],             # cycle, no two-parent
        [[1,2],[2,3],[3,4],[1,3]]                          # two-parent, no cycle
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for t in tests:
            r = sol.findRedundantDirectedConnection(t)
            #checksum += r[0] * 131 + r[1]
        #sink = checksum

    # print sink