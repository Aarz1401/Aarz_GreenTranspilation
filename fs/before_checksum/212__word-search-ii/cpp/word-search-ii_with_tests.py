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
    import time

    tests = []

    # 1) Classic example
    tests.append({
        'board': [
            ['o','a','a','n'],
            ['e','t','a','e'],
            ['i','h','k','r'],
            ['i','f','l','v']
        ],
        'words': ["oath","pea","eat","rain"]
    })

    # 2) Small 2x2 with overlapping candidates
    tests.append({
        'board': [
            ['a','b'],
            ['c','d']
        ],
        'words': ["ab","abc","abcd","acdb","bd","cd","adcb"]
    })

    # 3) Empty board
    tests.append({
        'board': [
        ],
        'words': ["a","b"]
    })

    # 4) Empty words
    tests.append({
        'board': [
            ['a','b'],
            ['c','d']
        ],
        'words': []
    })

    # 5) Single cell
    tests.append({
        'board': [
            ['a']
        ],
        'words': ["a","aa","b"]
    })

    # 6) Larger 5x5 mixed letters
    tests.append({
        'board': [
            ['t','h','i','s','a'],
            ['w','a','t','s','o'],
            ['o','a','h','g','g'],
            ['f','g','d','t','e'],
            ['x','y','z','b','n']
        ],
        'words': ["this","two","fat","that","hat","wag","dog","goat","fog","than","gadget"]
    })

    # 7) No matches
    tests.append({
        'board': [
            ['x','y','z'],
            ['x','y','z'],
            ['x','y','z']
        ],
        'words': ["abc","def","ghi"]
    })

    # 8) All same letters with duplicates in words
    tests.append({
        'board': [
            ['a','a','a'],
            ['a','a','a'],
            ['a','a','a']
        ],
        'words': ["a","aa","aaa","aaaa","aaaaa","aaaaaa","a"]
    })

    # 9) Rectangular 3x5
    tests.append({
        'board': [
            ['s','e','e','n','e'],
            ['l','e','e','k','s'],
            ['a','b','a','b','a']
        ],
        'words': ["see","seen","seek","seeks","leek","leeks","seab","eel","ababa"]
    })

    # 10) 4x6 keyboard-like layout
    tests.append({
        'board': [
            ['q','w','e','r','t','y'],
            ['a','s','d','f','g','h'],
            ['z','x','c','v','b','n'],
            ['m','j','k','l','p','o']
        ],
        'words': ["qwerty","asdf","zxcv","mjk","klp","qwe","ghn","bnm","pol","tygh","cvbn","sdg","jkl","poi"]
    })

    checksum = 0
    mask64 = (1 << 64) - 1

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for tc in tests:
            sol = Solution()
            board = tc['board']
            words = tc['words']
            if not board or (isinstance(board, list) and len(board) > 0 and len(board[0]) == 0):
                res = []
            else:
                res = sol.findWords(board, words)
            for s in res:
                local = 1469598103934665603
                for ch in s:
                    local ^= ord(ch)
                    local &= mask64
                    local = (local * 1099511628211) & mask64
                checksum ^= (local + (len(s) * 1315423911)) & mask64
                checksum &= mask64
            checksum = (checksum + (len(res) * 2654435761)) & mask64

    elapsed_ms = int((time.time() - start) * 1000)

    print "Checksum:", checksum
    print "Elapsed(ms):", elapsed_ms