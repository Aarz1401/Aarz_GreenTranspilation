# Time:  O(n)
# Space: O(n)

# flood fill, bfs, counting sort, greedy
"""
n = 11
edges = [[0,1],[1,2],[2,3],[5,6],[6,7]]
max is 367 but ans is 366, which is wrong by greedy
"""
class Solution_WA(object):
    def maxScore(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        def bfs(u):
            lookup[u] = True
            result = [u]
            for u in result:
                for v in adj[u]:
                    if lookup[v]:
                        continue
                    lookup[v] = True
                    result.append(v)
            return result

        def f(l, r, is_cycle):
            a = b = r
            result = 0
            for c in reversed(xrange(l, r)):
                result += a*c
                a, b = b, c
            if is_cycle:
                result += a*b
            return result

        adj = [[] for _ in xrange(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        cycles, chains = [], []
        lookup = [False]*n
        for u in xrange(n):
            if lookup[u]:
                continue
            comp = bfs(u)
            if all(len(adj[x]) == 2 for x in comp):
                cycles.append(len(comp))
            else:
                chains.append(len(comp))
        result = 0
        for l in cycles:
            result += f(n-l+1, n, True)
            n -= l
        cnt = [0]*((max(chains) if chains else 0)+1)
        for l in chains:
            cnt[l] += 1
        for l in reversed(xrange(len(cnt))):
            for _ in xrange(cnt[l]):
                result += f(n-l+1, n, False)
                n -= l
        return result

Solution = Solution_WA

if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs (graphs)
    tests = []

    # 1) Empty graph
    tests.append((0, []))

    # 2) Single node, no edges
    tests.append((1, []))

    # 3) Single edge (chain of length 2)
    tests.append((2, [[0,1]]))

    # 4) Triangle cycle (length 3)
    tests.append((3, [[0,1],[1,2],[2,0]]))

    # 5) Square with a tail (component not a cycle)
    tests.append((5, [[0,1],[1,2],[2,3],[3,0],[0,4]]))

    # 6) Two disjoint cycles: triangle and 4-cycle
    tests.append((7, [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]))

    # 7) Star graph centered at 0
    tests.append((6, [[0,1],[0,2],[0,3],[0,4],[0,5]]))

    # 8) Path of length 6
    tests.append((6, [[0,1],[1,2],[2,3],[3,4],[4,5]]))

    # 9) Mixed: chain of 3, cycle of 5, isolated node
    tests.append((9, [[0,1],[1,2], [3,4],[4,5],[5,6],[6,7],[7,3]]))

    # 10) Larger mixed: 4-cycle, path of 5, path of 3
    tests.append((12, [
        [0,1],[1,2],[2,3],[3,0],        # 4-cycle
        [4,5],[5,6],[6,7],[7,8],        # path of 5 nodes
        [9,10],[10,11]                  # path of 3 nodes
    ]))

    sol = Solution()

    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for t in tests:
            n = t[0]
            edges = [e[:] for e in t[1]]  # make a local copy to match non-const ref signature
            checksum += sol.maxScore(n, edges)

    end = time.time()
    elapsed_ns = int(round((end - start) * 1e9))

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns