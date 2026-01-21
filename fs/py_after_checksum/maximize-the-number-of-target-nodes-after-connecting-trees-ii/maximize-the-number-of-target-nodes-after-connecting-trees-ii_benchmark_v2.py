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
    tests = [
        {'e1': [[0,1]], 'e2': [[0,1]]},
        {'e1': [[0,1],[0,2],[0,3],[0,4]], 'e2': [[0,1],[1,2],[2,3]]},
        {'e1': [[0,1],[1,2],[2,3],[3,4],[4,5]], 'e2': [[1,0],[1,2],[1,3],[1,4],[1,5]]},
        {'e1': [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], 'e2': [[0,1],[1,2],[2,3],[3,4]]},
        {'e1': [[0,2],[2,3],[3,4],[4,5],[5,6],[2,1],[6,7]], 'e2': [[3,0],[3,1],[3,2],[3,4],[3,5],[3,6],[3,7]]},
        {'e1': [[0,1],[1,2],[2,3],[3,4],[4,5],[5,6],[6,7],[7,8],[8,9]], 'e2': [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[3,7],[3,8]]},
        {'e1': [[0,1],[1,2]], 'e2': [[0,1],[0,2],[0,3],[0,4],[0,5],[0,6]]},
        {'e1': [[5,0],[5,1],[5,2],[5,3],[5,4],[5,6],[5,7],[5,8],[5,9],[5,10]], 'e2': [[0,1],[1,2],[2,3],[3,4],[4,5],[5,6],[6,7],[7,8],[8,9],[9,10]]},
        {'e1': [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[5,7],[5,8],[6,9],[4,10],[10,11]], 'e2': [[0,1],[1,2],[2,3],[3,4],[4,5],[2,6],[6,7],[6,8],[4,9],[9,10],[10,11],[11,12]]},
        {'e1': [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6],[3,7],[3,8],[4,9],[4,10],[5,11],[5,12],[6,13],[6,14]], 'e2': [[0,1],[1,2],[2,3],[3,4],[4,5],[5,6],[6,7],[7,8],[8,9],[9,10],[10,11],[11,12],[12,13],[13,14]]}
    ]

    sink = 0
    sol = Solution()

    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for t in tests:
            e1 = [edge[:] for edge in t['e1']]
            e2 = [edge[:] for edge in t['e2']]
            res = sol.maxTargetNodes(e1, e2)
            for x in res:
                checksum += x
        sink += checksum
    print(sink)