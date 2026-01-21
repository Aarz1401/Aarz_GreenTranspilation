# Time:  O(m * log(m * n))
# Space: O(1)

class Solution(object):
    def findKthNumber(self, m, n, k):
        """
        :type m: int
        :type n: int
        :type k: int
        :rtype: int
        """
        def count(target, m, n):
            return sum(min(target//i, n) for i in xrange(1, m+1))

        left, right = 1, m*n
        while left <= right:
            mid = left + (right-left)/2
            if count(mid, m, n) >= k:
                right = mid-1
            else:
                left = mid+1
        return left


if __name__ == "__main__":
    # Benchmark test cases for Python2 Solution.findKthNumber(m, n, k)

    # Ensure that class Solution with method findKthNumber is defined/imported before running this.

    tests = [
        (1, 1, 1),
        (1, 10, 7),
        (10, 1, 3),
        (3, 3, 5),
        (10, 10, 50),
        (45, 37, 800),
        (100, 100, 5000),
        (300, 500, 120000),
        (500, 300, 75000),
        (1000, 1000, 500000),
    ]

    solver = Solution()
    checksum = 0

    import time
    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for m, n, k in tests:
            result = solver.findKthNumber(m, n, k)
            checksum += result

    end = time.time()
    elapsed_us = int((end - start) * 1000000)

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us