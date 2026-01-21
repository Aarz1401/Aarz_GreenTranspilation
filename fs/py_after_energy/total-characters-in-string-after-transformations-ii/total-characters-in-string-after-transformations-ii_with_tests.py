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
    import time

    tests = []

    # Test 1: Empty string, t=0, empty nums
    tests.append({"s": "", "t": 0, "nums": []})

    # Test 2: Single character, minimal nums
    tests.append({"s": "a", "t": 1, "nums": [1]})

    # Test 3: Small string, simple transitions
    tests.append({"s": "abc", "t": 2, "nums": [1, 1, 1]})

    # Test 4: Repeated 'z', sparse matrix across full alphabet
    nums4 = [0] * 26
    for i in xrange(26):
        nums4[i] = i % 3  # 0,1,2 repeating
    tests.append({"s": "z" * 10, "t": 3, "nums": nums4})

    # Test 5: Large counts for 'a', limited transitions
    nums5 = [0] * 26
    nums5[0] = 2  # 'a' -> 'b','c'
    nums5[1] = 1  # 'b' -> 'c'
    tests.append({"s": "a" * 1000, "t": 8, "nums": nums5})

    # Test 6: Partial nums vector smaller than 26
    tests.append({"s": "leetcode", "t": 5, "nums": [2, 0, 1, 2, 1]})

    # Test 7: Full alphabet string, sparse transitions across all rows
    nums7 = [0] * 26
    for i in xrange(26):
        nums7[i] = (i % 3)  # 0,1,2 repeating
    tests.append({"s": "abcdefghijklmnopqrstuvwxyz", "t": 7, "nums": nums7})

    # Test 8: Very sparse transitions, larger t
    nums8 = [0] * 26
    nums8[0] = 1   # 'a' -> 'b'
    nums8[1] = 2   # 'b' -> 'c','d'
    nums8[12] = 1  # 'm' -> 'n'
    nums8[23] = 2  # 'x' -> 'y','z'
    tests.append({"s": "abbaabbaab", "t": 16, "nums": nums8})

    # Test 9: Long string, nums longer than 26 (extra ignored)
    base9 = "thequickbrownfoxjumpsoverthelazydog"
    s9 = ""
    for i in xrange(6):
        s9 += base9  # length ~ 210
    nums9 = [0] * 30
    for i in xrange(30):
        nums9[i] = (i * 7) % 3  # 0,1,2 pattern
    tests.append({"s": s9, "t": 12, "nums": nums9})

    # Test 10: No transitions (empty nums), t=1
    tests.append({"s": "mismatchcases", "t": 1, "nums": []})

    sol = Solution()
    checksum = 0
    MASK = (1 << 64) - 1

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        for tc in tests:
            nums = tc["nums"]
            if len(nums) > 26:
                nums = nums[:26]
            res = sol.lengthAfterTransformations(tc["s"], tc["t"], nums)
            checksum = ((checksum * 1315423911) & MASK) ^ ((res + 0x9e3779b97f4a7c15) & MASK)
    end = time.time()

    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: %d" % (checksum & MASK)
    print "Elapsed time (ns): %d" % elapsed_ns