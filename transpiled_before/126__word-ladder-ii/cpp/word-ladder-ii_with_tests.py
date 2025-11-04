# Time:  O(b^(d/2)), b is the branch factor of bfs, d is the result depth
# Space: O(w * l), w is the number of words, l is the max length of words

from collections import defaultdict
from string import ascii_lowercase


class Solution(object):
    def findLadders(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        def backtracking(tree, beginWord, word): 
            return [[beginWord]] if word == beginWord else [path + [word] for new_word in tree[word] for path in backtracking(tree, beginWord, new_word)]

        words = set(wordList)
        if endWord not in words:
            return []
        tree = defaultdict(set)
        is_found, left, right, is_reversed = False, {beginWord}, {endWord}, False
        while left:
            words -= left
            new_left = set()
            for word in left:
                for new_word in (word[:i]+c+word[i+1:] for i in xrange(len(beginWord)) for c in ascii_lowercase):
                    if new_word not in words:
                        continue
                    if new_word in right: 
                        is_found = True
                    else: 
                        new_left.add(new_word)
                    tree[new_word].add(word) if not is_reversed else tree[word].add(new_word)
            if is_found:
                break
            left = new_left
            if len(left) > len(right): 
                left, right, is_reversed = right, left, not is_reversed
        return backtracking(tree, beginWord, endWord)


# Time:  O(b^d), b is the branch factor of bfs, d is the result depth
# Space: O(w * l), w is the number of words, l is the max length of words
class Solution2(object):
    def findLadders(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        dictionary = set(wordList)
        result, cur, visited, found, trace = [], [beginWord], set([beginWord]), False, defaultdict(list)

        while cur and not found:
            for word in cur:
                visited.add(word)

            next = set()
            for word in cur:
                for i in xrange(len(word)):
                    for c in ascii_lowercase:
                        candidate = word[:i] + c + word[i + 1:]
                        if candidate not in visited and candidate in dictionary:
                            if candidate == endWord:
                                found = True
                            next.add(candidate)
                            trace[candidate].append(word)
            cur = next

        if found:
            self.backtrack(result, trace, [], endWord)

        return result

    def backtrack(self, result, trace, path, word):
        if not trace[word]:
            path.append(word)
            result.append(path[::-1])
            path.pop()
        else:
            for prev in trace[word]:
                path.append(word)
                self.backtrack(result, trace, path, prev)
                path.pop()


if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    tests = []

    # 1) Classic example with two shortest ladders
    tests.append({
        'begin': "hit",
        'end': "cog",
        'wordList': ["hot","dot","dog","lot","log","cog"]
    })

    # 2) End word missing -> no path
    tests.append({
        'begin': "hit",
        'end': "cog",
        'wordList': ["hot","dot","dog","lot","log"]
    })

    # 3) Expanded dictionary to create more branching
    tests.append({
        'begin': "hit",
        'end': "cog",
        'wordList': ["hot","dot","dog","lot","log","cog","hig","hog","cot","cig","cit"]
    })

    # 4) Single-letter words
    tests.append({
        'begin': "a",
        'end': "c",
        'wordList': ["a","b","c"]
    })

    # 5) Direct transformation available with distractors
    tests.append({
        'begin': "bat",
        'end': "cat",
        'wordList': ["bot","bog","cog","cot","cat","cab","car","bar","bat"]
    })

    # 6) 4-letter path with a clear chain
    tests.append({
        'begin': "lost",
        'end': "miss",
        'wordList': ["most","mist","miss","lost","fist","fish"]
    })

    # 7) 4-letter with stepwise bridging
    tests.append({
        'begin': "aaaa",
        'end': "bbbb",
        'wordList': ["aaab","aabb","abbb","bbbb","bbba"]
    })

    # 8) Well-known 4-letter ladder
    tests.append({
        'begin': "lead",
        'end': "gold",
        'wordList': ["load","goad","gold","lead","mead"]
    })

    # 9) Empty word list -> no path
    tests.append({
        'begin': "a",
        'end': "b",
        'wordList': []
    })

    # 10) No neighbors from begin; end present but unreachable
    tests.append({
        'begin': "zzz",
        'end': "aaa",
        'wordList': ["aaa","abc","abd","aac","acc"]
    })

    solver = Solution()

    def U64(x):
        return x & 0xFFFFFFFFFFFFFFFF

    checksum = 0

    start = time.time()

    iterations = 1000
    C1 = 1315423911
    C2 = 0x9e3779b97f4a7c15

    for _ in range(iterations):
        for tc in tests:
            wl = list(tc['wordList'])
            res = solver.findLadders(tc['begin'], tc['end'], wl)

            checksum = U64(checksum + len(res))
            for path in res:
                checksum = U64(checksum ^ (len(path) * C1))
                for w in path:
                    for ch in w:
                        checksum = U64((checksum * C1) ^ ord(ch) ^ C2)
            checksum = U64(checksum ^ ((len(tc['begin']) << 32) ^ len(tc['end'])))

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %d" % checksum
    print "Elapsed time (ms): %.6f" % elapsed_ms