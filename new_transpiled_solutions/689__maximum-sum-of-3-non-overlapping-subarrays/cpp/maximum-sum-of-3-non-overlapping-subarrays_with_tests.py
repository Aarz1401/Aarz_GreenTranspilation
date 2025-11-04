# Time:  O(n)
# Space: O(n)

class Solution(object):
    def maxSumOfThreeSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        accu = [0]
        for num in nums:
            accu.append(accu[-1]+num)

        left_pos = [0] * n
        total = accu[k]-accu[0]
        for i in xrange(k, n):
            if accu[i+1]-accu[i+1-k] > total:
                left_pos[i] = i+1-k
                total = accu[i+1]-accu[i+1-k]
            else:
                left_pos[i] = left_pos[i-1]

        right_pos = [n-k] * n
        total = accu[n]-accu[n-k]
        for i in reversed(xrange(n-k)):
            if accu[i+k]-accu[i] > total:
                right_pos[i] = i
                total = accu[i+k]-accu[i]
            else:
                right_pos[i] = right_pos[i+1]

        result, max_sum = [], 0
        for i in xrange(k, n-2*k+1):
            left, right = left_pos[i-1], right_pos[i+k]
            total = (accu[i+k]-accu[i]) + \
                    (accu[left+k]-accu[left]) + \
                    (accu[right+k]-accu[right])
            if total > max_sum:
                max_sum = total
                result = [left, i, right]
        return result


if __name__ == "__main__":
    # Generate benchmark test cases identical to the given C++ code

    class MT19937(object):
        def __init__(self, seed):
            self.mt = [0] * 624
            self.index = 624
            self.mt[0] = seed & 0xFFFFFFFF
            for i in range(1, 624):
                self.mt[i] = (1812433253 * (self.mt[i - 1] ^ (self.mt[i - 1] >> 30)) + i) & 0xFFFFFFFF

        def twist(self):
            for i in range(624):
                y = (self.mt[i] & 0x80000000) | (self.mt[(i + 1) % 624] & 0x7FFFFFFF)
                self.mt[i] = (self.mt[(i + 397) % 624] ^ (y >> 1) ^ (0x9908B0DF if (y & 1) else 0)) & 0xFFFFFFFF
            self.index = 0

        def rand_uint32(self):
            if self.index >= 624:
                self.twist()
            y = self.mt[self.index]
            y ^= (y >> 11)
            y ^= ((y << 7) & 0x9D2C5680)
            y ^= ((y << 15) & 0xEFC60000)
            y ^= (y >> 18)
            self.index += 1
            return y & 0xFFFFFFFF


    def uniform_int(rng, a, b):
        n = b - a + 1
        max32 = 0xFFFFFFFF
        limit = max32 - ((max32 + 1) % n)
        while True:
            r = rng.rand_uint32()
            if r <= limit:
                return a + (r % n)


    tests = []

    # 1) Small k=1 case
    tests.append({'nums': [1, 2, 1, 2, 6, 7, 5, 1, 2], 'k': 1})

    # 2) Classic sample-like case
    tests.append({'nums': [1, 2, 1, 2, 6, 7, 5, 1], 'k': 2})

    # 3) All equal numbers
    tests.append({'nums': [5] * 12, 'k': 2})

    # 4) Increasing sequence
    v4 = [i + 1 for i in xrange(30)]
    tests.append({'nums': v4, 'k': 3})

    # 5) Decreasing sequence
    v5 = [30 - i for i in xrange(30)]
    tests.append({'nums': v5, 'k': 3})

    # 6) Mostly zeros with spikes
    v6 = [0] * 27
    for i in range(3, 6):
        v6[i] = 10
    for i in range(10, 13):
        v6[i] = 20
    for i in range(20, 23):
        v6[i] = 30
    tests.append({'nums': v6, 'k': 3})

    # 7) Large random array
    rng = MT19937(12345)
    v7 = [uniform_int(rng, 0, 100) for _ in xrange(3000)]
    tests.append({'nums': v7, 'k': 10})

    # 8) Minimal n = 3k case with alternating values
    v8 = [5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5]
    tests.append({'nums': v8, 'k': 5})

    # 9) Large k=1 patterned values
    v9 = [((i * 37 + 13) % 101) for i in xrange(1000)]
    tests.append({'nums': v9, 'k': 1})

    # 10) k near n/3 with random values
    rng2 = MT19937(2021)
    v10 = [uniform_int(rng2, 0, 50) for _ in xrange(60)]
    tests.append({'nums': v10, 'k': 20})

    iterations = 1000

    sol = Solution()
    for idx, t in enumerate(tests, 1):
        res = sol.maxSumOfThreeSubarrays(t['nums'], t['k'])
        print "Test #%d: n=%d, k=%d -> %s" % (idx, len(t['nums']), t['k'], res)