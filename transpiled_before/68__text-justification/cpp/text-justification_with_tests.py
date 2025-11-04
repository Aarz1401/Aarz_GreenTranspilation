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
    import time

    # Define 10 diverse test inputs
    tests = []
    tests.append((["This","is","an","example","of","text","justification."], 16))
    tests.append((["a","b","c","d"], 1))
    tests.append((["helloworld"], 10))
    tests.append((["a"], 5))
    tests.append((["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], 20))
    tests.append((["a","b","c","d","e"], 2))
    tests.append(([], 5))
    tests.append((["hello","world"], 50))
    tests.append((["abcdef","g","hijkl","mn","o"], 6))
    tests.append((["a","bb","ccc","dddd","eeeee","f","gg","hhh","i","jjjjjj"], 10))

    solver = Solution()
    checksum = 0
    MASK = (1 << 64) - 1

    start = time.time()
    iterations = 1000
    for _ in range(iterations):
        for words, width in tests:
            result = solver.fullJustify(words, width)
            checksum = (checksum + len(result)) & MASK
            for line in result:
                checksum ^= len(line)
                checksum &= MASK
                for ch in line:
                    checksum = (checksum * 1315423911) & MASK
                    checksum ^= ord(ch)
                    checksum &= MASK
    end = time.time()

    elapsed = int(round((end - start) * 1000000.0))
    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed