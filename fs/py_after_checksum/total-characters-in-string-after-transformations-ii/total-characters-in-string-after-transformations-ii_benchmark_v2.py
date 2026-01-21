
# Time:  O(n + 26^3 * logt)
# Space: O(26^2)

import itertools


# matrix fast exponentiation
class Solution(object):
    def lengthAfterTransformations(self, s, t, nums):
        """
        :type s: str
        :type t: int
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9+7
        def matrix_mult(A, B):
            ZB = zip(*B)
            return [[sum(a*b % MOD for a, b in itertools.izip(row, col)) % MOD for col in ZB] for row in A]
 
        def matrix_expo(A, K):
            result = [[int(i == j) for j in xrange(len(A))] for i in xrange(len(A))]
            while K:
                if K % 2:
                    result = matrix_mult(result, A)
                A = matrix_mult(A, A)
                K /= 2
            return result

        cnt = [0]*26
        for x in s:
            cnt[ord(x)-ord('a')] += 1
        matrix = [[0]*26 for _ in xrange(26)]
        for i in xrange(len(nums)):
            for j in xrange(1, nums[i]+1):
                matrix[i][(i+j)%26] = 1
        matrix_pow_t = matrix_expo(matrix, t)
        return reduce(lambda accu, x: (accu+x)%MOD, matrix_mult([cnt], matrix_pow_t)[0], 0)


if __name__ == "__main__":
    class TestCase(object):
        def __init__(self, s, t, nums):
            self.s = s
            self.t = t
            self.nums = nums

    sol = Solution()
    tests = []

    # Test 1
    nums1 = [0] * 26
    tests.append(TestCase("a", 0, nums1))

    # Test 2
    nums2 = [1] * 26
    tests.append(TestCase("abc", 1, nums2))

    # Test 3
    nums3 = [0] * 26
    nums3[25] = 2  # 'z'
    tests.append(TestCase("zzz", 2, nums3))

    # Test 4
    nums4 = [0] * 26
    for i in xrange(26):
        nums4[i] = i % 3
    tests.append(TestCase("leetcode", 3, nums4))

    # Test 5
    nums5 = [0] * 26
    for i in xrange(26):
        nums5[i] = i % 5
    tests.append(TestCase("abcdefghijklmnopqrstuvwxyz", 5, nums5))

    # Test 6
    nums6 = [0] * 26
    nums6[0] = 3  # 'a'
    tests.append(TestCase("aaaaaaaaaaaaaaaaaaaa", 10, nums6))

    # Test 7
    nums7 = [2] * 26
    tests.append(TestCase("mixandmatch", 26, nums7))

    # Test 8
    nums8 = [0] * 26
    for i in xrange(26):
        nums8[i] = 2 if (i % 2 == 0) else 1
    tests.append(TestCase("bcdxyzab", 12, nums8))

    # Test 9
    nums9 = [0] * 26
    nums9[16] = 4  # 'q'
    nums9[22] = 3  # 'w'
    nums9[19] = 2  # 't'
    tests.append(TestCase("qwerty", 32, nums9))

    # Test 10
    nums10 = [3,0,1,2,0,1,3,0,2,1,0,3,1,0,2,1,0,2,3,0,1,2,0,1,2,3]
    tests.append(TestCase("thequickbrownfox", 20, nums10))

    sink = 0
    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for tc in tests:
            checksum += sol.lengthAfterTransformations(tc.s, tc.t, tc.nums)
        sink += checksum
    print(sink)
