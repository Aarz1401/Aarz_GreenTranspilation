
# Time:  O(rlogr + qlogr), r = max(nums)
# Space: O(r)

import collections
import bisect


# number theory, freq table, prefix sum, binary search
class Solution(object):
    def gcdValues(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        cnt1 = collections.Counter(nums)
        cnt2 = [0]*(max(nums)+1)
        for g in reversed(xrange(1, len(cnt2))):
            c = sum(cnt1[ng] for ng in xrange(g, len(cnt2), g))
            cnt2[g] = c*(c-1)//2-sum(cnt2[ng] for ng in xrange(g+g, len(cnt2), g))
        prefix = [0]*(len(cnt2)+1)
        for i in xrange(len(prefix)-1):
            prefix[i+1] = prefix[i]+cnt2[i]
        return [bisect.bisect_right(prefix, q)-1 for q in queries]

if __name__ == "__main__":
    import time

    # Test 1: small array
    nums1 = [1, 2, 3, 4, 5]
    q1 = [0, 1, 3, 6, 9, 10]

    # Test 2: moderately sized with varied values
    nums2 = []
    for i in xrange(1, 61):
        nums2.append((i * 7) % 101 + 1)
    q2 = [0, 1, 10, 100, 500, 1000]

    # Test 3: all same numbers
    nums3 = [7] * 40
    q3 = [0L, 100L, 779L, 780L, 10000L]

    # Test 4: primes
    nums4 = [
        2,3,5,7,11,13,17,19,23,29,
        31,37,41,43,47,53,59,61,67,71,
        73,79,83,89,97,101,103,107,109,113,
        127,131,137,139,149,151,157,163,167,173,
        179,181,191,193,197,199,211,223,227,229
    ]
    q4 = [0, 1, 100, 1769]

    # Test 5: multiples of 6
    nums5 = []
    for i in xrange(1, 101):
        nums5.append(i * 6)
    q5 = [0L, 10L, 1000L, 3000L, 4950L]

    # Test 6: empty nums
    nums6 = []
    q6 = [0, 1, 2, 3, 4, 5]

    # Test 7: single element
    nums7 = [42]
    q7 = [0L, 1L, 2L, 3L, 4L, 5L, 100L]

    # Test 8: high values with moderate r
    nums8 = [10000, 9999, 9998, 9997, 9996, 9995, 5000, 2500, 1250]
    q8 = [0, 1, 2, 3, 4, 5, 10, 20, 30]

    # Test 9: 1..200
    nums9 = []
    for i in xrange(1, 201):
        nums9.append(i)
    q9 = [0L, 50L, 1000L, 10000L, 19900L]

    # Test 10: patterned 300 numbers with r up to 5000
    nums10 = []
    for i in xrange(1, 301):
        nums10.append((i * 37) % 5000 + 1)
    q10 = [0, 10, 100, 1000, 2000, 40000]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        r1 = sol.gcdValues(nums1, q1)
        for v in r1:
            checksum += v

        r2 = sol.gcdValues(nums2, q2)
        for v in r2:
            checksum += v

        r3 = sol.gcdValues(nums3, q3)
        for v in r3:
            checksum += v

        r4 = sol.gcdValues(nums4, q4)
        for v in r4:
            checksum += v

        r5 = sol.gcdValues(nums5, q5)
        for v in r5:
            checksum += v

        try:
            r6 = sol.gcdValues(nums6, q6)
        except ValueError:
            r6 = [0]*len(q6)
        for v in r6:
            checksum += v

        r7 = sol.gcdValues(nums7, q7)
        for v in r7:
            checksum += v

        r8 = sol.gcdValues(nums8, q8)
        for v in r8:
            checksum += v

        r9 = sol.gcdValues(nums9, q9)
        for v in r9:
            checksum += v

        r10 = sol.gcdValues(nums10, q10)
        for v in r10:
            checksum += v

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000))

    print "Checksum: " + str(checksum)
    print "Elapsed time (microseconds): " + str(elapsed_us)
