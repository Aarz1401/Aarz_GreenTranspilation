# Time:  O(n)
# Space: O(n)

class Solution(object):
    def bestRotation(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        N = len(A)
        change = [1] * N
        for i in xrange(N):
            change[(i-A[i]+1)%N] -= 1
        for i in xrange(1, N):
            change[i] += change[i-1]
        return change.index(max(change))


if __name__ == "__main__":
    tests = [
        [0],
        [1, 0],
        [2, 2, 1],
        [0, 0, 0, 0],
        [4, 3, 2, 1, 0],
        [0, 1, 2, 3, 4, 5],
        [6, 5, 4, 3, 2, 1, 0],
        [1, 3, 5, 7, 0, 2, 4, 6],
        [2, 0, 6, 3, 1, 4, 9, 7, 5, 8],
        [14, 0, 14, 7, 3, 5, 10, 2, 12, 6, 8, 1, 9, 4, 11]
    ]

    s = Solution()
    sink = 0
    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for t in tests:
            checksum += s.bestRotation(t[:])
        sink += checksum
    print(sink)
    # print sink