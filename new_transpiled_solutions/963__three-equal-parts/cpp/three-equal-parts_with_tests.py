# Time:  O(n)
# Space: O(1)

class Solution(object):
    def threeEqualParts(self, A):
        """
        :type A: List[int]
        :rtype: List[int]
        """
        total = sum(A)
        if total % 3 != 0:
            return [-1, -1]
        if total == 0:
            return [0, len(A)-1]

        count = total//3
        nums = [0]*3
        c = 0
        for i in xrange(len(A)):
            if A[i] == 1:
                if c % count == 0:
                    nums[c//count] = i
                c += 1

        while nums[2] != len(A):
            if not A[nums[0]] == A[nums[1]] == A[nums[2]]:
                return [-1, -1]
            nums[0] += 1
            nums[1] += 1
            nums[2] += 1
        return [nums[0]-1, nums[1]]

if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    tests = []

    # 1) Empty array
    tests.append([])

    # 2) Single zero
    tests.append([0])

    # 3) Single one (not divisible by 3)
    tests.append([1])

    # 4) All zeros
    tests.append([0, 0, 0, 0, 0])

    # 5) Not divisible by 3
    tests.append([1, 1, 0])

    # 6) Valid classic example
    tests.append([1, 0, 1, 0, 1])

    # 7) Valid "100" repeated
    tests.append([1, 0, 0, 1, 0, 0, 1])

    # 8) Valid "110" pattern repeated
    tests.append([1, 1, 0, 1, 1, 0, 1, 1, 0])

    # 9) Likely invalid due to trailing zeros mismatch
    tests.append([1, 0, 1, 0, 1, 0, 0])

    # 10) Large valid with long trailing zeros alignment
    big = []
    big.extend([0] * 500)
    big.append(1)
    big.extend([0] * 500)
    big.append(1)
    big.extend([0] * 500)
    big.append(1)
    big.extend([0] * 500)
    tests.append(big)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            res = sol.threeEqualParts(tests[i])
            checksum += ((long(res[0]) << 32) ^ (long(res[1]) & 0xffffffff)) + long(i) + iter

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us