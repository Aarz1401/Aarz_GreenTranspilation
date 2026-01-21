# Time:  O(n^2 * (l^2 + 2^n))
# Space: O(n^2)

class Solution(object):
    def shortestSuperstring(self, A):
        """
        :type A: List[str]
        :rtype: str
        """
        n = len(A)
        overlaps = [[0]*n for _ in xrange(n)]
        for i, x in enumerate(A):
            for j, y in enumerate(A):
                for l in reversed(xrange(min(len(x), len(y)))):
                    if y[:l].startswith(x[len(x)-l:]):
                        overlaps[i][j] = l
                        break

        dp = [[0]*n for _ in xrange(1<<n)]
        prev = [[None]*n for _ in xrange(1<<n)]
        for mask in xrange(1, 1<<n):
            for bit in xrange(n):
                if ((mask>>bit) & 1) == 0:
                    continue
                prev_mask = mask^(1<<bit)
                for i in xrange(n):
                    if ((prev_mask>>i) & 1) == 0:
                        continue
                    value = dp[prev_mask][i] + overlaps[i][bit]
                    if value > dp[mask][bit]:
                        dp[mask][bit] = value
                        prev[mask][bit] = i
        
        bit = max(xrange(n), key = dp[-1].__getitem__)
        words = []
        mask = (1<<n)-1
        while bit is not None:
            words.append(bit)
            mask, bit = mask^(1<<bit), prev[mask][bit]
        words.reverse()
        lookup = set(words)
        words.extend([i for i in xrange(n) if i not in lookup])

        result = [A[words[0]]]
        for i in xrange(1, len(words)):
            overlap = overlaps[words[i-1]][words[i]]
            result.append(A[words[i]][overlap:])
        return "".join(result)

if __name__ == "__main__":
    import time

    tests = []

    # 1. Simple overlap
    tests.append(["ab", "bc"])

    # 2. No overlaps
    tests.append(["abc", "def", "ghi"])

    # 3. Classic multi-overlap case
    tests.append(["catgc", "ctaagt", "gcta", "ttca", "atgcatc"])

    # 4. Contains substrings
    tests.append(["abcd", "bc", "c", "d"])

    # 5. Duplicates and repeats
    tests.append(["aaa", "aaa", "aa"])

    # 6. Mixed with embedded word
    tests.append(["leetc", "code", "leetcode", "etco"])

    # 7. Circular overlaps
    tests.append(["abc", "bca", "cab"])

    # 8. Many similar strings
    tests.append(["aaaaa", "aaaa", "aaa", "aa", "a"])

    # 9. Longer strings with patterned overlaps
    t9 = []
    t9a = 'a' * 200 + 'b' + 'c' * 200
    t9b = 'a' * 150 + "bc" + 'c' * 150
    t9c = 'c' * 200 + "d" + 'e' * 100
    t9d = 'a' * 100 + 'b' * 100 + 'c' * 100
    t9e = 'b' * 50 + 'c' * 200 + 'd'
    t9.append(t9a)
    t9.append(t9b)
    t9.append(t9c)
    t9.append(t9d)
    t9.append(t9e)
    tests.append(t9)

    # 10. Mixed genome-like overlaps
    tests.append(["gttac", "tacga", "acg", "cgat", "gattt"])

    sol = Solution()
    checksum = 0
    mask = (1 << 64) - 1

    iterations = 1000
    start = time.time()
    for it in xrange(iterations):
        for i in xrange(len(tests)):
            res = sol.shortestSuperstring(tests[i])
            size = len(res)
            checksum ^= size
            checksum &= mask
            if res:
                checksum = (checksum * 1315423911) & mask
                checksum ^= ord(res[0])
                checksum &= mask
                checksum = (checksum * 2654435761) & mask
                checksum ^= ord(res[-1])
                checksum &= mask
            if len(res) > 4:
                checksum ^= ord(res[len(res) // 2])
                checksum &= mask
                checksum ^= ord(res[len(res) // 3])
                checksum &= mask
                checksum ^= ord(res[len(res) // 4])
                checksum &= mask
    end = time.time()

    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: " + str(checksum)
    print "Elapsed time (ns): " + str(elapsed_ns)