# Time:  O(b^(d/2)), b is the branch factor of bfs, d is the result depth
# Space: O(w * l), w is the number of words, l is the max length of words

from string import ascii_lowercase


# two-end bfs
class Solution(object):
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        words = set(wordList)
        if endWord not in words:
            return 0
        left, right = {beginWord}, {endWord}
        ladder = 2
        while left:
            words -= left
            new_left = set()
            for word in left:
                for new_word in (word[:i]+c+word[i+1:] for i in xrange(len(beginWord)) for c in ascii_lowercase):
                    if new_word not in words:
                        continue
                    if new_word in right: 
                        return ladder
                    new_left.add(new_word)
            left = new_left
            ladder += 1
            if len(left) > len(right): 
                left, right = right, left
        return 0


# Time:  O(b^d), b is the branch factor of bfs, d is the result depth
# Space: O(w * l), w is the number of words, l is the max length of words
class Solution2(object):
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        lookup = set(wordList)
        if endWord not in lookup:
            return 0
        ladder = 2
        q = [beginWord]
        while q:
            new_q = []
            for word in q:
                for i in xrange(len(word)):
                    for j in ascii_lowercase:
                        new_word = word[:i] + j + word[i+1:]
                        if new_word == endWord:
                            return ladder
                        if new_word in lookup:
                            lookup.remove(new_word)
                            new_q.append(new_word)
            q = new_q
            ladder += 1
        return 0


if __name__ == "__main__":
    tests = [
        ("hit", "cog", ["hot", "dot", "dog", "lot", "log", "cog"]),
        ("hit", "cog", ["hot", "dot", "dog", "lot", "log"]),
        ("aab", "abb", ["abb", "aba", "bbb"]),
        ("lead", "gold", ["load", "goad", "gold", "golf", "gald"]),
        ("lost", "cost", ["most", "host", "cost", "lost", "lose"]),
        ("abc", "xyz", ["xbc", "xyc", "xyz", "xya", "abx"]),
        ("aaaa", "bbbb", ["baaa", "bbaa", "bbba", "bbbb", "abaa"]),
        ("talk", "tail", ["tall", "tail", "balk", "tark", "tauk"]),
        ("abcd", "dcba", ["abce", "abde", "acde", "bcde", "dcba"]),
        ("aaaaa", "zzzzz", ["zaaaa", "zzaaa", "zzzaa", "zzzza", "zzzzz", "aaaaz"]),
    ]

    sink = 0
    sol = Solution()
    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for i in range(len(tests)):
            begin, end, wordList = tests[i]
            r = sol.ladderLength(begin, end, wordList)
        #sink = checksum