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
    import time

    # Prepare 10 diverse test inputs
    tests = []

    # 1) Empty arrays
    tests.append(([], []))

    # 2) Single element equal arrays
    tests.append(([1], [1]))

    # 3) Classic example that needs 1 swap
    tests.append(([1, 3, 5, 4], [1, 2, 3, 7]))

    # 4) Already strictly increasing sequences
    tests.append(([1, 2, 3, 4], [2, 3, 4, 5]))

    # 5) Mixed requiring swaps
    tests.append(([0, 3, 5, 8, 9], [2, 1, 4, 6, 9]))

    # 6) Negative numbers
    tests.append(([-5, -3, -1, 2, 4], [-6, -4, 0, 3, 5]))

    # 7) Interleaved increasing
    tests.append(([1, 4, 6, 8, 10], [2, 3, 5, 7, 9]))

    # 8) Zig-zag pattern
    tests.append(([1, 5, 3, 9, 10, 13, 15], [2, 3, 7, 4, 12, 14, 16]))

    # 9) Large easy case (1000 elements, solvable without swaps)
    A = [0] * 1000
    B = [0] * 1000
    for i in xrange(1000):
        A[i] = i * 3 + (2 if i % 10 == 0 else 1)
        B[i] = i * 3 + (1 if i % 10 == 0 else 2)
    tests.append((A, B))

    # 10) Medium-sized with periodic perturbations
    A = [0] * 120
    B = [0] * 120
    for i in xrange(120):
        A[i] = i * 2 + (1 if i % 3 == 0 else 0)
        B[i] = i * 2 + 1 - (1 if i % 4 == 0 else 0)
    tests.append((A, B))

    solver = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for A, B in tests:
            checksum += solver.minSwap(A, B)
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms