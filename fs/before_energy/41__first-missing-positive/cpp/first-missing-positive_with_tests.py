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
    import time

    # Prepare 10 diverse test inputs
    tests = []
    tests.append([])                                 # empty
    tests.append([1, 2, 0])                          # contains zero, missing 3
    tests.append([3, 4, -1, 1])                      # negatives and positives, missing 2
    tests.append([7, 8, 9, 11, 12])                  # all > n, missing 1
    tests.append([1, 1])                             # duplicates of 1, missing 2
    tests.append([2, 2])                             # duplicates of 2, missing 1
    tests.append([1, 2, 3, 4, 5])                    # already 1..n, missing 6
    tests.append([2])                                # single element not 1, missing 1
    tests.append([1, 1, 0, -1, 2, 2, 4])             # mixed, missing 3

    # Large mixed test with one missing in range
    largeTest = []
    for i in xrange(1, 20001):
        if i != 5432:
            largeTest.append(i)                      # missing 5432
    largeTest.append(-1)
    largeTest.append(0)
    largeTest.append(1000000)
    largeTest.append(2)                              # duplicate
    tests.append(largeTest)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for ti in xrange(len(tests)):
            arr = list(tests[ti])  # copy since algorithm mutates
            result = sol.firstMissingPositive(arr)
            checksum += result

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us