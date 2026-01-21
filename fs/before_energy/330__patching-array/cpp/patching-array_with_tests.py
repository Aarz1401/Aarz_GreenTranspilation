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
    import time

    # Define 10 diverse test inputs (sorted positive integer arrays as per problem constraints)
    nums_list = [
        [],                         # empty array
        [1],                        # single element
        [1, 3],                     # small gap
        [1, 2, 2],                  # covers without patches
        [1, 5, 10],                 # requires multiple patches
        [2, 3, 4],                  # missing initial 1
        [1, 2, 31, 33],             # large n stress
        [1, 4, 10, 25, 50],         # scattered coverage
        [1, 2, 3, 8, 9, 13],        # mixed small and medium
        [5, 10, 25]                 # missing several small numbers
    ]

    n_list = [
        7,                          # with empty array
        1,                          # minimal n
        6,                          # small n
        5,                          # small n, no patches
        20,                         # moderate n
        13,                         # moderate n, needs 1
        2147483647,                 # INT_MAX
        100,                        # moderate n
        20,                         # moderate n
        1000                        # large n with few nums
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(nums_list)):
            res = sol.minPatches(nums_list[i], n_list[i])
            checksum += (res ^ int(i) ^ iter)
    end = time.time()

    elapsed_us = int((end - start) * 1000000.0)
    print 'Checksum: {}'.format(checksum)
    print 'Elapsed time (microseconds): {}'.format(elapsed_us)