# Time:  O(nlogn + nlogw), n = len(nums), w = max(nums)-min(nums)
# Space: O(1)

class Solution(object):
    def smallestDistancePair(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        # Sliding window solution
        def possible(guess, nums, k):
            count, left = 0, 0
            for right, num in enumerate(nums):
                while num-nums[left] > guess:
                    left += 1
                count += right-left
            return count >= k

        nums.sort()
        left, right = 0, nums[-1]-nums[0]+1
        while left < right:
            mid = left + (right-left)/2
            if possible(mid, nums, k):
                right = mid
            else:
                left = mid+1
        return left


if __name__ == "__main__":
    import time

    # Define 10 diverse test cases
    tests = [
        { 'nums': [1, 3, 1], 'k': 1 },                               # duplicates, expect 0
        { 'nums': [1, 6], 'k': 1 },                                  # minimal size
        { 'nums': [5, 5, 5, 5], 'k': 6 },                            # all equal
        { 'nums': [1, 2, 3, 4, 5], 'k': 7 },                         # increasing sequence
        { 'nums': [-10, -5, 0, 5, 10], 'k': 8 },                     # negatives and positives
        { 'nums': [1, 6, 1, 1, 6], 'k': 7 },                         # many duplicates
        { 'nums': [1, 1000000, 500000, 750000, 250000], 'k': 4 },    # wide spread
        { 'nums': [9, 4, 1, 7, 3, 8, 2, 6, 5], 'k': 20 },            # shuffled 1..9
        { 'nums': [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20], 'k': 100 }, # 1..20
        { 'nums': [100,1,50,2,50,3,50,4,50,5,100,1,50,2,50,3,50,4,50,5], 'k': 150 } # repeats
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for it in xrange(iterations):
        for t in tests:
            v = t['nums'][:]  # copy because the algorithm sorts in place
            checksum += sol.smallestDistancePair(v, t['k'])
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us