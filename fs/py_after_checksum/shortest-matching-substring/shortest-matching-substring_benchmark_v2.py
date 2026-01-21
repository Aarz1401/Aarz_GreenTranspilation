# Time:  O(n + m)
# Space: O(n + m)

# kmp, two pointers (three pointers)
class Solution(object):
    def shortestMatchingSubstring(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: int
        """
        INF = float("inf")
        def getPrefix(pattern):
            prefix = [-1]*len(pattern)
            j = -1
            for i in xrange(1, len(pattern)):
                while j+1 > 0 and pattern[j+1] != pattern[i]:
                    j = prefix[j]
                if pattern[j+1] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix

        def KMP(text, pattern):
            if not pattern:
                for i in xrange(len(text)+1):
                    yield i
                return
            prefix = getPrefix(pattern)
            j = -1
            for i in xrange(len(text)):
                while j+1 > 0 and pattern[j+1] != text[i]:
                    j = prefix[j]
                if pattern[j+1] == text[i]:
                    j += 1
                if j+1 == len(pattern):
                    yield i-j
                    j = prefix[j]
        
        a, b, c = p.split('*')
        n = len(s)
        la, lb, lc = len(a), len(b), len(c)
        result = INF
        j = k = 0
        jt = KMP(s, b)
        kt = KMP(s, c)
        for i in KMP(s, a):
            while j != -1 and j < i+la:
                j = next(jt, -1)
            if j == -1:
                break
            while k != -1 and k < j+lb:
                k = next(kt, -1)
            if k == -1:
                break
            result = min(result, (k+lc)-i)
        return result if result != INF else -1 
            

# Time:  O(n + m)
# Space: O(n + m)
# kmp, two pointers (three pointers)
class Solution2(object):
    def shortestMatchingSubstring(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: int
        """
        INF = float("inf")
        def getPrefix(pattern):
            prefix = [-1]*len(pattern)
            j = -1
            for i in xrange(1, len(pattern)):
                while j+1 > 0 and pattern[j+1] != pattern[i]:
                    j = prefix[j]
                if pattern[j+1] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix

        a, b, c = p.split('*')
        n = len(s)
        la, lb, lc = len(a), len(b), len(c)
        prefix1 = getPrefix(a+'#'+s)
        prefix2 = getPrefix(b+'#'+s)
        prefix3 = getPrefix(c+'#'+s)
        result = INF
        i = j = k = 0
        while i+lb+lc < n:
            while i < n and prefix1[la+1+i]+1 != la:
                i += 1
            if i == n:
                break
            while j < n and not (j >= i+lb and prefix2[lb+1+j]+1 == lb):
                j += 1
            if j == n:
                break
            while k < n and not (k >= j+lc and prefix3[lc+1+k]+1 == lc):
                k += 1
            if k == n:
                break
            result = min(result, k-(i-la))
            i += 1
        return result if result != INF else -1

if __name__ == "__main__":
    tests = [
        {"s": "abcde", "p": "a*b*e"},
        {"s": "aaabbbccc", "p": "a*b*c"},
        {"s": "xxabyybczzc", "p": "ab*bc*c"},
        {"s": "ababababa", "p": "aba*bab*aba"},
        {"s": "thequickbrownfoxjumpsoverthelazydog", "p": "the*own*dog"},
        {"s": "aaaaabaaaaacaaaaad", "p": "aaa*ba*ad"},
        {"s": "cabxxabcxxabcc", "p": "ca*ab*cc"},
        {"s": "mississippi", "p": "mi*si*pi"},
        {"s": "xyzxyzxyz", "p": "xy*zz*yz"},
        {"s": "aaabaaaaaccc", "p": "aaab*aaaa*cc"}
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += sol.shortestMatchingSubstring(t["s"], t["p"])
        sink += checksum
    print(sink)
    # print sink