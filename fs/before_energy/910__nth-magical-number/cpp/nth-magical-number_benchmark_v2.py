# Time:  O(logn)
# Space: O(1)

class Solution(object):
    def nthMagicalNumber(self, N, A, B):
        """
        :type N: int
        :type A: int
        :type B: int
        :rtype: int
        """
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a

        def check(A, B, N, lcm, target):
            return target//A + target//B - target//lcm >= N

        lcm = A*B // gcd(A, B)
        left, right = min(A, B), max(A, B)*N
        while left <= right:
            mid = left + (right-left)//2
            if check(A, B, N, lcm, mid):
                right = mid-1
            else:
                left = mid+1
        return left % (10**9 + 7)

if __name__ == "__main__":
    sol = Solution()
    tests = [
        [1, 2, 3],
        [5, 2, 4],
        [1000000000, 2, 3],
        [999999937, 40000, 39999],
        [123456789, 7, 11],
        [987654321, 6, 9],
        [500000000, 40000, 40000],
        [42, 999, 1000],
        [10, 7, 13],
        [214748364, 32768, 16384]
    ]

    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            r = sol.nthMagicalNumber(t[0], t[1], t[2])
        #sink = checksum