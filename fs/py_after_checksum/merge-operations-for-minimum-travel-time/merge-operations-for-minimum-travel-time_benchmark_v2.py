
# Time:  O((n - k) * k^3)
# Space: O(k^2)

import collections


# prefix sum, dp
class Solution(object):
    def minTravelTime(self, l, n, k, position, time):
        """
        :type l: int
        :type n: int
        :type k: int
        :type position: List[int]
        :type time: List[int]
        :rtype: int
        """
        prefix = [0]*(n+1)
        for i in xrange(n):
            prefix[i+1] = prefix[i]+time[i]
        dp = collections.defaultdict(lambda: collections.defaultdict(lambda: float("inf")))
        dp[0][time[0]] = 0
        for cnt in xrange(2, (n-k)+1):
            new_dp = collections.defaultdict(lambda: collections.defaultdict(lambda: float("inf")))
            for i in xrange(cnt-1, (cnt-1)+(k+1)):
                for j in xrange(cnt-2, i):
                    for t, c in dp[j].iteritems():
                        new_dp[i][prefix[i+1]-prefix[j+1]] = min(new_dp[i][prefix[i+1]-prefix[j+1]], (position[i]-position[j])*t+c)
            dp = new_dp
        return min(dp[n-1].itervalues())


if __name__ == "__main__":
    tests = [
        {'l': 10, 'n': 2, 'k': 0, 'position': [0, 5], 'time': [2, 3]},
        {'l': 20, 'n': 3, 'k': 1, 'position': [0, 4, 9], 'time': [1, 2, 3]},
        {'l': 30, 'n': 5, 'k': 2, 'position': [0, 2, 5, 9, 14], 'time': [1, 3, 2, 4, 1]},
        {'l': 40, 'n': 6, 'k': 3, 'position': [0, 1, 3, 6, 10, 15], 'time': [2, 2, 1, 3, 2, 1]},
        {'l': 50, 'n': 7, 'k': 5, 'position': [0, 1, 2, 3, 4, 5, 6], 'time': [1, 1, 1, 1, 1, 1, 1]},
        {'l': 60, 'n': 8, 'k': 6, 'position': [0, 2, 3, 7, 11, 12, 13, 20], 'time': [2, 1, 3, 1, 2, 3, 1, 2]},
        {'l': 70, 'n': 9, 'k': 7, 'position': [0, 3, 5, 8, 12, 13, 17, 18, 25], 'time': [3, 2, 4, 1, 2, 5, 1, 3, 2]},
        {'l': 80, 'n': 10, 'k': 8, 'position': [0, 5, 6, 10, 11, 16, 20, 23, 27, 30], 'time': [2, 2, 3, 4, 1, 3, 2, 4, 1, 2]},
        {'l': 90, 'n': 12, 'k': 10, 'position': [0, 1, 3, 6, 10, 15, 21, 22, 24, 27, 31, 36], 'time': [1, 2, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1]},
        {'l': 100, 'n': 15, 'k': 13, 'position': [0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 56, 60, 65, 71], 'time': [1, 3, 2, 4, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1]},
    ]

    sol = Solution()

    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            res = sol.minTravelTime(t['l'], t['n'], t['k'], list(t['position']), list(t['time']))
            checksum += res
        sink += checksum
    print(sink)
    #print(sink)
