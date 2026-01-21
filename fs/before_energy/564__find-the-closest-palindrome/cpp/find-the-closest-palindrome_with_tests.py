# Time:  O(l)
# Space: O(l)

class Solution(object):
    def nearestPalindromic(self, n):
        """
        :type n: str
        :rtype: str
        """
        l = len(n)
        candidates = set((str(10**l + 1), str(10**(l - 1) - 1)))
        prefix = int(n[:(l + 1)/2])
        for i in map(str, (prefix-1, prefix, prefix+1)):
            candidates.add(i + [i, i[:-1]][l%2][::-1])
        candidates.discard(n)
        return min(candidates, key=lambda x: (abs(int(x) - int(n)), int(x)))


if __name__ == "__main__":
    import time

    tests = [
        "0",
        "1",
        "9",
        "10",
        "11",
        "99",
        "100",
        "123",
        "123456789",
        "1000000000000000000"
    ]

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    def hash64_str(s):
        if isinstance(s, unicode):
            s = s.encode('utf-8')
        h = 1469598103934665603
        for ch in s:
            h ^= ord(ch)
            h = (h * 1099511628211) & mask
        return h

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for s in tests:
            res = sol.nearestPalindromic(s)
            if isinstance(res, unicode):
                res_bytes = res.encode('utf-8')
            else:
                res_bytes = res
            h = hash64_str(res_bytes)
            checksum ^= (h + 0x9e3779b97f4a7c15 + len(res_bytes)) & mask
            checksum &= mask
            if res_bytes:
                checksum ^= ord(res_bytes[0]) & 0xFF
                checksum &= mask
                checksum = ((checksum << 1) | (checksum >> 63)) & mask
                checksum ^= ord(res_bytes[-1]) & 0xFF
                checksum &= mask
    end = time.time()

    elapsed_ns = int((end - start) * 1e9)
    print "Checksum: %d" % (checksum & mask)
    print "Elapsed time (ns): %d" % elapsed_ns