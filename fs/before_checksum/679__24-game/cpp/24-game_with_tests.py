# Time:  O(n^3 * 4^n) = O(1), n = 4
# Space: O(n^2) = O(1)

from operator import add, sub, mul, truediv
from fractions import Fraction


class Solution(object):
    def judgePoint24(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        if len(nums) == 1:
            return abs(nums[0]-24) < 1e-6
        ops = [add, sub, mul, truediv]
        for i in xrange(len(nums)):
            for j in xrange(len(nums)):
                if i == j:
                    continue
                next_nums = [nums[k] for k in xrange(len(nums)) if i != k != j]
                for op in ops:
                    if ((op is add or op is mul) and j > i) or \
                       (op == truediv and nums[j] == 0):
                        continue
                    next_nums.append(op(nums[i], nums[j]))
                    if self.judgePoint24(next_nums):
                        return True
                    next_nums.pop()
        return False


# Time:  O(n^3 * 4^n) = O(1), n = 4
# Space: O(n^2) = O(1)
class Solution2(object):
    def judgePoint24(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def dfs(nums):
            if len(nums) == 1:
                return nums[0] == 24
            ops = [add, sub, mul, truediv]
            for i in xrange(len(nums)):
                for j in xrange(len(nums)):
                    if i == j:
                        continue
                    next_nums = [nums[k] for k in xrange(len(nums))
                                 if i != k != j]
                    for op in ops:
                        if ((op is add or op is mul) and j > i) or \
                           (op == truediv and nums[j] == 0):
                            continue
                        next_nums.append(op(nums[i], nums[j]))
                        if dfs(next_nums):
                            return True
                        next_nums.pop()
            return False

        return dfs(map(Fraction, nums))


if __name__ == "__main__":
    # Define 10 diverse test inputs
    tests = [
        [4, 1, 8, 7],   # true
        [1, 2, 1, 2],   # false
        [3, 3, 8, 8],   # true
        [1, 3, 4, 6],   # true
        [6, 6, 6, 6],   # true
        [0, 0, 0, 24],  # true
        [0, 0, 0, 1],   # false
        [2, 3, 4, 4],   # true
        [6, 6, 2, 2],   # true
        [1, 1, 1, 1]    # false
    ]

    sol = Solution()
    checksum = 0

    from timeit import default_timer as timer
    start = timer()

    iterations = 1
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            nums = tests[i]
            res = sol.judgePoint24(nums)
            checksum += (i + 1) if res else -(i + 1)

    end = timer()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us