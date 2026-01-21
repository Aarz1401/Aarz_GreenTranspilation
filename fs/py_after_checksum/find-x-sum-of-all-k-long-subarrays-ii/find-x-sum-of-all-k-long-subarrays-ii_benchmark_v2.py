# Time:  O(nlogn)
# Space: O(n)

from sortedcontainers import SortedList
import collections


# freq table, sorted list, two pointers, sliding window
class Solution(object):
    def findXSum(self, nums, k, x):
        """
        :type nums: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        def update(v, d, curr):
            if d == 1:
                sl.add((-cnt[v], -v))
            if sl.index((-cnt[v], -v)) < x:
                curr += d*cnt[v]*v
                if x < len(sl):
                    nc, nv = sl[x]
                    curr -= d*nc*nv
            if d != 1:
                sl.remove((-cnt[v], -v))
            return curr

        sl = SortedList()
        cnt = collections.defaultdict(int)
        result = []
        curr = 0
        for i, v in enumerate(nums):
            if v in cnt:
                curr = update(v, -1, curr)
            cnt[v] += 1
            curr = update(v, +1, curr)
            if i < k-1:
                continue
            result.append(curr)
            curr = update(nums[i-(k-1)], -1, curr)
            cnt[nums[i-(k-1)]] -= 1
            if cnt[nums[i-(k-1)]]:
                curr = update(nums[i-(k-1)], +1, curr)
            else:
                del cnt[nums[i-(k-1)]]
        return result


if __name__ == "__main__":
    tests = [
        ([1], 1, 1),
        ([5, 5, 5, 5, 5], 3, 1),
        ([1, 2, 2, 3, 3, 3, 4, 4, 4, 4], 5, 2),
        ([10, 9, 8, 7, 6, 5, 4, 3, 2, 1], 4, 3),
        ([1000000000, 1000000000, 999999999, 1000000000, 999999999], 3, 2),
        ([1, 1, 2, 2, 2, 3, 3, 4, 5, 5, 5, 5, 6], 6, 4),
        ([7, 7, 7, 8, 8, 9, 9, 9, 9, 10, 10, 10], 5, 5),
        ([2, 3, 5, 7, 11, 13, 17, 19, 23, 29], 2, 1),
        ([0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1], 3, 10),
        ([1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2], 5, 3)
    ]

    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        sol = Solution()
        for nums, k, x in tests:
            res = sol.findXSum(nums, k, x)
            for v in res:
                checksum ^= int(v)
        sink += checksum
    print(sink)
    # print sink