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
    import time

    # Prepare 10 diverse test inputs
    tests = []
    # 1) Empty
    tests.append([])
    # 2) Single element
    tests.append([0])
    # 3) All zeros
    tests.append([0, 0, 0, 0, 0])
    # 4) Small mixed
    tests.append([1, 0])
    # 5) Example known case with non-zero best rotation
    tests.append([2, 3, 1, 4, 0])
    # 6) Another mixed case
    tests.append([1, 3, 0, 2, 4])
    # 7) Increasing sequence (best rotation likely 0)
    tests.append([0, 1, 2, 3, 4, 5, 6, 7])
    # 8) Deterministic pseudo-random for N=10
    t = [(i * 3 + 1) % 10 for i in xrange(10)]
    tests.append(t)
    # 9) All N-1 values
    tests.append([6, 6, 6, 6, 6, 6, 6])
    # 10) Larger N with deterministic pattern
    N = 1000
    t = [((i * i + 3 * i + 7) % N) for i in xrange(N)]
    tests.append(t)

    solver = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for j in xrange(len(tests)):
            try:
                r = solver.bestRotation(tests[j])
            except Exception:
                r = 0
            checksum += (r ^ j ^ iter)

    end = time.time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time: %d microseconds" % elapsed_us