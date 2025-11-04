# Time:  O(logn)
# Space: O(logn)

class Solution(object):
    def atMostNGivenDigitSet(self, D, N):
        """
        :type D: List[str]
        :type N: int
        :rtype: int
        """
        str_N = str(N)
        set_D = set(D)
        result = sum(len(D)**i for i in xrange(1, len(str_N)))
        i = 0
        while i < len(str_N):
            result += sum(c < str_N[i] for c in D) * (len(D)**(len(str_N)-i-1))
            if str_N[i] not in set_D:
                break
            i += 1
        return result + int(i == len(str_N))


if __name__ == "__main__":
    from time import time
    import sys

    # Define 10 diverse test inputs
    tests = [
        (['1', '3', '5', '7'], 100),               # typical example
        (['1', '4', '9'], 1000000000),             # large N, small digit set
        (['7'], 8),                                 # single digit set
        (['2', '3', '5', '7'], 29),                 # primes as digits
        (['1', '2', '3', '4', '5', '6', '7', '8', '9'], 999999999),  # many digits, large N
        (['0', '1', '2'], 100),                     # includes zero
        (['8', '9'], 1000),                         # two high digits
        (['1'], 111111),                            # repetitive N with single digit
        (['3', '4', '8'], 3456),                    # mixed mid-range
        ([], 12345),                                # empty digit set (edge case)
    ]

    sol = Solution()

    checksum = 0

    start = time()
    iterations = 1000
    for _ in xrange(iterations):
        for D, N in tests:
            checksum += sol.atMostNGivenDigitSet(D, N)
    end = time()

    checksum_sink = checksum  # to avoid optimization

    elapsed_ns = int(round((end - start) * 1e9))

    sys.stdout.write("Checksum: %s\n" % (checksum_sink,))
    sys.stdout.write("Elapsed time (ns): %s\n" % (elapsed_ns,))