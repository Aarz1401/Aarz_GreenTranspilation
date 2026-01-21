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
    tests = [
        (["1","3","5","7"], 100),
        (["1","4","9"], 1000000000),
        (["7"], 7),
        (["1","2","3","4","5","6","7","8","9"], 999999999),
        (["2","5","8"], 256),
        (["3","4"], 30),
        (["9"], 1000),
        (["2","3","5","7"], 50000000),
        (["1","2"], 1),
        (["6","7","8","9"], 68)
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for i in xrange(len(tests)):
            D, N = tests[i]
            r = sol.atMostNGivenDigitSet(D, N)
        #sink = checksum

    # print sink