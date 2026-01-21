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
    tests = [
        ("0", 0),
        ("1", 0),
        ("00000", 0),
        ("010101", 0),
        ("11110000", 2),
        ("00110011", 1),
        ("101010001110", 3),
        ("000111000111000", 5),
        ("0100111001011", 4),
        ("0010010110110001110100011101100010110010100110", 7),
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for s, x in tests:
            r = sol.minLength(s, x)
        #sink = checksum

    # print sink