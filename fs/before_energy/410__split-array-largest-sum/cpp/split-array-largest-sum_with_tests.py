# Time:  O(nlogs), s is the sum of nums
# Space: O(1)

class Solution(object):
    def splitArray(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        def check(nums, m, s):
            cnt, curr_sum = 1, 0
            for num in nums:
                curr_sum += num
                if curr_sum > s:
                    curr_sum = num
                    cnt += 1
            return cnt <= m

        left, right = max(nums), sum(nums)
        while left <= right:
            mid = left + (right - left) // 2
            if check(nums, m, mid):
                right = mid - 1
            else:
                left = mid + 1
        return left

if __name__ == "__main__":
    import time
    import random

    arrays = []
    ms = []

    # 1) Classic example
    arrays.append([7, 2, 5, 10, 8])
    ms.append(2)

    # 2) All ones, m equals size
    arrays.append([1, 1, 1, 1, 1])
    ms.append(5)

    # 3) Single large element
    arrays.append([1000000000])
    ms.append(1)

    # 4) Increasing sequence 1..1000, m = 10
    v = list(range(1, 1001))
    arrays.append(v)
    ms.append(10)

    # 5) Large equal numbers, m = 5
    v = [1000] * 1000
    arrays.append(v)
    ms.append(5)

    # 6) All zeros
    arrays.append([0, 0, 0, 0])
    ms.append(2)

    # 7) Random moderate size, fixed seed for determinism
    rng = random.Random(123456)
    v = [rng.randint(0, 10000) for _ in range(200)]
    arrays.append(v)
    ms.append(20)

    # 8) Alternating small and large values
    v = [(1 if (i % 2 == 0) else 1000000) for i in range(500)]
    arrays.append(v)
    ms.append(50)

    # 9) m equals array size (result should be max element)
    v = [((i * i) % 97) + 1 for i in range(50)]
    arrays.append(v)
    ms.append(50)

    # 10) Descending values with step, m = 3
    v = [10000 - i * 50 for i in range(100)]
    arrays.append(v)
    ms.append(3)

    solver = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for iter_idx in range(iterations):
        for t in range(len(arrays)):
            res = solver.splitArray(arrays[t], ms[t])
            checksum += int(res) * (iter_idx + 1) + t
    end = time.time()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms