# Time:  O(qlogr)
# Space: O(1)

# greedy
class Solution(object):
    def minOperations(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: int
        """
        result = 0
        for l, r in queries:
            total = 0
            base = i = 1
            while base <= r:
                nl, nr = max(l, base), min(r, 4*base-1)
                if nl <= nr:
                    total += i*(nr-nl+1)
                i += 1
                base *= 4
            result += (total+1)//2
        return result

if __name__ == "__main__":
    import time

    INT_MAX = 2147483647

    tests = []

    # 1) Minimal interval
    tests.append([[1, 1]])

    # 2) Small intervals spanning first group and boundary
    tests.append([[1, 3], [4, 4]])

    # 3) Interval spanning across 1..3 and 4..7
    tests.append([[2, 7]])

    # 4) Singletons at powers of two within different 4^k buckets
    tests.append([[4, 4], [8, 8], [16, 16]])

    # 5) Large continuous interval
    tests.append([[1, 1000000]])

    # 6) Two large separated intervals
    tests.append([[1000000, 2000000], [3000000, 4000000]])

    # 7) Large mid-range interval
    tests.append([[123456789, 223456789]])

    # 8) Interval near INT_MAX
    tests.append([[INT_MAX - 1000, INT_MAX]])

    # 9) Many small mixed intervals including l=0
    t9 = []
    t9.append([0, 50])
    for i in xrange(1, 51):
        l = i * 3
        r = l + (i % 5)
        t9.append([l, r])
    tests.append(t9)

    # 10) Programmatically generated diverse intervals
    t10 = []
    base = 25000000
    for i in xrange(1, 301):
        l = base + ((i * 12345) % 1000000)
        length = 50 + ((i * 37) % 5000)
        r64 = l + length
        r = INT_MAX if r64 > INT_MAX else r64
        t10.append([l, r])
    tests.append(t10)

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    MASK64 = (1 << 64) - 1

    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            res = sol.minOperations(tests[i])
            if not isinstance(res, (int, long)):
                res = int(res)
            checksum = (checksum ^ (res + i + iter)) & MASK64
            checksum = ((checksum << 1) | (checksum >> 63)) & MASK64

    end = time.time()

    elapsed_us = int((end - start) * 1000000)

    # Convert checksum to signed 64-bit for printing like C++ long long
    if checksum >= (1 << 63):
        checksum_print = checksum - (1 << 64)
    else:
        checksum_print = checksum

    print "Checksum: %d" % checksum_print
    print "Elapsed time (microseconds): %d" % elapsed_us