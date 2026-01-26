# Time:  O(nlogn)
# Space: O(n)

import heapq


class Solution(object):
    def minRefuelStops(self, target, startFuel, stations):
        """
        :type target: int
        :type startFuel: int
        :type stations: List[List[int]]
        :rtype: int
        """
        max_heap = []
        stations.append((target, float("inf")))

        result = prev = 0
        for location, capacity in stations:
            startFuel -= location - prev
            while max_heap and startFuel < 0:
                startFuel += -heapq.heappop(max_heap)
                result += 1
            if startFuel < 0:
                return -1
            heapq.heappush(max_heap, -capacity)
            prev = location

        return result

if __name__ == "__main__":
    tests = [
        (100, 150, [[25, 10]]),
        (100, 50, [[25, 30], [50, 25], [75, 25]]),
        (100, 10, [[10, 60], [20, 10], [30, 10], [60, 30]]),
        (100, 1, [[10, 100]]),
        (1000000000, 100000, [[100000, 100000], [200000, 200000], [400000, 300000], [700000, 400000], [1000000, 500000], [2000000, 600000], [5000000, 700000], [10000000, 800000], [50000000, 900000], [100000000, 1000000]]),
        (100, 60, [[60, 40]]),
        (120, 25, [[10, 10], [20, 10], [30, 50], [60, 30], [90, 30]]),
        (500, 100, [[50, 50], [100, 50], [150, 50], [200, 50], [300, 100], [400, 100]]),
        (200, 200, [[50, 30], [150, 50]]),
        (300, 50, [[25, 25], [50, 25], [75, 25], [100, 100], [150, 50], [200, 50], [250, 50]])
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter_ in xrange(iterations):
        checksum = 0
        for tc in tests:
            target, startFuel, stations = tc
            checksum += sol.minRefuelStops(target, startFuel, stations)
        sink += checksum
    print(sink)