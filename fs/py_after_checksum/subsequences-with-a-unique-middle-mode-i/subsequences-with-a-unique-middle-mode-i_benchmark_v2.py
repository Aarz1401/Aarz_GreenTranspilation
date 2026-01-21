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
    tests = []
    tests.append([1, 2, 3])
    tests.append([5])
    tests.append([2, 2, 2])
    tests.append([1, 2, 1, 2, 3, 3])
    t5 = []
    for i in range(50):
        t5.append(i % 2)
    tests.append(t5)
    tests.append([0, 0, 0, 1, 1, 2, 2, 2])
    tests.append([5, 3, 5, 2, 5, 2, 3, 4, 5, 6, 7, 8, 5, 9])
    t8 = []
    for i in range(1, 21):
        t8.append(i)
    tests.append(t8)
    t9 = []
    for i in range(1, 11):
        t9.append(i)
        t9.append(i)
    tests.append(t9)
    t10 = []
    for i in range(30):
        t10.append(0)
    for i in range(10):
        t10.append(1)
    for i in range(5):
        t10.append(2)
    tests.append(t10)

    sol = Solution()
    iterations = 1
    sink = 0
    for iter in range(iterations):
        checksum = 0
        for i in range(10):
            checksum += sol.subsequencesWithMiddleMode(tests[i])
        sink += checksum
    print(sink)