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
    tests = [
        {'n': 1, 'edges': [], 'score': [5]},
        {'n': 2, 'edges': [(0, 1)], 'score': [3, 4]},
        {'n': 3, 'edges': [(0, 1), (0, 2)], 'score': [2, -1, 5]},
        {'n': 4, 'edges': [(0, 2), (1, 3)], 'score': [4, 1, 2, 3]},
        {'n': 5, 'edges': [(0, 1), (1, 2), (2, 3), (3, 4)], 'score': [7, -3, 4, -2, 5]},
        {'n': 6, 'edges': [], 'score': [1, 2, 3, 4, 5, 6]},
        {'n': 8, 'edges': [(0, 3), (0, 4), (1, 4), (1, 5), (2, 5), (3, 6), (4, 6), (5, 7)], 'score': [3, -5, 2, 8, 7, -1, 4, 6]},
        {'n': 10, 'edges': [(0, 2), (1, 2), (2, 3), (2, 4), (4, 6), (3, 5), (5, 7), (6, 8), (7, 9)], 'score': [5, -2, 7, 1, -3, 4, 9, -6, 2, 8]},
        {'n': 9, 'edges': [(0, 2), (0, 3), (1, 3), (1, 4), (2, 5), (3, 5), (3, 6), (4, 6), (5, 7), (6, 8)], 'score': [0, 10, -4, 3, -1, 2, 6, 5, -2]},
        {'n': 11, 'edges': [(0, 3), (1, 4), (2, 5), (0, 4), (1, 5), (3, 6), (4, 6), (4, 7), (5, 7), (6, 8), (7, 9), (8, 10), (9, 10)], 'score': [4, -3, 5, 2, -6, 7, 1, 8, -2, 3, 6]},
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for tc in tests:
            res = sol.maxProfit(tc['n'], tc['edges'], tc['score'])
            checksum += res
        sink += checksum
    print(sink)