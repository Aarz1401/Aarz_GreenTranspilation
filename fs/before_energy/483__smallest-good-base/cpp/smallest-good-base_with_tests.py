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
    import time

    # Define 10 diverse test inputs as strings (as required by the solution)
    tests = [
        "3",                        # small, 2^2 - 1
        "13",                       # 1 + 3 + 9
        "31",                       # 2^5 - 1
        "4681",                     # 1 + 8 + 8^2 + 8^3 + 8^4
        "121",                      # 1 + 10 + 100
        "21",                       # 1 + 4 + 16
        "1000000000000000000",      # large 1e18
        "999999999999999999",       # large, 18-digit 9s
        "2251799813685247",         # 2^51 - 1
        "1099511627775"             # 2^40 - 1
    ]

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    start = time.time()

    iterations = 1000
    for iter_idx in xrange(iterations):
        for i in xrange(len(tests)):
            res = sol.smallestGoodBase(tests[i])
            b = int(res)
            checksum = (checksum + b) & mask
            checksum ^= (len(res) + i + iter_idx) & mask
            checksum = ((checksum << 7) | (checksum >> (64 - 7))) & mask

    end = time.time()
    elapsed_ns = int((end - start) * 1e9)

    print 'Checksum:', checksum
    print 'Elapsed time (ns):', elapsed_ns