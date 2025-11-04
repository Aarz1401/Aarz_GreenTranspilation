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
    import time

    # Define 10 diverse test inputs
    tests = [
        {'target': 1, 'startFuel': 1, 'stations': []},  # 0 stops
        {'target': 100, 'startFuel': 1, 'stations': [[10, 100]]},  # impossible
        {'target': 100, 'startFuel': 10, 'stations': [[10, 60], [20, 30], [30, 30], [60, 40]]},  # typical => 2
        {'target': 100, 'startFuel': 50, 'stations': [[25, 25], [50, 25]]},  # needs 2
        {'target': 1000, 'startFuel': 299, 'stations': [[100, 100], [200, 100], [300, 100], [400, 100]]},  # impossible
        {'target': 100, 'startFuel': 100, 'stations': [[10, 10], [20, 20]]},  # already enough fuel
        {'target': 100, 'startFuel': 25, 'stations': [[25, 25], [25, 25], [50, 25], [75, 25]]},  # duplicate positions
        {'target': 5000, 'startFuel': 500, 'stations': [[400, 300], [800, 300], [1200, 300], [1600, 300], [2000, 300], [2400, 300], [2800, 300], [3200, 300], [3600, 300], [4000, 300], [4400, 300], [4800, 300]]},  # many mid-size stops
        {'target': 300, 'startFuel': 50, 'stations': [[25, 0], [50, 0], [60, 90], [120, 0], [180, 30], [240, 100]]},  # includes zero-capacity stations
        {'target': 1000000, 'startFuel': 100000, 'stations': [[100000, 100000], [200000, 100000], [300000, 100000], [400000, 100000], [500000, 100000], [600000, 100000], [700000, 100000], [800000, 100000], [900000, 100000]]},  # large numbers
    ]

    sol = Solution()
    checksum = 0L

    start = time.time()

    iterations = 1000
    for it in xrange(iterations):
        for i, t in enumerate(tests):
            # Pass a shallow copy of stations to avoid mutation across iterations
            result = sol.minRefuelStops(t['target'], t['startFuel'], list(t['stations']))
            checksum += long(result) * long((i + 1) + (it % 7))

    end = time.time()
    elapsed_ns = int((end - start) * 1e9)

    print 'Checksum: %d' % checksum
    print 'Elapsed time (ns): %d' % elapsed_ns