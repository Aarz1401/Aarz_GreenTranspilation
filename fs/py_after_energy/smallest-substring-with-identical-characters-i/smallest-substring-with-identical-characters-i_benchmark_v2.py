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
    tests = []
    tests.append(("0", 0))
    tests.append(("1", 1))
    tests.append(("00", 0))
    tests.append(("01", 0))
    tests.append(("010101010101010", 0))
    tests.append(("0010110100110", 2))
    tests.append(("11111111111111111111", 5))
    tests.append(("000111000111000111000111000111", 4))
    tests.append(("10110011100011110000", 2))
    longRun = ""
    for i in range(25):
        longRun += "11110000"
    tests.append((longRun, 20))

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for tc in tests:
            r = sol.minLength(tc[0], tc[1])
        #sink = checksum