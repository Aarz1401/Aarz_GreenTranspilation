
# Time:  O(26 * n)
# Space: O(26)

# freq table, dp
class Solution(object):
    def makeStringGood(self, s):
        """
        :type s: str
        :rtype: int
        """
        cnt = [0]*26
        for x in s:
            cnt[ord(x)-ord('a')] += 1
        result = len(s)
        for f in xrange(min(x for x in cnt if x), max(cnt)+1):
            # dp1: min number of the last one of the operations is insert
            # dp2: min number of the last one of the operations is delete
            dp1 = dp2 = 0
            for i in xrange(26):
                if not cnt[i]:
                    continue
                if cnt[i] >= f:
                    new_dp1 = len(s)
                    new_dp2 = min(dp1, dp2)+(cnt[i]-f)
                else:
                    free = (cnt[i-1]-f if cnt[i-1] >= f else cnt[i-1]) if i-1 >= 0 else 0
                    new_dp1 = min(min(dp1, dp2)+(f-cnt[i]), dp2+max((f-cnt[i])-free, 0))
                    new_dp2 = min(dp1, dp2)+cnt[i]
                dp1, dp2 = new_dp1, new_dp2
            result = min(result, dp1, dp2)
        return result


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs (strings as required by the solution)
    tests = []
    tests.append("")  # 1. empty
    tests.append("a")  # 2. single char
    tests.append("aaaaaaa")  # 3. uniform
    tests.append("abc")  # 4. small distinct
    tests.append("abababababababababababab")  # 5. alternating pattern
    tests.append("thequickbrownfoxjumpsoveralazydog")  # 6. pangram
    tests.append("mississippi")  # 7. repeated clusters
    # 8. full alphabet once
    t8 = ""
    for c in range(ord('a'), ord('z') + 1):
        t8 += chr(c)
    tests.append(t8)
    # 9. large two-char block
    t9 = ""
    t9 += 'a' * 500
    t9 += 'b' * 500
    tests.append(t9)
    # 10. repeated word
    t10 = ""
    for k in range(100):
        t10 += "leetcode"
    tests.append(t10)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for iter in range(iterations):
        for s in tests:
            try:
                checksum += sol.makeStringGood(s)
            except Exception:
                # Skip cases that may not be supported by the implementation (e.g., empty string)
                pass

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: " + str(checksum)
    print "Elapsed time (ms): " + str(elapsed_ms)
