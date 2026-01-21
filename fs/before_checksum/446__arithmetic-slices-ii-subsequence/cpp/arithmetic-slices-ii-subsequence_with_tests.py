# Time:  O(n^2)
# Space: O(n * d)

import collections


class Solution(object):
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        result = 0
        dp = [collections.defaultdict(int) for i in xrange(len(A))]
        for i in xrange(1, len(A)):
            for j in xrange(i):
                diff = A[i]-A[j]
                dp[i][diff] += 1
                if diff in dp[j]:
                    dp[i][diff] += dp[j][diff]
                    result += dp[j][diff]
        return result


if __name__ == "__main__":
    import time

    INT_MAX = 2147483647

    tests = []
    # 1. Empty array
    tests.append([])

    # 2. Single element
    tests.append([42])

    # 3. Two elements
    tests.append([1, 2])

    # 4. Simple arithmetic progression of length 3
    tests.append([1, 3, 5])

    # 5. Non-arithmetic triple
    tests.append([1, 4, 9])

    # 6. All equal elements
    tests.append([7, 7, 7, 7])

    # 7. Mixed negatives and positives with constant step
    tests.append([-5, -1, 3, 7, 11])

    # 8. Large values near INT_MAX to test diff handling
    tests.append([INT_MAX, INT_MAX - 1, INT_MAX - 2, INT_MAX - 3])

    # 9. Longer arithmetic progression (even numbers)
    ap = []
    for i in xrange(12):
        ap.append(i * 2)
    tests.append(ap)

    # 10. Larger mixed dataset with various patterns
    tests.append([
        5, 1, 9, 3, 7, 13, 2, 8, 14, 0,
        6, 12, 4, 10, 11, 15, 20, 25, -5, -1,
        -9, 100, 105, 110, 115, 200, 195, 190, 180, 170,
        160, 150, 140, 130, 120, 300, 301, 303, 306, 310,
        -100, -90, -80, -70, -60, -50, -40, -30, -20, -10
    ])

    sol = Solution()
    checksum = 0L

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            checksum += sol.numberOfArithmeticSlices(tests[i])

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print("Checksum: %d" % checksum)
    print("Elapsed time (microseconds): %d" % elapsed_us)