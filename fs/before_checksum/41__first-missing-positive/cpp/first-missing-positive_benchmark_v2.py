# Time:  O(n)
# Space: O(1)

class Solution(object):
    # @param A, a list of integers
    # @return an integer
    def firstMissingPositive(self, A):
        i = 0
        while i < len(A):
            if A[i] > 0 and A[i] - 1 < len(A) and A[i] != A[A[i]-1]:
                A[A[i]-1], A[i] = A[i], A[A[i]-1]
            else:
                i += 1

        for i, integer in enumerate(A):
            if integer != i + 1:
                return i + 1
        return len(A) + 1


if __name__ == "__main__":
    tests = [
        [1, 2, 0],
        [3, 4, -1, 1],
        [7, 8, 9, 11, 12],
        [1, 1],
        [2],
        [1, 2, 3, 4, 5],
        [2, 3, 4, 5, 6],
        [1, 1, 0, -1, -2, 2, 2, 3, 4],
        [1],
        [10, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    ]

    sink = 0

    iterations = 1
    for iter in range(iterations):
        checksum = 0
        sol = Solution()
        for t in tests:
            v = list(t)
            checksum += sol.firstMissingPositive(v)
        sink += checksum
    print(sink)