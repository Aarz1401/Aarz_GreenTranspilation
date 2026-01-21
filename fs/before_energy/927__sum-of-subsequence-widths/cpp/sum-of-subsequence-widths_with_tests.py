# Time:  O(n)
# Spce:  O(1)

class Solution(object):
    def sumSubseqWidths(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        M = 10**9+7
        # sum(A[i] * (2^i - 2^(len(A)-1-i))), i = 0..len(A)-1
        # <=>
        # sum(((A[i] - A[len(A)-1-i]) * 2^i), i = 0..len(A)-1
        result, c = 0, 1
        A.sort()
        for i in xrange(len(A)):
            result = (result + (A[i]-A[len(A)-1-i])*c % M) % M
            c = (c<<1) % M
        return result


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs
    inputs = []

    # 1) Empty
    inputs.append([])

    # 2) Single element
    inputs.append([42])

    # 3) Two elements
    inputs.append([1, 2])

    # 4) All equal values
    inputs.append([7] * 100)

    # 5) Increasing sequence 0..999
    inputs.append(list(range(1000)))

    # 6) Decreasing sequence 1000..1
    inputs.append(list(range(1000, 0, -1)))

    # 7) Mixed negatives and positives
    inputs.append([-1000, -1, 0, 1, 1000, 500, -500, 123456, -654321])

    # 8) Extreme int values
    INT_MAX = 2147483647
    INT_MIN = -2147483648
    inputs.append([INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1, 0, -12345, 12345])

    # 9) Pseudo-random 2000 elements (deterministic)
    v = []
    seed = 123456789
    for i in xrange(2000):
        seed = (seed * 1664525 + 1013904223) & 0xFFFFFFFF
        val = int(seed % 2000000001) - 1000000000  # [-1e9, 1e9]
        v.append(val)
    inputs.append(v)

    # 10) Repeating pattern
    pattern = [1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0, 0, -1, -1, 100, -100]
    inputs.append(pattern * 200)

    sol = Solution()
    checksum = 0
    mask64 = (1 << 64) - 1

    start = time.time()

    iterations = 1000
    for iter_idx in xrange(iterations):
        for i in xrange(len(inputs)):
            A = list(inputs[i])  # copy to preserve original unsorted inputs
            res = sol.sumSubseqWidths(A)
            mix = ((res & mask64) + len(A) + iter_idx) & mask64
            checksum = ((checksum * 1315423911) ^ mix) & mask64

    end = time.time()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns