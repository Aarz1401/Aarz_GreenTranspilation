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
    import time

    # 10 diverse test inputs
    tests = [
        [1,2,3,4,5,6,7,8],                         # typical, expected true
        [3,1],                                      # small, expected false
        [1,2,3,4,5,6,7,8,9,10],                     # larger, expected true (e.g., {1,10})
        [0,0,0,0,0,0,0,0],                          # all zeros, true
        [1,1,1,1,1,1,1,1,1,1],                      # all equal, true
        [2,4,6,8,10,12],                            # evens, true (e.g., {2,12})
        [1,2,3,5],                                  # early impossible, false
        [18,0,16,2],                                # true (e.g., {16,2})
        [1],                                        # single element, false
        [9,1,2,3,10,12,7,8,4,6,5,11]                # mixed 1..12 shuffled, true (e.g., {5,8})
    ]

    sol = Solution()
    checksum = 0L

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        for t in xrange(len(tests)):
            res = sol.splitArraySameAverage(tests[t])
            if res:
                checksum += long((t + 1) * (iter + 1))
    end = time.time()

    elapsed_ns = long(round((end - start) * 1e9))
    print "Checksum:", checksum
    print "Elapsed time (ns):", elapsed_ns