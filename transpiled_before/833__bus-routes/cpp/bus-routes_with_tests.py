# Time:  O(|V| + |E|)
# Space: O(|V| + |E|)

import collections


class Solution(object):
    def numBusesToDestination(self, routes, S, T):
        """
        :type routes: List[List[int]]
        :type S: int
        :type T: int
        :rtype: int
        """
        if S == T:
            return 0

        to_route = collections.defaultdict(set)
        for i, route in enumerate(routes):
            for stop in route:
                to_route[stop].add(i)

        result = 1
        q = [S]
        lookup = set([S])
        while q:
            next_q = []
            for stop in q:
                for i in to_route[stop]:
                    for next_stop in routes[i]:
                        if next_stop in lookup:
                            continue
                        if next_stop == T:
                            return result
                        next_q.append(next_stop)
                        to_route[next_stop].remove(i)
                        lookup.add(next_stop)
            q = next_q
            result += 1

        return -1


if __name__ == "__main__":
    # Prepare 10 diverse test cases
    allRoutes = []
    ST = []

    # Test 1: Basic example - expect 2
    allRoutes.append([[1, 2, 7], [3, 6, 7]])
    ST.append((1, 6))

    # Test 2: S == T - expect 0
    allRoutes.append([[1, 5, 9]])
    ST.append((5, 5))

    # Test 3: Unreachable target - expect -1
    allRoutes.append([[1, 2, 3], [4, 5, 6]])
    ST.append((1, 6))

    # Test 4: Direct bus available - expect 1
    allRoutes.append([[10, 20, 30], [5, 15]])
    ST.append((20, 30))

    # Test 5: Multiple transfers needed - expect 4
    allRoutes.append([[1, 5, 9], [9, 10], [10, 15], [15, 20]])
    ST.append((1, 20))

    # Test 6: Large stop IDs - expect 4
    allRoutes.append([[1000000, 2000000], [2000000, 3000000], [3000000, 4000000, 5000000], [5000000, 6000000], [7000000]])
    ST.append((1000000, 6000000))

    # Test 7: Branching paths - expect minimal transfers (likely 4)
    allRoutes.append([[1, 2, 3, 4], [4, 5, 6], [2, 7], [7, 8, 9], [9, 10]])
    ST.append((1, 10))

    # Test 8: Single large route - expect 1
    bigRoute = []
    for i in xrange(200):
        bigRoute.append(i)
    allRoutes.append([bigRoute])
    ST.append((0, 199))

    # Test 9: No routes - expect -1
    allRoutes.append([])
    ST.append((1, 2))

    # Test 10: Overlapping routes with immediate reach - likely 1
    allRoutes.append([[1, 1, 1, 2], [2, 3, 3, 4], [4, 5], [1, 6], [6, 7, 8, 9, 10]])
    ST.append((1, 10))

    sol = Solution()
    checksum = 0

    import time
    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(allRoutes)):
            # Make a copy of routes for each call to avoid any accidental state across runs
            routes = [list(r) for r in allRoutes[i]]
            S, T = ST[i]
            res = sol.numBusesToDestination(routes, S, T)
            checksum += res

    elapsed_ms = int(round((time.time() - start) * 1000))

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms