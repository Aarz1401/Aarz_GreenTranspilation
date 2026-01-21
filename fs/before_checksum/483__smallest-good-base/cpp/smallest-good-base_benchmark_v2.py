# Time:  O(logn * log(logn))
# Space: O(1)

import math


class Solution(object):
    def smallestGoodBase(self, n):
        """
        :type n: str
        :rtype: str
        """
        num = int(n)
        max_len = int(math.log(num,2))
        for l in xrange(max_len, 1, -1):
            b = int(num ** (l**-1))
            if (b**(l+1)-1) // (b-1) == num:
                return str(b)
        return str(num-1)

if __name__ == "__main__":
    tests = [
        "3",
        "4",
        "13",
        "31",
        "4681",
        "999999999999999999",
        "1000000000000000000",
        "2251799813685247",
        "1099511627775",
        "1000003"
    ]

    s = Solution()
    sink = 0

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for n in tests:
            res = s.smallestGoodBase(n)
            checksum += len(res)
            checksum += ord(res[-1]) - ord('0')
        sink += checksum
    print(sink)

    # print sink