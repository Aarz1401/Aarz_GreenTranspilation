
# Time:  O((n * m * 2^n + m * 3^n) * log(n * m * 2^n + m * 3^n)) = O(m * 3^n * log(m * 3^n))
# Space: O(n * m * 2^n + m * 3^n) = O(m * 3^n)

import heapq


# dijkstra's algorithm, submask enumeration
class Solution(object):
    def minTime(self, n, k, m, time, mul):
        """
        :type n: int
        :type k: int
        :type m: int
        :type time: List[int]
        :type mul: List[float]
        :rtype: float
        """
        def update(d, r, s, mask, submask):
            t = lookup[submask]*mul[s]
            nr = r^1
            ns = (s+int(t))%m
            new_mask = mask^submask
            nd = d+t
            if dist[nr][ns][new_mask] > nd:
                dist[nr][ns][new_mask] = nd
                heapq.heappush(min_heap, (nd, nr, ns, new_mask))
    
        popcount = [0]*(1<<n)  # for better performance
        for i in xrange(1, (1<<n)):
            popcount[i] = popcount[i>>1]+(i&1)
        lookup = [max(time[i] for i in xrange(n) if mask&(1<<i)) if mask else 0 for mask in xrange(1<<n)]  # Time: O(n * 2^n)
        INF = float("inf")
        dist = [[[INF]*(1<<n) for _ in xrange(m)] for _ in xrange(2)]
        dist[0][0][(1<<n)-1] = 0.0
        min_heap = [(0.0, 0, 0, (1<<n)-1)]
        while min_heap:
            d, r, s, mask = heapq.heappop(min_heap)  # Total Time: O((n * m * 2^n + m * 3^n) * log(n * m * 2^n + m * 3^n))
            if d != dist[r][s][mask]:
                continue
            if mask == 0:
                assert(r == 1)
                return d
            if r == 0:
                submask = mask
                while submask:  # Total Time: O(m * 3^n)
                    if popcount[submask] <= k:
                        update(d, r, s, mask, submask)
                    submask = (submask-1)&mask
            else:
                for i in xrange(n):  # Total Time: O(n * m * 2^n)
                    if mask&(1<<i):
                        continue
                    update(d, r, s, mask, 1<<i)
        return -1.0

if __name__ == "__main__":
    import sys
    import time as _time

    tests = []
    tests.append({'n': 1, 'k': 1, 'm': 1, 'time': [5], 'mul': [1.0]})
    tests.append({'n': 2, 'k': 1, 'm': 2, 'time': [3, 7], 'mul': [0.8, 1.2]})
    tests.append({'n': 3, 'k': 2, 'm': 3, 'time': [4, 2, 9], 'mul': [1.0, 1.5, 0.5]})
    tests.append({'n': 4, 'k': 2, 'm': 4, 'time': [2, 5, 1, 7], 'mul': [0.9, 1.1, 1.3, 0.7]})
    tests.append({'n': 5, 'k': 3, 'm': 3, 'time': [8, 3, 6, 2, 9], 'mul': [1.0, 0.95, 1.2]})
    tests.append({'n': 6, 'k': 2, 'm': 5, 'time': [5, 4, 7, 3, 8, 6], 'mul': [1.2, 0.8, 1.0, 1.5, 0.6]})
    tests.append({'n': 7, 'k': 3, 'm': 2, 'time': [9, 1, 4, 7, 2, 5, 3], 'mul': [1.1, 0.9]})
    tests.append({'n': 8, 'k': 4, 'm': 4, 'time': [6, 2, 9, 1, 7, 3, 8, 5], 'mul': [1.0, 0.75, 1.25, 0.5]})
    tests.append({'n': 9, 'k': 3, 'm': 6, 'time': [3, 6, 1, 8, 2, 7, 4, 9, 5], 'mul': [0.9, 1.05, 1.2, 0.8, 1.3, 0.7]})
    tests.append({'n': 5, 'k': 1, 'm': 7, 'time': [10, 3, 8, 2, 6], 'mul': [0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1]})

    sol = Solution()
    checksum = 0.0

    start = _time.time()
    iterations = 1
    for _ in xrange(iterations):
        for tc in tests:
            checksum += sol.minTime(tc['n'], tc['k'], tc['m'], tc['time'], tc['mul'])
    end = _time.time()
    elapsed_ms = (end - start) * 1000.0

    sys.stdout.write("Checksum: %.6f\n" % checksum)
    sys.stdout.write("Elapsed time (ms): %.6f\n" % elapsed_ms)
