
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
    import time

    tests = []
    tests.append({'l': 10, 'n': 2, 'k': 0, 'position': [0, 5], 'time': [3, 4]})
    tests.append({'l': 20, 'n': 3, 'k': 1, 'position': [0, 2, 7], 'time': [1, 2, 3]})
    tests.append({'l': 50, 'n': 4, 'k': 1, 'position': [0, 10, 20, 35], 'time': [5, 2, 4, 1]})
    tests.append({'l': 100, 'n': 5, 'k': 2, 'position': [0, 5, 15, 30, 50], 'time': [1, 3, 2, 6, 4]})
    tests.append({'l': 200, 'n': 6, 'k': 3, 'position': [0, 2, 6, 14, 15, 30], 'time': [2, 2, 3, 1, 5, 4]})
    tests.append({'l': 150, 'n': 7, 'k': 4, 'position': [0, 3, 8, 9, 15, 21, 28], 'time': [3, 1, 4, 2, 6, 5, 2]})
    tests.append({'l': 300, 'n': 8, 'k': 5, 'position': [0, 1, 2, 6, 10, 15, 21, 28], 'time': [2, 2, 1, 3, 4, 5, 6, 7]})
    tests.append({'l': 500, 'n': 9, 'k': 6, 'position': [0, 4, 5, 11, 18, 26, 35, 45, 56], 'time': [1, 3, 2, 4, 6, 5, 3, 2, 1]})
    tests.append({'l': 800, 'n': 10, 'k': 7, 'position': [0, 2, 5, 9, 14, 20, 27, 35, 44, 54], 'time': [5, 4, 3, 2, 1, 2, 3, 4, 5, 6]})
    tests.append({'l': 1000, 'n': 12, 'k': 8, 'position': [0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66], 'time': [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]})

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for _ in xrange(iterations):
        for t in tests:
            result = sol.minTravelTime(t['l'], t['n'], t['k'], t['position'], t['time'])
            checksum += result
    end = time.time()

    elapsed = int((end - start) * 1000000)
    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed
