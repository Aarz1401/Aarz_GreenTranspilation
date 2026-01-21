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
    # Benchmark test cases for Python2 Solution.findRedundantDirectedConnection

    # Define 10 diverse test inputs
    tests = []

    # 1) Pure cycle
    tests.append([[1,2],[2,3],[3,1]])

    # 2) Two parents, no cycle
    tests.append([[1,2],[1,3],[2,3]])

    # 3) Two parents + cycle
    tests.append([[2,1],[3,1],[4,2],[1,4]])

    # 4) Larger cycle
    tests.append([[1,2],[2,3],[3,4],[4,5],[5,3]])

    # 5) Two parents, no cycle in union pass
    tests.append([[1,2],[2,3],[3,4],[1,4],[4,5]])

    # 6) Back edge to root creates cycle
    tests.append([[1,2],[1,3],[2,4],[3,5],[5,1]])

    # 7) Larger, two parents, no cycle
    tests.append([[1,2],[1,3],[2,4],[3,5],[4,6],[5,6]])

    # 8) Two parents + existing cycle elsewhere
    tests.append([[1,2],[2,3],[3,1],[4,3],[3,5],[5,6]])

    # 9) Minimal n=2 forming cycle
    tests.append([[1,2],[2,1]])

    # 10) Two parents + cycle (choose earlier parent)
    tests.append([[1,2],[2,3],[3,4],[4,1],[1,5],[5,3]])

    sol = Solution()
    checksum = 0

    from timeit import default_timer as timer
    start = timer()

    iterations = 1000
    for iter in xrange(iterations):
        for edges in tests:
            # Pass a copy to mimic C++ pass-by-value behavior
            res = sol.findRedundantDirectedConnection([e[:] for e in edges])
            for v in res:
                checksum += v + (iter & 1)

    end = timer()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum:", checksum
    print "Elapsed time (ns):", elapsed_ns