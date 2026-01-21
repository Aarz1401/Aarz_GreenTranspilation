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
    import time

    def main():
        sol = Solution()

        tests = [
            (1, 2, 3),
            (5, 2, 4),
            (10, 5, 5),
            (100, 3, 7),
            (1000, 8, 12),
            (100000, 1, 1000000000),
            (1000000, 999999937, 999999929),
            (200000000, 40000, 39999),
            (1000000000, 2147483647, 2147483646),
            (123456789, 12345, 67890),
        ]

        checksum = 0
        start = time.time()
        iterations = 1000
        for _ in xrange(iterations):
            for N, A, B in tests:
                res = sol.nthMagicalNumber(N, A, B)
                checksum += res
        end = time.time()

        elapsed_ms = (end - start) * 1000.0

        print("Checksum: %d" % checksum)
        print("Elapsed time (ms): %f" % elapsed_ms)

    main()