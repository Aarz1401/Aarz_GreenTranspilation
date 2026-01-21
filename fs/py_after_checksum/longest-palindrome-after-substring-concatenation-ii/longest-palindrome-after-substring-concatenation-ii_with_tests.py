
# Time:  O(n * m)
# Space: O(n + m)

# manacher's algorithm, dp
class Solution(object):
    def longestPalindrome(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        def manacher(s):
            s = '^#' + '#'.join(s) + '#$'
            P = [0]*len(s)
            C, R = 0, 0
            for i in xrange(1, len(s)-1):
                i_mirror = 2*C-i
                if R > i:
                    P[i] = min(R-i, P[i_mirror])
                while s[i+1+P[i]] == s[i-1-P[i]]:
                    P[i] += 1
                if i+P[i] > R:
                    C, R = i, i+P[i]
            return P

        def longest_palindrome(s):
            result = [0]*(len(s)+1)
            P = manacher(s)
            for i in xrange(1, len(P)-1):
                result[(i-P[i])//2] = P[i]
            return result

        t = t[::-1]
        p1 = longest_palindrome(s)
        p2 = longest_palindrome(t)
        result = 0
        dp = [[0]*(len(t)+1) for _ in xrange(len(s)+1)]
        for i in xrange(len(s)):
            for j in xrange(len(t)):
                dp[i+1][j+1] = dp[i][j]+2 if s[i] == t[j] else 0
                result = max(result, dp[i+1][j+1]+max(p1[i+int(s[i] == t[j])] , p2[j+int(s[i] == t[j])]))
        return result


if __name__ == "__main__":
    from timeit import default_timer as timer

    tests = []

    # 1. Both empty
    tests.append(("", ""))

    # 2. One empty, one single character
    tests.append(("a", ""))

    # 3. No common characters
    tests.append(("abc", "def"))

    # 4. Both palindromic
    tests.append(("abba", "abba"))

    # 5. Same single repeated character, different lengths
    tests.append(("a" * 120, "a" * 110))

    # 6. Alphabet repeated vs reverse alphabet repeated
    a = "abcdefghijklmnopqrstuvwxyz"
    ar = a[::-1]
    s = a * 3
    t = ar * 3
    tests.append((s, t))

    # 7. Embedded palindrome vs another palindrome
    tests.append(("xyzracecarxyz", "abcdefgfedcba"))

    # 8. Deterministic pseudo-random-like sequences
    s = []
    for i in range(100):
        s.append(chr(ord('a') + (i * 7) % 26))
    s = "".join(s)
    t = []
    for i in range(120):
        t.append(chr(ord('a') + (i * 11) % 26))
    t = "".join(t)
    tests.append((s, t))

    # 9. Alternating characters
    s = "ab" * 60
    t = "ba" * 60
    tests.append((s, t))

    # 10. Digits repeated vs reversed digits repeated
    s = "0123456789" * 10
    t = "9876543210" * 8
    tests.append((s, t))

    sol = Solution()
    checksum = 0

    start = timer()

    iterations = 1
    for iter in range(iterations):
        for tc in tests:
            checksum += sol.longestPalindrome(tc[0], tc[1])

    end = timer()
    elapsed = int((end - start) * 1000)

    print "Checksum: %d" % checksum
    print "Elapsed time: %d ms" % elapsed
