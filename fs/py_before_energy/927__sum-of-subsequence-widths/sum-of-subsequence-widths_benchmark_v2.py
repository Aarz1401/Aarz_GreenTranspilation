
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
    tests = [
        [1],
        [1, 2],
        [5, 5],
        [2, 2, 2, 2, 2],
        [4, 1, 3, 2],
        [1000000000, 1, 1000000000],
        [1000000000, 999999999, 123456789, 987654321],
        [7, 7, 3, 1, 9, 9, 5],
        [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],
        [42, 42, 42, 1, 2, 3, 100, 1000000000, 999999999, 12345, 67890]
    ]

    sol = Solution()
    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            v = list(t)
            res = sol.sumSubseqWidths(v)
            #r = (checksum + res) % 1000000007
        #sink = checksum
    # print sink
