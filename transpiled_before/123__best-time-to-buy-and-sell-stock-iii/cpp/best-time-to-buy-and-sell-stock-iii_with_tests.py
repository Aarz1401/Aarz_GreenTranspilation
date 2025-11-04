# Time:  O(n)
# Space: O(1)

class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        hold1, hold2 = float("-inf"), float("-inf")
        release1, release2 = 0, 0
        for i in prices:
            hold1 = max(hold1, -i)
            release1 = max(release1, hold1 + i)
            hold2 = max(hold2, release1 - i)
            release2 = max(release2, hold2 + i)
        return release2


# Time:  O(k * n)
# Space: O(k)
class Solution2(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        def maxAtMostKPairsProfit(prices, k):
            max_buy = [float("-inf") for _ in xrange(k + 1)]
            max_sell = [0 for _ in xrange(k + 1)]
            for i in xrange(len(prices)):
                for j in xrange(1, k + 1):
                    max_buy[j] = max(max_buy[j], max_sell[j-1] - prices[i])
                    max_sell[j] = max(max_sell[j], max_buy[j] + prices[i])
            return max_sell[k]

        return maxAtMostKPairsProfit(prices, 2)


# Time:  O(n)
# Space: O(n)
class Solution3(object):
    # @param prices, a list of integer
    # @return an integer
    def maxProfit(self, prices):
        min_price, max_profit_from_left, max_profits_from_left = \
            float("inf"), 0, []
        for price in prices:
            min_price = min(min_price, price)
            max_profit_from_left = max(max_profit_from_left, price - min_price)
            max_profits_from_left.append(max_profit_from_left)

        max_price, max_profit_from_right, max_profits_from_right = 0, 0, []
        for i in reversed(range(len(prices))):
            max_price = max(max_price, prices[i])
            max_profit_from_right = max(max_profit_from_right,
                                        max_price - prices[i])
            max_profits_from_right.insert(0, max_profit_from_right)

        max_profit = 0
        for i in range(len(prices)):
            max_profit = max(max_profit,
                             max_profits_from_left[i] +
                             max_profits_from_right[i])

        return max_profit


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    test1 = []                                      # empty
    test2 = [5]                                     # single element
    test3 = [1, 2]                                  # simple increasing
    test4 = [5, 1]                                  # simple decreasing
    test5 = [1, 2, 3, 4, 5, 6]                      # strictly increasing
    test6 = [6, 5, 4, 3, 2, 1]                      # strictly decreasing
    test7 = [3, 3, 5, 0, 0, 3, 1, 4]                # typical multi-transaction pattern
    test8 = [2, 1, 2, 0, 1]                         # small waves
    m = 2147483647
    test9 = [m - 3, m - 2, m - 1, m, m - 4, m]      # near int max values

    # Long pseudo-random but deterministic pattern, non-negative prices
    test10 = []
    for i in xrange(5000):
        price = (i * 97) % 1000
        if i % 7 == 0:
            price += 500
        if i % 13 == 0:
            price //= 2
        test10.append(price)

    tests = [
        test1, test2, test3, test4, test5, test6, test7, test8, test9, test10
    ]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for t in tests:
            checksum += sol.maxProfit(t)

    end = time.time()
    ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", ms