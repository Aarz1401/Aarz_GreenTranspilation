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
    tests = [
        (1, 1, 1),
        (1, 10, 7),
        (10, 1, 4),
        (3, 3, 5),
        (2, 3, 6),
        (15, 20, 150),
        (20, 15, 213),
        (43, 47, 1000),
        (100, 100, 1000),
        (200, 150, 12345),
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += sol.findKthNumber(t[0], t[1], t[2])
        sink += checksum
    print(sink)