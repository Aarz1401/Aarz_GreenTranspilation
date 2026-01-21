
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

if __name__ == "__main__":
    import time

    class TestCase(object):
        def __init__(self, nums, maxC):
            self.nums = nums
            self.maxC = maxC

    tests = []

    tests.append(TestCase([], 0))
    tests.append(TestCase([7], 0))
    tests.append(TestCase([1], 0))

    t4 = [4] * 10
    tests.append(TestCase(t4, 2))

    tests.append(TestCase([5, 7, 11, 13, 17, 19, 23, 29, 31, 37], 0))

    tests.append(TestCase([2, 4, 6, 9, 3, 15, 10, 5, 25, 50, 75], 1))

    t7 = [1] * 500
    tests.append(TestCase(t7, 0))

    t8 = []
    pattern8 = [6, 10, 15, 21, 14, 22]
    for rep in xrange(50):
        for v in pattern8:
            t8.append(v)
    tests.append(TestCase(t8, 50))

    tests.append(TestCase([0, 0, 4, 0, 8, 0, 16, 0, 3, 0, 9, 0], 3))

    tests.append(TestCase([-4, -8, 12, -16, 24, -36, 48, -60, 2147483646, -2147483646, 1000000000, -1000000000], 5))

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        for tc in tests:
            if len(tc.nums) == 0:
                res = 0
            else:
                res = sol.minStable(tc.nums, tc.maxC)
            checksum += res
    end = time.time()

    elapsed_ns = int(round((end - start) * 1000000000.0))
    print 'Checksum: %d' % checksum
    print 'Elapsed time (ns): %d' % elapsed_ns
