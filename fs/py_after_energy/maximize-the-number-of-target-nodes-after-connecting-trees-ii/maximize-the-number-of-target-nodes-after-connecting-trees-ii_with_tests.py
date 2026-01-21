# Time:  O(n + m)
# Space: O(n + m)

# bfs
class Solution(object):
    def maxTargetNodes(self, edges1, edges2):
        """
        :type edges1: List[List[int]]
        :type edges2: List[List[int]]
        :rtype: List[int]
        """
        def bfs(adj):
            result = [0]*len(adj)
            parity = 0
            lookup = [-1]*len(adj)
            lookup[0] = parity
            q = [0]
            while q:
                new_q = []
                for u in q:
                    for v in adj[u]:
                        if lookup[v] != -1:
                            continue
                        lookup[v] = parity^1
                        new_q.append(v)
                q = new_q
                parity ^= 1
            cnt = sum(lookup)
            return [cnt if lookup[u] else len(adj)-cnt for u in xrange(len(adj))]
    
        def find_adj(edges):
            adj = [[] for _ in xrange(len(edges)+1)]
            for u, v in edges:
                adj[u].append(v)
                adj[v].append(u)
            return adj

        adj2 = find_adj(edges2)
        mx = max(bfs(adj2))
        adj1 = find_adj(edges1)
        return [mx+x for x in bfs(adj1)]

if __name__ == "__main__":
    import time

    tests = []

    # Test 1: n=1 (single node)
    edges1_1 = []
    edges2_1 = []
    tests.append((edges1_1, edges2_1))

    # Test 2: n=2
    edges1_2 = [[0,1]]
    edges2_2 = [[0,1]]
    tests.append((edges1_2, edges2_2))

    # Test 3: n=3 (chain vs star)
    edges1_3 = [[0,1],[1,2]]
    edges2_3 = [[0,1],[0,2]]
    tests.append((edges1_3, edges2_3))

    # Test 4: n=4 (chain vs star)
    edges1_4 = [[0,1],[1,2],[2,3]]
    edges2_4 = [[0,1],[0,2],[0,3]]
    tests.append((edges1_4, edges2_4))

    # Test 5: n=5 (star centered at 2 vs chain)
    edges1_5 = [[2,0],[2,1],[2,3],[2,4]]
    edges2_5 = [[0,1],[1,2],[2,3],[3,4]]
    tests.append((edges1_5, edges2_5))

    # Test 6: n=6 (two different trees)
    edges1_6 = [[0,1],[1,2],[1,3],[3,4],[4,5]]
    edges2_6 = [[0,2],[2,1],[1,3],[3,4],[4,5]]
    tests.append((edges1_6, edges2_6))

    # Test 7: n=7 (binary-like vs chain)
    edges1_7 = [[0,1],[0,2],[1,3],[1,4],[2,5],[5,6]]
    edges2_7 = [[0,1],[1,2],[2,3],[3,4],[4,5],[5,6]]
    tests.append((edges1_7, edges2_7))

    # Test 8: n=8 (skewed vs star centered at 7)
    edges1_8 = [[0,1],[0,2],[2,3],[2,4],[4,5],[5,6],[6,7]]
    edges2_8 = [[7,0],[7,1],[7,2],[7,3],[7,4],[7,5],[7,6]]
    tests.append((edges1_8, edges2_8))

    # Test 9: n=9 (random vs reversed chain-like)
    edges1_9 = [[0,1],[1,2],[2,3],[3,4],[1,5],[5,6],[6,7],[7,8]]
    edges2_9 = [[0,8],[8,7],[7,6],[6,5],[5,4],[4,3],[3,2],[2,1]]
    tests.append((edges1_9, edges2_9))

    # Test 10: n=10 (balanced-ish vs chain)
    edges1_10 = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[5,7],[5,8],[6,9]]
    edges2_10 = [[0,9],[9,8],[8,7],[7,6],[6,5],[5,4],[4,3],[3,2],[2,1]]
    tests.append((edges1_10, edges2_10))

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for iter in range(iterations):
        for tt in tests:
            e1 = [edge[:] for edge in tt[0]]
            e2 = [edge[:] for edge in tt[1]]
            res = sol.maxTargetNodes(e1, e2)
            for v in res:
                checksum += (v ^ iter)
    end = time.time()

    elapsed_ns = int((end - start) * 1000000000)
    print "Checksum: " + str(checksum)
    print "Elapsed (ns): " + str(elapsed_ns)