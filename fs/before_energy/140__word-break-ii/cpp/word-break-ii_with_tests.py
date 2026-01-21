# Time:  O(n * l^2 + n * r), l is the max length of the words,
#                            r is the number of the results.
# Space: O(n^2)

class Solution(object):
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: Set[str]
        :rtype: List[str]
        """
        n = len(s)

        max_len = 0
        for string in wordDict:
            max_len = max(max_len, len(string))

        can_break = [False for _ in xrange(n + 1)]
        valid = [[False] * n for _ in xrange(n)]
        can_break[0] = True
        for i in xrange(1, n + 1):
            for l in xrange(1, min(i, max_len) + 1):
                if can_break[i-l] and s[i-l:i] in wordDict:
                    valid[i-l][i-1] = True
                    can_break[i] = True

        result = []
        if can_break[-1]:
            self.wordBreakHelper(s, valid, 0, [], result)
        return result

    def wordBreakHelper(self, s, valid, start, path, result):
        if start == len(s):
            result.append(" ".join(path))
            return
        for i in xrange(start, len(s)):
            if valid[start][i]:
                path += [s[start:i+1]]
                self.wordBreakHelper(s, valid, i + 1, path, result)
                path.pop()

if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    tests = [
        ("catsanddog", ["cat","cats","and","sand","dog"]),
        ("pineapplepenapple", ["apple","pen","applepen","pine","pineapple"]),
        ("aaaaaaaa", ["a","aa","aaa","aaaa"]),
        ("leetcode", ["leet","code"]),
        ("catsandog", ["cats","dog","sand","and","cat"]),
        ("bb", ["a","b","bb","bbb"]),
        ("abcdabcdabcd", ["ab","abc","cd","abcd","d","cda","bca"]),
        ("aaaaab", ["a","aa","aaa","aaaa","aaaaa"]),
        ("catscatscats", ["cat","cats","scat","s","catsc","ats","ca","ts","atsc","at","t","c"]),
        ("thequickbrownfox", ["the","quick","brown","fox","thequick","quickbrown","brownfox"]),
    ]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for t in tests:
            res = sol.wordBreak(t[0], t[1])
            checksum += len(res)
            for sentence in res:
                checksum += len(sentence)
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us