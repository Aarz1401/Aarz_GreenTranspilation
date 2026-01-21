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
    from time import time

    tests = []
    tests.append(("0", 0))                              # 1: single char, zero ops
    tests.append(("1", 1))                              # 2: single char, one op
    tests.append(("0101010101", 0))                     # 3: alternating, even length, zero ops
    tests.append(("1010101010101", 5))                  # 4: alternating, odd length, some ops
    tests.append(("0000000000", 0))                     # 5: all zeros
    tests.append(("1111111111", 4))                     # 6: all ones
    tests.append(("0011001111001100", 3))               # 7: grouped pairs
    tests.append(("000111000111000111000", 2))          # 8: repeating runs

    # 9: long runs with varied lengths (total length 1000)
    s9 = ""
    s9 += "0" * 200
    s9 += "1" * 300
    s9 += "0" * 150
    s9 += "1" * 350
    tests.append((s9, 100))

    # 10: long alternating (length 1000)
    s10 = "".join(("0" if i % 2 == 0 else "1") for i in xrange(1000))
    tests.append((s10, 10))

    sol = Solution()

    start = time()

    checksum = 0

    iterations = 1000
    for iter in xrange(iterations):
        for tc in tests:
            checksum += sol.minLength(tc[0], tc[1])

    end = time()
    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us