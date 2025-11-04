# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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
        
        parts = p.split('*')
        a = parts[0] if len(parts) > 0 else ''
        b = parts[1] if len(parts) > 1 else ''
        c = parts[2] if len(parts) > 2 else ''
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

        parts = p.split('*')
        a = parts[0] if len(parts) > 0 else ''
        b = parts[1] if len(parts) > 1 else ''
        c = parts[2] if len(parts) > 2 else ''
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ("abc", "a*b*c"),            # straightforward match
        ("abbbc", "ab*b*c"),         # multiple occurrences of middle part
        ("xbxcxd", "*b*c"),          # empty a
        ("abccba", "ab**ba"),        # empty middle part
        ("aaaaa", "aa*aa*aa"),       # impossible due to non-overlap constraint
        ("zz", "**"),                # all parts empty -> shortest 0
        ("abcde", "x*y*z"),          # no match at all
        ("xyzaaxyzb", "xy*aa*zb"),   # spaced parts
        ("cababcab", "ca*ba*b"),     # multiple choices for minimal window
        ("helloworld", "world"),     # no star in pattern
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.shortestMatchingSubstring(*test)
        else:
            sol.shortestMatchingSubstring(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.shortestMatchingSubstring(*test)
            else:
                result = sol.shortestMatchingSubstring(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
