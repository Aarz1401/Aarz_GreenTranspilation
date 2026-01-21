
# Time:  O(nlogn)
# Space: O(1)

# binary search, greedy
class Solution(object):
    def minLength(self, s, numOps):
        """
        :type s: str
        :type numOps: int
        :rtype: int
        """
        def binary_search(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return left

        def lengths():
            cnt = 0
            for i in xrange(len(s)):
                cnt += 1
                if i+1 == len(s) or s[i+1] != s[i]:
                    yield cnt
                    cnt = 0
    
        def check(x):
            if x == 1:
                cnt = sum(int(x) != i%2 for i, x in enumerate(s))
                return min(cnt, len(s)-cnt) <= numOps
            return sum(l//(x+1) for l in lengths()) <= numOps
    
        return binary_search(1, len(s), check)


# Time:  O(nlogn)
# Space: O(n)
# binary search, greedy
class Solution2(object):
    def minLength(self, s, numOps):
        """
        :type s: str
        :type numOps: int
        :rtype: int
        """
        def binary_search(left, right, check):
            while left <= right:
                mid = left + (right-left)//2
                if check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return left

        def check(x):
            if x == 1:
                cnt = sum(int(x) != i%2 for i, x in enumerate(s))
                return min(cnt, len(s)-cnt) <= numOps
            return sum(l//(x+1) for l in arr) <= numOps
    
        arr = []
        cnt = 0
        for i in xrange(len(s)):
            cnt += 1
            if i+1 == len(s) or s[i+1] != s[i]:
                arr.append(cnt)
                cnt = 0
        return binary_search(1, len(s), check)


if __name__ == "__main__":
    import time
    import random

    def makeAlternating(n, startChar):
        offset = 0 if startChar == '0' else 1
        return ''.join(chr(ord('0') + ((i + offset) & 1)) for i in xrange(n))

    def makeRuns(pairs):
        out = []
        for ch, cnt in pairs:
            out.append(ch * cnt)
        return ''.join(out)

    def makeRandom01(n, seed):
        rng = random.Random(seed)
        return ''.join('1' if rng.getrandbits(1) else '0' for _ in xrange(n))

    # Generate 10 diverse test inputs (string s, int numOps)
    tests = []

    # 1) Single zero, zero ops
    tests.append(("0", 0))

    # 2) Single one, one op
    tests.append(("1", 1))

    # 3) Alternating even length, zero ops
    tests.append((makeAlternating(10, '0'), 0))

    # 4) Small mixed blocks, small ops
    tests.append(("00110011", 1))

    # 5) All zeros, moderate ops
    tests.append(("0" * 100, 10))

    # 6) All ones, zero ops, odd length
    tests.append(("1" * 257, 0))

    # 7) Random length 1000, arbitrary ops
    tests.append((makeRandom01(1000, 42), 123))

    # 8) Long runs with varied sizes
    tests.append((
        makeRuns([
            ('0', 10), ('1', 10), ('0', 8), ('1', 6), ('0', 1), ('1', 20), ('0', 5)
        ]),
        5
    ))

    # 9) Mixed pattern with increasing/decreasing run lengths
    tests.append((
        makeRuns([
            ('0', 3), ('1', 3), ('0', 2), ('1', 4), ('0', 4), ('1', 5), ('0', 6), ('1', 2)
        ]),
        8
    ))

    # 10) Larger random length 5000, higher ops
    tests.append((makeRandom01(5000, 2025), 777))

    sol = Solution()

    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for i in xrange(len(tests)):
            s, numOps = tests[i]
            checksum += sol.minLength(s, numOps)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us
