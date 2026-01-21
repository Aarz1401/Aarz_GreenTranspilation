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
    import time

    # Define 10 diverse special binary string test inputs
    inputs = []
    inputs.append("10")                    # minimal
    inputs.append("1100")                  # nested once
    inputs.append("1010")                  # concatenation of basics
    inputs.append("110100")                # mixed nested/concat
    inputs.append("111000")                # deep nesting
    inputs.append("11011000")              # example-like
    inputs.append("11110000")              # deeper nesting
    inputs.append("1101001100")            # longer mixed
    inputs.append("110110110000")          # multiple clusters
    longRep = "11011000" * 25              # length 200
    inputs.append(longRep)                 # long repeated special string

    solver = Solution()

    checksum = 1469598103934665603  # FNV-1a offset basis
    FNV_PRIME = 1099511628211
    MASK64 = (1 << 64) - 1

    start = time.time()
    iterations = 1000
    for iter in range(iterations):
        for s in inputs:
            out = solver.makeLargestSpecial(s)
            for ch in out:
                checksum ^= ord(ch)
                checksum = (checksum * FNV_PRIME) & MASK64
            checksum ^= (iter + len(out)) & MASK64
            checksum = (checksum * FNV_PRIME) & MASK64
    end = time.time()

    elapsed_ns = int((end - start) * 1000000000)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns