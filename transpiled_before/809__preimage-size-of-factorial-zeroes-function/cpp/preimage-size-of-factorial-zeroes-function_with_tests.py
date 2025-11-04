# Time:  O((logn)^2)
# Space: O(1)

class Solution(object):
    def preimageSizeFZF(self, K):
        """
        :type K: int
        :rtype: int
        """
        def count_of_factorial_primes(n, p):
            cnt = 0
            while n > 0:
                cnt += n//p
                n //= p
            return cnt

        p = 5
        left, right = 0, p*K
        while left <= right:
            mid = left + (right-left)//2
            if count_of_factorial_primes(mid, p) >= K:
                right = mid-1
            else:
                left = mid+1
        return p if count_of_factorial_primes(left, p) == K else 0


if __name__ == "__main__":
    import time

    # 10 diverse test inputs for K
    test_inputs = [
        0,          # expect 5
        1,          # expect 5
        4,          # expect 5
        5,          # expect 0
        6,          # expect 5
        10,         # expect 5
        24,         # expect 0
        25,         # expect 5
        100,        # commonly 0
        1000000000  # large K for stress
    ]

    sol = Solution()
    checksum = 0L

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(test_inputs)):
            k = test_inputs[i] + (iter & 1)  # toggle between k and k+1
            result = sol.preimageSizeFZF(k)
            checksum += result
            checksum ^= (long(k) << (i % 23))

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us