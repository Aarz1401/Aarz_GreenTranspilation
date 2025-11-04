# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(nlogn * logr)
# Space: O(nlogn)

# number theory, binary search, rmq, sparse table, greedy
class Solution(object):
    def minStable(self, nums, maxC):
        """
        :type nums: List[int]
        :type maxC: int
        :rtype: int
        """
        if not nums:
            return 0
        def gcd(a, b):
            while b:
                a, b = b, a%b
            return a

        def binary_search_right(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if not check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return right

        # RMQ - Sparse Table
        # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
        # Time:  ctor:  O(NlogN) * O(fn)
        #        query: O(fn)
        # Space: O(NlogN)
        class SparseTable(object):
            def __init__(self, arr, fn):
                self.fn = fn
                self.bit_length = [0]
                n = len(arr)
                k = n.bit_length()-1  # log2_floor(n)
                for i in xrange(k+1):
                    self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
                self.st = [[0]*n for _ in xrange(k+1)]
                self.st[0] = arr[:]
                for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                    for j in xrange((n-(1<<i))+1):
                        self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
        
            def query(self, L, R):  # Time: O(fn)
                i = self.bit_length[R-L+1]-1  # log2_floor(R-L+1)
                return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])

        def check(l):
            cnt = 0
            i = 0
            while i+l-1 < len(nums):
                if rmq.query(i, i+l-1) >= 2:
                    cnt += 1
                    i += l
                else:
                    i += 1
            return cnt > maxC

        rmq = SparseTable(nums, gcd)
        return binary_search_right(1, len(nums), check)

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    arr9 = []
    for i in xrange(1, 51):
        if i % 5 == 0:
            arr9.append(0)
        elif i % 2 == 0:
            arr9.append(i * 2)
        elif i % 3 == 0:
            arr9.append(i * 3)
        else:
            arr9.append(i * 7 + 1)

    test_cases = [
        ([], 0),  # 0) Empty array
        ([2], 0),  # 1) Single element
        ([2, 4, 6, 8, 10, 12, 14, 16], 2),  # 2) All evens (high gcd)
        ([3, 5, 7, 11, 13, 17, 19], 0),  # 3) All odd primes (mostly gcd 1)
        ([0, 0, 2, 4, 0, 6, 0, 8, 10, 0], 3),  # 4) Mix with zeros
        ([-2, -4, 6, -8, 10, -12], 1),  # 5) Includes negatives
        ([14, 25, 9, 35, 22, 49, 18, 55, 26], 1),  # 6) Mixed values with likely gcd 1
        ([1, 1, 1, 1, 1, 1, 1], 5),  # 7) All ones (gcd always 1)
        ([12, 18, 24, 30, 36, 42, 48, 54], 5),  # 8) Composite numbers with many common factors
        (arr9, 7),  # 9) Larger mixed array programmatically generated
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.minStable(*test)
        else:
            sol.minStable(test)

    # Benchmark
    results = []
    start_time = time.time()

    for iter_idx in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                nums, maxC = test
                result = sol.minStable(nums, maxC + (iter_idx & 1))
            else:
                result = sol.minStable(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
