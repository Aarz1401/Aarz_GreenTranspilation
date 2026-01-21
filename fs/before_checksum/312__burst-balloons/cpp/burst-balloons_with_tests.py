# Time:  O(n^3)
# Space: O(n^2)


class Solution(object):
    def maxCoins(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        coins = [1] + [i for i in nums if i > 0] + [1]
        n = len(coins)
        max_coins = [[0 for _ in xrange(n)] for _ in xrange(n)]

        for k in xrange(2, n):
            for left in xrange(n - k):
                right = left + k
                for i in xrange(left + 1, right):
                    max_coins[left][right] = \
                        max(max_coins[left][right],
                            coins[left] * coins[i] * coins[right] +
                            max_coins[left][i] +
                            max_coins[i][right])

        return max_coins[0][-1]


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    tests = [
        [],                                   # 1. Empty
        [5],                                  # 2. Single element
        [1, 5],                               # 3. Two elements
        [0, -1, 2, 0, 3, -5],                 # 4. Zeros and negatives
        [1, 1, 1, 1, 1, 1, 1, 1],             # 5. All ones
        [1, 2, 3, 4, 5],                      # 6. Increasing
        [5, 4, 3, 2, 1],                      # 7. Decreasing
        [7, 9, 8, 0, 1, 2, 3],                # 8. Mixed with zero
        [100, 1, 100, 1, 100],                # 9. Larger values mix
        [3, 1, 5, 8, 2, 7, 9, 4, 6, 1, 2, 3]  # 10. Longer mixed
    ]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for t in xrange(len(tests)):
            data = list(tests[t])  # copy per run
            res = sol.maxCoins(data)
            checksum += int(res) + int((iter + 1) * (t + 1))

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us