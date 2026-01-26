# Time:  O(n)
# Space: O(1)

class Solution(object):
    def minSwap(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: int
        """
        dp_no_swap, dp_swap = [0]*2, [1]*2
        for i in xrange(1, len(A)):
            dp_no_swap[i%2], dp_swap[i%2] = float("inf"), float("inf")
            if A[i-1] < A[i] and B[i-1] < B[i]:
                dp_no_swap[i%2] = min(dp_no_swap[i%2], dp_no_swap[(i-1)%2])
                dp_swap[i%2] = min(dp_swap[i%2], dp_swap[(i-1)%2]+1)
            if A[i-1] < B[i] and B[i-1] < A[i]:
                dp_no_swap[i%2] = min(dp_no_swap[i%2], dp_swap[(i-1)%2])
                dp_swap[i%2] = min(dp_swap[i%2], dp_no_swap[(i-1)%2]+1)
        return min(dp_no_swap[(len(A)-1)%2], dp_swap[(len(A)-1)%2])


if __name__ == "__main__":
    tests = []
    tests.append(([1], [2]))
    tests.append(([1, 3, 5, 4], [1, 2, 3, 7]))
    tests.append(([1, 200, 3, 400, 5, 600, 7, 800], [100, 2, 300, 4, 500, 6, 700, 8]))
    tests.append(([1, 3, 5, 7, 9], [2, 4, 6, 8, 10]))
    tests.append(([2, 4, 6, 8, 10], [1, 3, 5, 7, 9]))
    tests.append(([-5, -2, 1, 3, 4, 9], [-4, -3, 0, 2, 7, 10]))
    tests.append(([100, 2, 300, 4, 500, 6], [1, 200, 3, 400, 5, 600]))
    tests.append(([1, 3, 7, 9, 13], [2, 4, 8, 10, 14]))
    tests.append(([1, 3, 3, 5], [1, 2, 4, 4]))
    tests.append(([10, 2, 30, 4, 50, 6, 70, 8, 90, 10, 110, 12], [1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120]))

    sol = Solution()
    sink = 0

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for a, b in tests:
            r = sol.minSwap(a[:], b[:])
        #sink = checksum

    # print sink