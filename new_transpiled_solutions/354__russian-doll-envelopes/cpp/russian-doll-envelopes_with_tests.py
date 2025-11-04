# Time:  O(nlogn + nlogk) = O(nlogn), k is the length of the result.
# Space: O(1)

class Solution(object):
    def maxEnvelopes(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        def insert(target):
            left, right = 0, len(result) - 1
            while left <= right:
                mid = left + (right - left) / 2
                if result[mid] >= target:
                    right = mid - 1
                else:
                    left = mid + 1
            if left == len(result):
                result.append(target)
            else:
                result[left] = target

        result = []

        envelopes.sort(lambda x, y: y[1] - x[1] if x[0] == y[0] else \
                                    x[0] - y[0])
        for envelope in envelopes:
            insert(envelope[1])

        return len(result)


if __name__ == "__main__":
    import time
    import random

    # Prepare 10 diverse test inputs
    base1 = []  # empty

    base2 = [
        [5, 4]
    ]

    base3 = []  # all duplicates
    for i in range(8):
        base3.append([2, 2])

    base4 = []  # strictly increasing chain
    for i in range(1, 21):
        base4.append([i, i])

    base5 = [  # mixed small sample
        [5, 4], [6, 4], [6, 7], [2, 3], [1, 1], [7, 8],
        [7, 7], [8, 9], [5, 5], [5, 3], [9, 6], [10, 10]
    ]

    base6 = []  # same width, varying heights
    for h in range(1, 31):
        base6.append([3, h])

    base7 = []  # strictly decreasing widths/heights
    for i in range(30, 0, -1):
        base7.append([i, i])

    base8 = [  # tie-breaker heavy (many equal widths)
        [4, 5], [4, 6], [4, 7], [4, 4],
        [5, 3], [5, 5], [5, 4],
        [6, 7], [6, 6], [6, 8],
        [7, 1], [7, 2], [7, 3]
    ]

    # Deterministic random dataset
    base9 = []
    _rng = random.Random(123456)
    for i in range(200):
        base9.append([_rng.randint(1, 10000), _rng.randint(1, 10000)])

    base10 = []  # ascending width, descending height (LIS of 1)
    N = 300
    for i in range(1, N + 1):
        base10.append([i, N - i + 1])

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        # Copy each base input to avoid in-place modification by sort
        t1 = list(base1)
        t2 = list(base2)
        t3 = list(base3)
        t4 = list(base4)
        t5 = list(base5)
        t6 = list(base6)
        t7 = list(base7)
        t8 = list(base8)
        t9 = list(base9)
        t10 = list(base10)

        checksum += sol.maxEnvelopes(t1)
        checksum += sol.maxEnvelopes(t2)
        checksum += sol.maxEnvelopes(t3)
        checksum += sol.maxEnvelopes(t4)
        checksum += sol.maxEnvelopes(t5)
        checksum += sol.maxEnvelopes(t6)
        checksum += sol.maxEnvelopes(t7)
        checksum += sol.maxEnvelopes(t8)
        checksum += sol.maxEnvelopes(t9)
        checksum += sol.maxEnvelopes(t10)

    end = time.time()
    elapsed_ns = int(round((end - start) * 1e9))

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns