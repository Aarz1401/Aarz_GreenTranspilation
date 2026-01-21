# Time:  O(n^4)
# Space: O(n^3)

class Solution(object):
    def splitArraySameAverage(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        def possible(total, n):
            for i in xrange(1, n//2+1):
                if total*i%n == 0:
                    return True
            return False
        n, s = len(A), sum(A)
        if not possible(n, s):
            return False

        sums = [set() for _ in xrange(n//2+1)]
        sums[0].add(0)
        for num in A:  # O(n) times
            for i in reversed(xrange(1, n//2+1)):  # O(n) times
                for prev in sums[i-1]:  # O(1) + O(2) + ... O(n/2) = O(n^2) times
                    sums[i].add(prev+num)
        for i in xrange(1, n//2+1):
            if s*i%n == 0 and s*i//n in sums[i]:
                return True
        return False

if __name__ == "__main__":
    tests = [
        [1, 2],
        [1, 2, 3, 4, 5, 6, 7, 8],
        [5, 5, 5, 5],
        [0, 0, 0, 0, 0, 0, 0],
        [2, 0, 5, 6, 16, 12, 15, 9],
        [3, 3, 3, 4, 5],
        [1, 2, 3, 4, 6, 8, 10],
        [9, 1, 2, 3, 4, 5, 6, 7, 8],
        [1, 1, 1, 1, 1, 1],
        [10, 20, 30, 40, 50, 60]
    ]

    s = Solution()
    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for A in tests:
            r = 1 if s.splitArraySameAverage(A) else 0
        #sink = checksum