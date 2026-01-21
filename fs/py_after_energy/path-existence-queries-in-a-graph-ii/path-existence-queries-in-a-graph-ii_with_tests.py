
# Time:  O((n + q) * logn)
# Space: O(nlogn)

# prefix sum, greedy, binary lifting
class Solution(object):
    def pathExistenceQueries(self, n, nums, maxDiff, queries):
        """
        :type n: int
        :type nums: List[int]
        :type maxDiff: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def ceil_log2_x(x):
            return (x-1).bit_length() if x-1 >= 0 else -1

        sorted_i = sorted((i for i in xrange(n)), key=lambda i : nums[i])
        i_to_idx = [0]*n
        for idx, i in enumerate(sorted_i):
            i_to_idx[i] = idx
        prefix = [0]*n
        for i in xrange(n-1):
            prefix[i+1] = prefix[i]+int(nums[sorted_i[i+1]]-nums[sorted_i[i]] > maxDiff)
        P = [[n-1]*n for _ in xrange(ceil_log2_x(n-1)+1)]
        left = 0
        for right in xrange(n):
            while nums[sorted_i[right]]-nums[sorted_i[left]] > maxDiff:
                P[0][left] = right-1
                left += 1
        for i in xrange(len(P)-1):
            for j in xrange(n):
                P[i+1][j] = P[i][P[i][j]]
        result = [-1]*len(queries)
        for idx, (i, j) in enumerate(queries):
            if i == j:
                result[idx] = 0
                continue
            if prefix[i_to_idx[i]] != prefix[i_to_idx[j]]:
                continue
            if i_to_idx[i] > i_to_idx[j]:
                i, j = j, i
            curr, l = i_to_idx[i], 0
            for k in reversed(xrange(len(P))):
                if P[k][curr] < i_to_idx[j]:
                    curr = P[k][curr]
                    l += 1<<k
            result[idx] = l+1
        return result

def runOnce(sol, tests):
    MASK = (1<<64) - 1
    checksum = 0
    for idx, t in enumerate(tests):
        res = sol.pathExistenceQueries(t.n, t.nums, t.maxDiff, t.queries)
        local = 1469598103934665603  # FNV-1a 64-bit offset
        for v in res:
            x = v & MASK
            local ^= x
            local = (local * 1099511628211) & MASK
        checksum ^= local
        checksum = (checksum + (idx + 1) * (len(res) + 1)) & MASK
    return checksum

if __name__ == "__main__":
    import time

    class TestCase(object):
        __slots__ = ('n', 'nums', 'maxDiff', 'queries')
        def __init__(self, n, nums, maxDiff, queries):
            self.n = n
            self.nums = nums
            self.maxDiff = maxDiff
            self.queries = queries

    tests = []

    # Test 1: Single element
    tests.append(TestCase(
        1,
        [5],
        0,
        [(0, 0), (0, 0)]
    ))

    # Test 2: Two equal elements with maxDiff = 0
    tests.append(TestCase(
        2,
        [1, 1],
        0,
        [(0, 1), (1, 0), (0, 0), (1, 1)]
    ))

    # Test 3: Increasing sequence, large maxDiff
    tests.append(TestCase(
        5,
        [1, 2, 3, 4, 5],
        10,
        [(0, 4), (4, 0), (1, 3), (2, 2)]
    ))

    # Test 4: One large gap causing disconnection
    tests.append(TestCase(
        5,
        [0, 2, 100, 101, 102],
        3,
        [(0, 1), (1, 2), (3, 4), (0, 4), (2, 4)]
    ))

    # Test 5: Mixed negatives, duplicates, and large value
    tests.append(TestCase(
        10,
        [-5, -5, 0, 7, 7, 8, 20, -1, 3, 3],
        2,
        [(0, 1), (2, 9), (7, 6), (3, 4), (8, 9), (2, 7)]
    ))

    # Test 6: All equal elements, maxDiff = 0
    tests.append(TestCase(
        8,
        [5, 5, 5, 5, 5, 5, 5, 5],
        0,
        [(0, 7), (3, 4), (1, 6), (2, 2)]
    ))

    # Test 7: Decreasing sequence, adjacent diffs within maxDiff
    nums7 = list(range(30, 15, -1))
    tests.append(TestCase(
        len(nums7),
        nums7,
        1,
        [(0, 14), (14, 0), (7, 8), (1, 13), (5, 5)]
    ))

    # Test 8: Alternating low/high values -> two segments with maxDiff = 3
    tests.append(TestCase(
        12,
        [1, 10, 2, 11, 3, 12, 4, 13, 5, 14, 6, 15],
        3,
        [(0, 10), (1, 11), (0, 5), (6, 7), (2, 4), (8, 9), (3, 8)]
    ))

    # Test 9: 50 elements with periodic large jumps (segments per 10 elements)
    nums9 = []
    for i in range(50):
        nums9.append(i + (i // 10) * 100)
    tests.append(TestCase(
        len(nums9),
        nums9,
        2,
        [(0, 10), (9, 10), (5, 25), (15, 19), (35, 49), (0, 49), (22, 27), (11, 12)]
    ))

    # Test 10: 64 elements repeating pattern, maxDiff = 0 (only equal values connected)
    nums10 = []
    for i in range(64):
        nums10.append(i % 8)
    tests.append(TestCase(
        len(nums10),
        nums10,
        0,
        [(0, 8), (7, 15), (0, 7), (16, 24), (32, 33), (9, 17), (40, 48), (5, 13)]
    ))

    sol = Solution()

    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in range(iterations):
        checksum += runOnce(sol, tests)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us
