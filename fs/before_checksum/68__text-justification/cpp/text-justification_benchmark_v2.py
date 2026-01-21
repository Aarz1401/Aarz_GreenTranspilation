# Time:  O(n)
# Space: O(k), k is maxWidth.

class Solution(object):
    def fullJustify(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        def addSpaces(i, spaceCnt, maxWidth, is_last):
            if i < spaceCnt:
                # For the last line of text, it should be left justified,
                # and no extra space is inserted between words.
                return 1 if is_last else (maxWidth // spaceCnt) + int(i < maxWidth % spaceCnt)
            return 0

        def connect(words, maxWidth, begin, end, length, is_last):
            s = []  # The extra space O(k) is spent here.
            n = end - begin
            for i in xrange(n):
                s += words[begin + i],
                s += ' ' * addSpaces(i, n - 1, maxWidth - length, is_last),
            # For only one word in a line.
            line = "".join(s)
            if len(line) < maxWidth:
                line += ' ' * (maxWidth - len(line))
            return line

        res = []
        begin, length = 0, 0
        for i in xrange(len(words)):
            if length + len(words[i]) + (i - begin) > maxWidth:
                res += connect(words, maxWidth, begin, i, length, False),
                begin, length = i, 0
            length += len(words[i])

        # Last line.
        res += connect(words, maxWidth, begin, len(words), length, True),
        return res

if __name__ == "__main__":
    tests = [
        (["Hello"], 5),
        (["Hi"], 4),
        (["This","is","an","example","of","text","justify"], 16),
        (["a","b","c"], 6),
        (["lorem","ipsum","dolor","sit","amet","consect","adipis"], 14),
        (["a","group","of","words","to","fill","the","last","line"], 12),
        (["aa","bb","cc","dd"], 11),
        (["a","b","c","d"], 1),
        (["longword","tiny","mid","size","words","here"], 10),
        (["abc","def","ghi"], 11)
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for words, width in tests:
            res = sol.fullJustify(list(words), width)
            for line in res:
                checksum += len(line)
                checksum += ord(line[0])
                checksum += ord(line[-1])
            sink += checksum
    print(sink)