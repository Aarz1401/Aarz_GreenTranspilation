
# Time:  O(n)
# Space: O(n)

import collections


# freq table, prefix sum, combinatorics
class Solution(object):
    def subsequencesWithMiddleMode(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def nC2(x):
            return x*(x-1)//2

        MOD = 10**9+7
        result = 0
        left = collections.defaultdict(int)
        right = collections.defaultdict(int)
        for x in nums:
            right[x] += 1
        left_x_sq = 0  # sum(left[x]^2 for x != v)
        right_x_sq = sum(v**2 for v in right.itervalues())  # sum(right[x]^2 for x != v)
        left_x_right_x = 0  # sum(left[x]*right[x] for x != v)
        left_x_sq_right_x = 0  # sum(left[x]^2*right[x] for x != v)
        left_x_right_x_sq = 0  # sum(left[x]*right[x]^2 for x != v)
        for i, v in enumerate(nums):
            left_x_sq -= left[v]**2
            right_x_sq -= right[v]**2
            left_x_right_x -= left[v]*right[v]
            left_x_sq_right_x -= left[v]**2*right[v]
            left_x_right_x_sq -= left[v]*right[v]**2
            right[v] -= 1

            l, r = i, len(nums)-(i+1)
            # all possibles
            result += nC2(l)*nC2(r)
            # only mid is a
            result -= nC2(l-left[v])*nC2(r-right[v])
            # bb/a/ac
            # sum((left[x]*(left[x]-1)//2)*right[v]*((r-right[v])-right[x]) for x != v)
            result -= ((left_x_sq-(l-left[v]))*(r-right[v])-(left_x_sq_right_x-left_x_right_x))*right[v]//2
            # ac/a/bb
            # sum(left[v]*((l-left[v])-left[x])*(right[x]*(right[x]-1)//2) for x != v)
            result -= ((right_x_sq-(r-right[v]))*(l-left[v])-(left_x_right_x_sq-left_x_right_x))*left[v]//2
            # ab/a/bc
            # sum(left[v]*left[x]*right[x]*((r-right[v])-right[x]) for x != v)
            result -= left[v]*left_x_right_x*(r-right[v])-left[v]*left_x_right_x_sq
            # bc/a/ab
            # sum(left[x]*((l-left[v])-left[x])*right[v]*right[x] for x != v)
            result -= right[v]*left_x_right_x*(l-left[v])-right[v]*left_x_sq_right_x
            # bb/a/ab
            # sum((left[x]*(left[x]-1)//2)*right[v]*right[x] for x != v)
            result -= right[v]*(left_x_sq_right_x-left_x_right_x)//2
            # ab/a/bb
            # sum((right[x]*(right[x]-1)//2)*left[v]*left[x] for x != v)
            result -= left[v]*(left_x_right_x_sq-left_x_right_x)//2

            left[v] += 1
            left_x_sq += left[v]**2
            right_x_sq += right[v]**2
            left_x_right_x += left[v]*right[v]
            left_x_sq_right_x += left[v]**2*right[v]
            left_x_right_x_sq += left[v]*right[v]**2
        return result % MOD


if __name__ == "__main__":
    import time

    testCases = []

    # 1) Empty array
    tc1 = []
    testCases.append(tc1)

    # 2) Single element
    tc2 = [42]
    testCases.append(tc2)

    # 3) Two different elements
    tc3 = [1, 2]
    testCases.append(tc3)

    # 4) All identical elements
    tc4 = [5] * 50
    testCases.append(tc4)

    # 5) Alternating two values
    tc5 = []
    for i in xrange(60):
        tc5.append(2 if (i % 2) else 1)
    testCases.append(tc5)

    # 6) Increasing sequence
    tc6 = []
    for i in xrange(1, 101):
        tc6.append(i)
    testCases.append(tc6)

    # 7) Decreasing sequence
    tc7 = []
    for i in xrange(200, 0, -1):
        tc7.append(i)
    testCases.append(tc7)

    # 8) Pseudo-random with quadratic formula modulo 25 (lots of duplicates)
    tc8 = []
    for i in xrange(200):
        val = (i * i + 7 * i + 13) % 25
        tc8.append(int(val))
    testCases.append(tc8)

    # 9) Extremes and small values repeated
    INT_MAX = 2147483647
    INT_MIN = -2147483648
    tc9 = []
    for i in xrange(25):
        tc9.append(INT_MAX)
        tc9.append(INT_MIN)
        tc9.append(0)
        tc9.append(-1)
    testCases.append(tc9)

    # 10) Linear congruential-like sequence modulo 50
    tc10 = []
    for i in xrange(300):
        tc10.append((i * 37 + 23) % 50)
    testCases.append(tc10)

    sol = Solution()

    checksum = 0
    start = time.time()
    iterations = 1000
    mask = (1 << 64) - 1
    GOLDEN = 0x9e3779b97f4a7c15
    for _ in xrange(iterations):
        for i in xrange(len(testCases)):
            res = sol.subsequencesWithMiddleMode(testCases[i])
            res_ull = res & mask
            t = (res_ull + GOLDEN + ((checksum << 6) & mask) + (checksum >> 2)) & mask
            checksum = (checksum ^ t) & mask
    end = time.time()

    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: " + str(checksum)
    print "Elapsed time (microseconds): " + str(elapsed_us)
