
# Time:  O(n) on average, using Median of Medians could achieve O(n) (Intro Select)
# Space: O(n)

import random


class Solution(object):
    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        def nth_element(nums, n, compare=lambda a, b: a < b):
            def tri_partition(nums, left, right, target, compare):
                mid = left
                while mid <= right:
                    if nums[mid] == target:
                        mid += 1
                    elif compare(nums[mid], target):
                        nums[left], nums[mid] = nums[mid], nums[left]
                        left += 1
                        mid += 1
                    else:
                        nums[mid], nums[right] = nums[right], nums[mid]
                        right -= 1
                return left, right

            left, right = 0, len(nums)-1
            while left <= right:
                pivot_idx = random.randint(left, right)
                pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
                if pivot_left <= n <= pivot_right:
                    return
                elif pivot_left > n:
                    right = pivot_left-1
                else:  # pivot_right < n.
                    left = pivot_right+1

        profits = []
        v_p_stk = []  # mono stack, where v is increasing and p is strictly decreasing
        v, p = -1, -1
        while p+1 < len(prices): # at most O(n) peaks, so v_p_stk and profits are both at most O(n) space
            for v in xrange(p+1, len(prices)-1):
                if prices[v] < prices[v+1]:
                    break
            else:
                v = len(prices)-1
            for p in xrange(v, len(prices)-1):
                if prices[p] > prices[p+1]:
                    break 
            else:
                p = len(prices)-1
            while v_p_stk and prices[v_p_stk[-1][0]] > prices[v]:  # not overlapped
                last_v, last_p = v_p_stk.pop()
                profits.append(prices[last_p]-prices[last_v])  # count [prices[last_v], prices[last_p]] interval
            while v_p_stk and prices[v_p_stk[-1][1]] <= prices[p]:  # overlapped
                # prices[last_v] <= prices[v] <= prices[last_p] <= prices[p],
                # treat overlapped as [prices[v], prices[last_p]], [prices[last_v], prices[p]] intervals due to invariant max profit
                last_v, last_p = v_p_stk.pop()
                profits.append(prices[last_p]-prices[v])  # count [prices[v], prices[last_p]] interval
                v = last_v
            v_p_stk.append((v, p))  # keep [prices[last_v], prices[p]] interval to check overlapped      
        while v_p_stk:
            last_v, last_p = v_p_stk.pop()
            profits.append(prices[last_p]-prices[last_v])  # count [prices[last_v], prices[last_p]] interval
        if k > len(profits):
            k = len(profits)
        else:
            nth_element(profits, k-1, compare=lambda a, b: a > b)
        return sum(profits[i] for i in xrange(k))  # top k profits of nonoverlapped intervals


# Time:  O(k * n)
# Space: O(k)
class Solution2(object):
    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        def maxAtMostNPairsProfit(sprices):
            profit = 0
            for i in xrange(len(prices) - 1):
                profit += max(0, prices[i + 1] - prices[i])
            return profit

        def maxAtMostKPairsProfit(prices, k):
            max_buy = [float("-inf") for _ in xrange(k + 1)]
            max_sell = [0 for _ in xrange(k + 1)]
            for i in xrange(len(prices)):
                for j in xrange(1, k + 1):
                    max_buy[j] = max(max_buy[j], max_sell[j-1] - prices[i])
                    max_sell[j] = max(max_sell[j], max_buy[j] + prices[i])
            return max_sell[k]

        if k >= len(prices) // 2:
            return maxAtMostNPairsProfit(prices)

        return maxAtMostKPairsProfit(prices, k)


if __name__ == "__main__":
    from time import time

    pricesList = []
    ks = []

    # 1. Empty prices
    pricesList.append([])
    ks.append(3)

    # 2. Single element
    pricesList.append([5])
    ks.append(1)

    # 3. Strictly increasing
    pricesList.append([1, 2, 3, 4, 5])
    ks.append(10)

    # 4. Strictly decreasing
    pricesList.append([5, 4, 3, 2, 1])
    ks.append(2)

    # 5. Mixed typical case
    pricesList.append([3, 2, 6, 5, 0, 3])
    ks.append(2)

    # 6. All equal elements
    pricesList.append([2, 2, 2, 2, 2, 2])
    ks.append(100)

    # 7. Multiple rising peaks
    pricesList.append([1, 7, 2, 8, 3, 9, 4, 10, 5, 11])
    ks.append(4)

    # 8. Alternating high-low
    pricesList.append([10, 1, 10, 1, 10, 1, 10, 1])
    ks.append(2)

    # 9. Long repeating up-down pattern (size ~2000)
    pattern = [1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10]
    longPattern = []
    while len(longPattern) < 2000:
        longPattern.extend(pattern)
    longPattern = longPattern[:2000]
    pricesList.append(longPattern)
    ks.append(500)

    # 10. Pseudo-random-like large sequence (size 3000)
    largeSeq = []
    x = 123456789
    for i in xrange(3000):
        x = (1664525 * x + 1013904223) & 0xFFFFFFFF
        largeSeq.append(int(x % 100000))
    pricesList.append(largeSeq)
    ks.append(1000)

    sol = Solution()
    checksum = 0

    start = time()

    iterations = 1000
    for iter in xrange(iterations):
        checksum += sol.maxProfit(ks[0], pricesList[0])
        checksum += sol.maxProfit(ks[1], pricesList[1])
        checksum += sol.maxProfit(ks[2], pricesList[2])
        checksum += sol.maxProfit(ks[3], pricesList[3])
        checksum += sol.maxProfit(ks[4], pricesList[4])
        checksum += sol.maxProfit(ks[5], pricesList[5])
        checksum += sol.maxProfit(ks[6], pricesList[6])
        checksum += sol.maxProfit(ks[7], pricesList[7])
        checksum += sol.maxProfit(ks[8], pricesList[8])
        checksum += sol.maxProfit(ks[9], pricesList[9])

    end = time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms
