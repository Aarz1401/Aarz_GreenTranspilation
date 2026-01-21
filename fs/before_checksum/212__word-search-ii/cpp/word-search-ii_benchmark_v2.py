
# Time:  O(m * n * 4 * 3^(h - 1)) ~= O(m * n * 3^h), h is the height of trie
# Space: O(t), t is the number of nodes in trie

class TrieNode(object):
    # Initialize your data structure here.
    def __init__(self):
        self.is_string = False
        self.leaves = {}

    # Inserts a word into the trie.
    def insert(self, word):
        cur = self
        for c in word:
            if not c in cur.leaves:
                cur.leaves[c] = TrieNode()
            cur = cur.leaves[c]
        cur.is_string = True


class Solution(object):
    def findWords(self, board, words):
        """
        :type board: List[List[str]]
        :type words: List[str]
        :rtype: List[str]
        """
        visited = [[False for j in xrange(len(board[0]))] for i in xrange(len(board))]
        result = {}
        trie = TrieNode()
        for word in words:
            trie.insert(word)

        for i in xrange(len(board)):
            for j in xrange(len(board[0])):
                self.findWordsRecu(board, trie, 0, i, j, visited, [], result)

        return result.keys()

    def findWordsRecu(self, board, trie, cur, i, j, visited, cur_word, result):
        if not trie or i < 0 or i >= len(board) or j < 0 or j >= len(board[0]) or visited[i][j]:
            return

        if board[i][j] not in trie.leaves:
            return

        cur_word.append(board[i][j])
        next_node = trie.leaves[board[i][j]]
        if next_node.is_string:
            result["".join(cur_word)] = True

        visited[i][j] = True
        self.findWordsRecu(board, next_node, cur + 1, i + 1, j, visited, cur_word, result)
        self.findWordsRecu(board, next_node, cur + 1, i - 1, j, visited, cur_word, result)
        self.findWordsRecu(board, next_node, cur + 1, i, j + 1, visited, cur_word, result)
        self.findWordsRecu(board, next_node, cur + 1, i, j - 1, visited, cur_word, result)
        visited[i][j] = False
        cur_word.pop()


if __name__ == "__main__":
    tests = []

    tests.append((
        [
            ['o','a','a','n'],
            ['e','t','a','e'],
            ['i','h','k','r'],
            ['i','f','l','v']
        ],
        ["oath","pea","eat","rain","hklf","hf"]
    ))

    tests.append((
        [
            ['a','b','c','d','e','f']
        ],
        ["abc","cde","fed","abf","ace"]
    ))

    tests.append((
        [
            ['g'],
            ['h'],
            ['i'],
            ['j'],
            ['k']
        ],
        ["ghi","ijk","ghij","hg","jk"]
    ))

    tests.append((
        [
            ['a','a','a'],
            ['a','a','a'],
            ['a','a','a']
        ],
        ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa"]
    ))

    tests.append((
        [
            ['x','y','z'],
            ['p','q','r'],
            ['l','m','n']
        ],
        ["abc","def","ghi","uvw","rst"]
    ))

    tests.append((
        [
            ['s','e','e','d'],
            ['s','e','n','d'],
            ['s','e','e','d']
        ],
        ["see","seen","seed","sees","send","ends"]
    ))

    tests.append((
        [
            ['t','h','i','s','i','s','a'],
            ['s','i','m','p','l','e','x']
        ],
        ["this","is","a","simple","isth","xis","thisis","plex","simplex"]
    ))

    tests.append((
        [
            ['a','b','c','d'],
            ['e','f','g','h'],
            ['i','j','k','l'],
            ['m','n','o','p']
        ],
        ["abfj","mnop","aeim","cfk","ghkl"]
    ))

    tests.append((
        [
            ['a','b','a'],
            ['b','a','b'],
            ['a','b','a']
        ],
        ["aba","bab","ababa","babab","aaaa","abba"]
    ))

    tests.append((
        [
            ['l','e','e','t','c'],
            ['o','d','e','c','o'],
            ['d','e','l','e','t'],
            ['c','o','e','d','e'],
            ['c','o','d','e','s']
        ],
        ["leet","code","codes","leetcode","cool","deco","decode"]
    ))

    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        sol = Solution()
        for board, words in tests:
            res = sol.findWords(board, words)
            checksum += int(len(res))
        sink += checksum
    print(sink)

    # print sink
