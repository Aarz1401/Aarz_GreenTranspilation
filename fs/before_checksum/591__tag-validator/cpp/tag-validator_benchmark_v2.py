# Time:  O(n)
# Space: O(n)

class Solution(object):
    def isValid(self, code):
        """
        :type code: str
        :rtype: bool
        """
        def validText(s, i):
            j = i
            i = s.find("<", i)
            return i != j, i

        def validCData(s, i):
            if s.find("<![CDATA[", i) != i:
                return False, i
            j = s.find("]]>", i)
            if j == -1:
                return False, i
            return True, j+3

        def parseTagName(s, i):
            if s[i] != '<':
                return "", i
            j = s.find('>', i)
            if j == -1 or not (1 <= (j-1-i) <= 9):
                return "", i
            tag = s[i+1:j]
            for c in tag:
                if not (ord('A') <= ord(c) <= ord('Z')):
                    return "", i
            return tag, j+1

        def parseContent(s, i):
            while i < len(s):
                result, i = validText(s, i)
                if result:
                    continue
                result, i = validCData(s, i)
                if result:
                    continue
                result, i = validTag(s, i)
                if result:
                    continue
                break
            return i

        def validTag(s, i):
            tag, j = parseTagName(s, i)
            if not tag:
                return False, i
            j = parseContent(s, j)
            k = j + len(tag) + 2
            if k >= len(s) or s[j:k+1] != "</" + tag + ">":
                return False, i
            return True, k+1

        result, i = validTag(code, 0)
        return result and i == len(code)

if __name__ == "__main__":
    tests = [
        "<A></A>",
        "<A>TEXT</A>",
        "<A><![CDATA[xyz]]></A>",
        "<A><B>HELLO</B><C></C></A>",
        "<TAG><INNERA><![CDATA[<not>parsed</not>]]></INNERA><INNERB>DATA</INNERB></TAG>",
        "<ABCDEFGHI></ABCDEFGHI>",
        "<OUT>pre<B>mid</B>post</OUT>",
        "<X>t1<![CDATA[abc]]>t2<B></B>t3</X>",
        "<A><B><C><D></D></C></B></A>",
        "<ROOT>123<![CDATA[<tag>]]>456</ROOT>"
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in range(iterations):
        checksum = 0
        checksum += sol.isValid(tests[0])
        checksum += sol.isValid(tests[1])
        checksum += sol.isValid(tests[2])
        checksum += sol.isValid(tests[3])
        checksum += sol.isValid(tests[4])
        checksum += sol.isValid(tests[5])
        checksum += sol.isValid(tests[6])
        checksum += sol.isValid(tests[7])
        checksum += sol.isValid(tests[8])
        checksum += sol.isValid(tests[9])
        sink += checksum
    print(sink)

    # print sink