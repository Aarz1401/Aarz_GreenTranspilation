# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ([1, 2, 3, 4, 5], 3, 1),                            # simple increasing
        ([7, 7, 7, 7, 7, 7], 2, 2),                         # all equal
        ([1, 1, 2, 2, 3, 3, 4, 4], 5, 3),                   # increasing with duplicates
        ([-5, -1, 0, 2, -1, 2, 3, -5], 4, 2),               # includes negatives
        ([1000000000, -1000000000, 999999999, -999999999, 0, 123456789, -123456789], 3, 2), # large magnitude
        ([10, -10, 20, -20, 0], 1, 5),                      # k = 1, x >= unique
        ([4, 4, 4, 2, 2, 7, 7, 7], 8, 0),                   # x = 0
        ([5, 5, 5, 5, 3, 3, 3, 2, 2], 6, 2),                # many duplicates
        ([0, 1, 0, 1, 0, 1, 2, 2, 2, 3, 0], 5, 3),          # zigzag with zeros
        ([8, 1, 8, 2, 8, 3, 8, 4, 8, 5, 7, 7, 9, 9, 1, 2], 10, 4), # mixed pattern
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        nums, k, x = test
        sol.findXSum(list(nums), k, x)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for nums, k, x in test_cases:
            result = sol.findXSum(list(nums), k, x)
            results.append(result)

    elapsed_time = time.time() - start_time

    # Checksum similar to C++: add last element if exists, then XOR with size
    checksum = 0
    for r in results:
        try:
            if r:
                checksum += int(r[-1])
            checksum ^= len(r)
        except Exception:
            checksum ^= hash(str(r))

    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()