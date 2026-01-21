# Time:  O(n * 2^n)
# Space: O(2^n)

# dp, bitmasks
class Solution(object):
    def maxProfit(self, n, edges, score):
        """
        :type n: int
        :type edges: List[List[int]]
        :type score: List[int]
        :rtype: int
        """
        def popcount(x):
            return bin(x).count('1')

        adj = [0]*n
        for i, j in edges:
            adj[j] |= 1<<i
        dp = [-1]*(1<<n)
        dp[0] = 0 
        for mask in xrange(1<<n):
            if dp[mask] == -1:
                continue
            l = popcount(mask)+1
            for i in xrange(n):
                if mask&(1<<i):
                    continue
                if (mask & adj[i]) == adj[i]: 
                    dp[mask|(1<<i)] = max(dp[mask|(1<<i)], dp[mask]+l*score[i])
        return dp[-1]

if __name__ == "__main__":
    import time

    # Prepare 10 diverse test cases
    tests = []

    # 1) n = 0 (empty graph)
    tests.append({
        'n': 0,
        'edges': [],
        'score': []
    })

    # 2) Single node, positive score
    tests.append({
        'n': 1,
        'edges': [],
        'score': [5]
    })

    # 3) Two nodes with dependency 0 -> 1
    tests.append({
        'n': 2,
        'edges': [[0, 1]],
        'score': [3, 4]
    })

    # 4) Three nodes, no dependencies, mix of negative and positive scores
    tests.append({
        'n': 3,
        'edges': [],
        'score': [-1, 2, 1]
    })

    # 5) Star dependencies: 0 prerequisite for 1,2,3
    tests.append({
        'n': 4,
        'edges': [[0,1], [0,2], [0,3]],
        'score': [10, -5, 3, 2]
    })

    # 6) Chain 0 -> 1 -> 2 -> 3 -> 4
    tests.append({
        'n': 5,
        'edges': [[0,1], [1,2], [2,3], [3,4]],
        'score': [1, -2, 3, -4, 5]
    })

    # 7) Random small DAG
    tests.append({
        'n': 6,
        'edges': [[0,2], [1,2], [2,3], [1,4], [4,5]],
        'score': [7, -3, 5, -2, 4, 1]
    })

    # 8) Dense layered DAG: each j depends on all i < j (unique topological order)
    n = 8
    edges8 = []
    for j in range(1, n):
        for i in range(0, j):
            edges8.append([i, j])
    score8 = [1, 2, 3, 4, 5, 6, 7, 8]
    tests.append({'n': n, 'edges': edges8, 'score': score8})

    # 9) Two disconnected chains
    tests.append({
        'n': 10,
        'edges': [[0,1], [1,2], [2,3], [4,5], [5,6], [6,7], [7,8], [8,9]],
        'score': [9, -1, 8, -2, 7, -3, 6, -4, 5, -5]
    })

    # 10) Larger DAG with mixed dependencies
    tests.append({
        'n': 12,
        'edges': [
            [0,3], [1,3], [1,4], [2,5], [3,6], [4,6], [5,7], [6,8], [2,8],
            [7,9], [8,10], [9,11]
        ],
        'score': [3, -6, 7, 2, -1, 4, -3, 5, -2, 8, -4, 6]
    })

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for tc in tests:
            checksum += sol.maxProfit(tc['n'], tc['edges'], tc['score'])

    end = time.time()
    elapsed_ns = int(round((end - start) * 1e9))

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns