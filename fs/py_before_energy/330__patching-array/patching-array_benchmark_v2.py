# Time:  O(s + logn), s is the number of elements in the array
# Space: O(1)

class Solution(object):
    def minPatches(self, nums, n):
        """
        :type nums: List[int]
        :type n: int
        :rtype: int
        """
        result = reachable = 0
        for x in nums:
            if x > n:
                break
            while not reachable >= x-1:
                result += 1
                reachable += reachable+1
            reachable += x
        while not reachable >= n:
            result += 1
            reachable += reachable+1
        return result


# Time:  O(s + logn), s is the number of elements in the array
# Space: O(1)
class Solution2(object):
    def minPatches(self, nums, n):
        """
        :type nums: List[int]
        :type n: int
        :rtype: int
        """
        result = reachable = 0
        for x in nums:
            while not reachable >= x-1:
                result += 1
                reachable += reachable+1
                if reachable >= n:
                    return result
            reachable += x
            if reachable >= n:
                return result
        while not reachable >= n:
            result += 1
            reachable += reachable+1
        return result


# Time:  O(s + logn), s is the number of elements in the array
# Space: O(1)
class Solution3(object):
    def minPatches(self, nums, n):
        """
        :type nums: List[int]
        :type n: int
        :rtype: int
        """
        patch, miss, i = 0, 1, 0
        while miss <= n:
            if i < len(nums) and nums[i] <= miss:
                miss += nums[i]
                i += 1
            else:
                miss += miss
                patch += 1

        return patch


if __name__ == "__main__":
    tests = [
        {'nums': [1, 3], 'n': 6},
        {'nums': [1, 5, 10], 'n': 20},
        {'nums': [1, 2, 2], 'n': 5},
        {'nums': [2], 'n': 1},
        {'nums': [2, 3, 4, 7], 'n': 15},
        {'nums': [1, 1, 1, 1], 'n': 8},
        {'nums': [5, 10, 25], 'n': 50},
        {'nums': [1, 4, 7, 13, 28], 'n': 100},
        {'nums': [1, 2, 31, 33], 'n': 2147483647},
        {'nums': [1, 2, 4, 8, 16, 32], 'n': 63}
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        r = 0
        r = sol.minPatches(tests[0]['nums'], tests[0]['n'])
        r = sol.minPatches(tests[1]['nums'], tests[1]['n'])
        r = sol.minPatches(tests[2]['nums'], tests[2]['n'])
        r = sol.minPatches(tests[3]['nums'], tests[3]['n'])
        r = sol.minPatches(tests[4]['nums'], tests[4]['n'])
        r = sol.minPatches(tests[5]['nums'], tests[5]['n'])
        r = sol.minPatches(tests[6]['nums'], tests[6]['n'])
        r = sol.minPatches(tests[7]['nums'], tests[7]['n'])
        r = sol.minPatches(tests[8]['nums'], tests[8]['n'])
        r = sol.minPatches(tests[9]['nums'], tests[9]['n'])
        #sink = checksum

    # print sink