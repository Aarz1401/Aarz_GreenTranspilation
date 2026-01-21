import collections


# mono deque, two pointers, sliding window
class Solution(object):
    def countNonDecreasingSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        result = cnt = 0
        dq = collections.deque()
        right = len(nums)-1
        for left in reversed(xrange(len(nums))):
            while dq and nums[dq[-1]] < nums[left]:
                l = dq.pop()
                r = dq[-1]-1 if dq else right
                cnt += (r-l+1)*(nums[left]-nums[l])
            dq.append(left)
            while cnt > k:
                cnt -= nums[dq[0]]-nums[right]
                if dq[0] == right:
                    dq.popleft()
                right -= 1
            result += right-left+1
        return result


if __name__ == "__main__":
    import time

    # MT19937 implementation to replicate C++ std::mt19937
    class MT19937(object):
        def __init__(self, seed):
            self.mt = [0] * 624
            self.index = 624
            self.mt[0] = seed & 0xFFFFFFFF
            for i in range(1, 624):
                prev = self.mt[i - 1]
                self.mt[i] = (1812433253 * (prev ^ (prev >> 30)) + i) & 0xFFFFFFFF

        def twist(self):
            for i in range(624):
                y = (self.mt[i] & 0x80000000) | (self.mt[(i + 1) % 624] & 0x7fffffff)
                self.mt[i] = self.mt[(i + 397) % 624] ^ (y >> 1)
                if y & 1:
                    self.mt[i] ^= 0x9908B0DF
            self.index = 0

        def rand_uint32(self):
            if self.index >= 624:
                self.twist()
            y = self.mt[self.index]
            self.index += 1
            y ^= (y >> 11)
            y ^= (y << 7) & 0x9D2C5680
            y ^= (y << 15) & 0xEFC60000
            y ^= (y >> 18)
            return y & 0xFFFFFFFF

    def uniform_int_distribution(rng, a, b):
        n = long(b) - long(a) + 1L
        r = 1L << 32
        bucket = r // n
        limit = bucket * n - 1
        while True:
            x = long(rng.rand_uint32())
            if x <= limit:
                return int(long(a) + (x // bucket))

    # Prepare 10 diverse test cases
    tests = []

    # 1) Empty array
    t = {}
    t['nums'] = []
    t['kLL'] = 0L
    t['useLL'] = True
    tests.append(t)

    # 2) Single element
    t = {}
    t['nums'] = [5]
    t['kI'] = 0
    t['useLL'] = False
    tests.append(t)

    # 3) Strictly increasing
    t = {}
    t['nums'] = []
    for i in range(1, 51):
        t['nums'].append(i)
    t['kI'] = 5
    t['useLL'] = False
    tests.append(t)

    # 4) Strictly decreasing
    t = {}
    t['nums'] = []
    for i in range(50, 0, -1):
        t['nums'].append(i)
    t['kLL'] = 100000L
    t['useLL'] = True
    tests.append(t)

    # 5) All equal
    t = {}
    t['nums'] = [7] * 100
    t['kI'] = 1234
    t['useLL'] = False
    tests.append(t)

    # 6) Alternating low/high
    t = {}
    t['nums'] = []
    for i in range(100):
        t['nums'].append(1)
        t['nums'].append(1000)
    t['kLL'] = 5000L
    t['useLL'] = True
    tests.append(t)

    # 7) Mixed negatives and small positives (patterned)
    t = {}
    t['nums'] = []
    for i in range(60):
        t['nums'].append((i % 10) - 5)
    t['kI'] = 50
    t['useLL'] = False
    tests.append(t)

    # 8) Near INT_MAX, small differences (avoid overflow)
    t = {}
    t['nums'] = []
    start = 2147483647 - 200
    for i in range(201):
        t['nums'].append(start + i)
    t['kLL'] = 1000000L
    t['useLL'] = True
    tests.append(t)

    # 9) Pseudorandom values in [-10000, 10000], size 1000
    t = {}
    rng = MT19937(42)
    t['nums'] = [0] * 1000
    for i in range(1000):
        t['nums'][i] = uniform_int_distribution(rng, -10000, 10000)
    t['kLL'] = 1000000000000L
    t['useLL'] = True
    tests.append(t)

    # 10) Repeating segments: up, down, equal blocks
    t = {}
    t['nums'] = []
    for rep in range(5):
        for i in range(1, 21):
            t['nums'].append(i)
        for i in range(20, 0, -1):
            t['nums'].append(i)
        for i in range(10):
            t['nums'].append(5)
    t['kI'] = 10000
    t['useLL'] = False
    tests.append(t)

    sol = Solution()
    sink = 0
    checksum = 0

    start_time = time.time()
    iterations = 1000
    for iter_idx in range(iterations):
        for i in range(len(tests)):
            res = 0L
            if tests[i]['useLL']:
                res = sol.countNonDecreasingSubarrays(tests[i]['nums'], tests[i]['kLL'])
            else:
                res = sol.countNonDecreasingSubarrays(tests[i]['nums'], tests[i]['kI'])
            checksum += (long(res) ^ long(iter_idx + i * 97))
            sink = res
    end_time = time.time()

    elapsed_ns = long((end_time - start_time) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns