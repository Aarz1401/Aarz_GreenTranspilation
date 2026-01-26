# Time:  f(n) = k * f(n/k) + n/k * klogk <= O(logn * nlogk) <= O(n^2)
#        n is the length of S, k is the max number of special strings in each depth
# Space: O(n)

class Solution(object):
    def makeLargestSpecial(self, S):
        """
        :type S: str
        :rtype: str
        """
        result = []
        anchor = count = 0
        for i, v in enumerate(S):
            count += 1 if v == '1' else -1
            if count == 0:
                result.append("1{}0".format(self.makeLargestSpecial(S[anchor+1:i])))
                anchor = i+1
        result.sort(reverse = True)
        return "".join(result)

if __name__ == "__main__":
    tests = [
        "10",
        "1100",
        "1010",
        "111000",
        "110100",
        "110010",
        "11100100",
        "11011000",
        "1011001100",
        "1101101000"
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for s in tests:
            r = sol.makeLargestSpecial(s)
        #     checksum += int(len(r))
        # sink = checksum