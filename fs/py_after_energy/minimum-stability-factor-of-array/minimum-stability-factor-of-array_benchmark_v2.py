
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
    tests = []

    # Test 1: all 2's
    a = [2] * 60
    tests.append({'nums': a, 'maxC': 5})

    # Test 2: all 1's
    a = [1] * 20
    tests.append({'nums': a, 'maxC': 0})

    # Test 3: primes
    a = [2,3,5,7,11,13,17,19,23,29,31,37]
    tests.append({'nums': a, 'maxC': 8})

    # Test 4: repeating mixed pattern
    base = [6, 10, 15, 21, 14, 22]
    a = []
    for i in range(6):
        a.extend(base)
    tests.append({'nums': a, 'maxC': 4})

    # Test 5: powers of two
    a = []
    for i in range(1, 17):
        a.append(1 << i)
    tests.append({'nums': a, 'maxC': 1})

    # Test 6: mixed composites and multiples
    a = [12,18,6,9,3,27,30,15,21,14,7,28,35,5,10,20,25,50,75,100]
    tests.append({'nums': a, 'maxC': 3})

    # Test 7: single element
    a = [2]
    tests.append({'nums': a, 'maxC': 0})

    # Test 8: alternating 2 and 3, length 200
    a = [0] * 200
    for i in range(200):
        a[i] = 2 if (i % 2 == 0) else 3
    tests.append({'nums': a, 'maxC': 80})

    # Test 9: diverse composites
    a = [30,42,70,105,210,330,66,198,462,924,231,77,143,187,221]
    tests.append({'nums': a, 'maxC': 2})

    # Test 10: alternating 4 and 6, length 256
    a = [0] * 256
    for i in range(256):
        a[i] = 4 if (i % 2 == 0) else 6
    tests.append({'nums': a, 'maxC': 100})

    sink = 0
    iterations = 1000
    for iter in range(iterations):
        checksum = 0
        sol = Solution()
        for i in range(10):
            nums = list(tests[i]['nums'])
            res = sol.minStable(nums, tests[i]['maxC'])
            #checksum += res
        #sink = checksum
    # print sink
