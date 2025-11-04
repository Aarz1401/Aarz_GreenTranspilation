# Time:  O(n * l^2)
# Space: O(n * l)

class Solution(object):
    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        lookup = set(words)
        result = []
        for word in words:
            dp = [False] * (len(word)+1)
            dp[0] = True
            for i in xrange(len(word)):
                if not dp[i]:
                    continue

                for j in xrange(i+1, len(word)+1):
                    if j - i < len(word) and word[i:j] in lookup:
                        dp[j] = True

                if dp[len(word)]:
                    result.append(word)
                    break

        return result

if __name__ == "__main__":
    import sys
    import time

    # Prepare 10 diverse test inputs
    tests = []

    # 1) Classic concatenation cases
    tests.append(["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"])

    # 2) No concatenations
    tests.append(["xyz","abc","defgh","ijkl","mnop"])

    # 3) Duplicates and simple concatenations
    tests.append(["cat","catcat","catcat","catcatcat","dog","dogcat","catdog","dogdogcat"])

    # 4) Includes empty string and small repeats
    tests.append(["","a","aa","aaa","aaaa","b","bb","bbb"])

    # 5) Prefix/suffix style words
    tests.append(["base","ball","baseball","ballbase","basebase","ballball"])

    # 6) Overlapping but mostly non-concatenatable
    tests.append(["abcde","bcdea","cdeab","deabc","eabcd","abcdabc"])

    # 7) Long chain with one large repeat and a small valid one
    tests.append(["a","b","ab","abc","abcd","abcde","abcdef","abcdefg","abcdefgh","abcdefghi","abcdefghij","abcdefghijabcdefghij"])

    # 8) Palindromic patterns and combinations
    tests.append(["noon","good","goodnoon","noongood","goodgood","nogood","on"])

    # 9) Programmatically generated repeated character strings
    t9 = []
    t9.append("x")
    t9.append("xx")
    t9.append("xxx")
    t9.append("x" * 8)    # 8 x's
    t9.append("x" * 16)   # 16 x's = 8 + 8
    t9.append("x" * 24)   # 24 x's = 8 + 8 + 8
    tests.append(t9)

    # 10) Color words with multi-part concatenations
    tests.append(["red","blue","green","redblue","bluegreen","redbluegreen","greenredblue","blueredgreenred","redred"])

    if len(tests) != 10:
        sys.stderr.write("Error: Expected 10 test inputs, got %d\n" % len(tests))
        sys.exit(1)

    checksum = 0

    start = time.time()
    iterations = 1000
    for iter in xrange(iterations):
        sol = Solution()
        for tc in tests:
            words = list(tc)
            res = sol.findAllConcatenatedWordsInADict(words)
            checksum += len(res)
            for s in res:
                checksum += len(s)
                if s:
                    checksum += ord(s[0])
                    checksum += ord(s[-1])
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))
    print "Checksum: %d" % checksum
    print "Elapsed microseconds: %d" % elapsed_us