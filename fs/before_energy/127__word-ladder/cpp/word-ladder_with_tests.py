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
    import time

    tests = []

    tests.append(("hit", "cog", ["hot","dot","dog","lot","log","cog"]))

    tests.append(("hit", "cog", ["hot","dot","dog","lot","log"]))

    tests.append(("a", "c", ["a","b","c"]))

    tests.append(("talk", "tail", ["talk","tall","tail","balk","tale","fail"]))

    tests.append(("lead", "gold", ["load","goad","gold","golf","gale","geld","lead"]))

    tests.append(("aaaa", "bbbb", ["aaab","aabb","abbb","bbbb","baaa","bbaa"]))

    tests.append(("lost", "cost", ["lost","cost","most","host","post"]))

    tests.append(("abc", "xyz", ["abx","axc","xbc","yzz","xya","xyz"]))

    tests.append(("zzzz", "zzzy", ["zzzy","zzyy","zyyy","yyyy","zzzz","azzz","zzzq","zzqy"]))

    dense = []
    for c1 in 'abc':
        for c2 in 'abc':
            for c3 in 'abc':
                dense.append(c1 + c2 + c3)
    tests.append(("aaa", "ccc", dense))

    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        sol = Solution()
        for beginWord, endWord, wordList in tests:
            res = sol.ladderLength(beginWord, endWord, list(wordList))
            checksum += res

    end = time.time()
    us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % us