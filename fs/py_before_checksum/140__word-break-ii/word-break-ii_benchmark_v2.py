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
    tests = [
        {'s': 'catsanddog', 'dict': ['cat','cats','and','sand','dog']},
        {'s': 'pineapplepenapple', 'dict': ['apple','pen','applepen','pine','pineapple']},
        {'s': 'aaaaaaa', 'dict': ['a','aa','aaa']},
        {'s': 'leetcode', 'dict': ['leet','code']},
        {'s': 'catsandog', 'dict': ['cats','dog','sand','and','cat']},
        {'s': 'abcd', 'dict': ['a','abc','b','cd']},
        {'s': 'aaaaab', 'dict': ['a','aa','aaa','aaaa','b']},
        {'s': 'bb', 'dict': ['a','b','bbb','bbbb']},
        {'s': 'foobarbaz', 'dict': ['foo','bar','baz','foobar','barbaz','foob','arb','az']},
        {'s': 'impossible', 'dict': ['im','possible','impo','ss','ible']}
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            res = sol.wordBreak(t['s'], set(t['dict']))
            checksum += int(len(res))
        sink += checksum
    print(sink)