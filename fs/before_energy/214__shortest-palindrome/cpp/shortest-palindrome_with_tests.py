# Time:  O(n)
# Space: O(n)

# optimized from Solution2
class Solution(object):
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        def getPrefix(pattern):
            prefix = [-1] * len(pattern)
            j = -1
            for i in xrange(1, len(pattern)):
                while j > -1 and pattern[j+1] != pattern[i]:
                    j = prefix[j]
                if pattern[j+1] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix

        if not s:
            return s

        A = s + '#' + s[::-1]
        return s[getPrefix(A)[-1]+1:][::-1] + s


# Time:  O(n)
# Space: O(n)
class Solution2(object):
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        def getPrefix(pattern):
            prefix = [-1] * len(pattern)
            j = -1
            for i in xrange(1, len(pattern)):
                while j > -1 and pattern[j+1] != pattern[i]:
                    j = prefix[j]
                if pattern[j+1] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix

        if not s:
            return s

        A = s + s[::-1]
        prefix = getPrefix(A)
        i = prefix[-1]
        while i >= len(s):
            i = prefix[i]
        return s[i+1:][::-1] + s


# Time:  O(n)
# Space: O(n)
# Manacher's Algorithm
class Solution3(object):
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        def preProcess(s):
            if not s:
                return ['^', '$']
            string = ['^']
            for c in s:
                string +=  ['#', c]
            string += ['#', '$']
            return string

        string = preProcess(s)
        palindrome = [0] * len(string)
        center, right = 0, 0
        for i in xrange(1, len(string) - 1):
            i_mirror = 2 * center - i
            if right > i:
                palindrome[i] = min(right - i, palindrome[i_mirror])
            else:
                palindrome[i] = 0

            while string[i + 1 + palindrome[i]] == string[i - 1 - palindrome[i]]:
                palindrome[i] += 1

            if i + palindrome[i] > right:
                center, right = i, i + palindrome[i]

        max_len = 0
        for i in xrange(1, len(string) - 1):
            if i - palindrome[i] == 1:
                max_len = palindrome[i]
        return s[len(s)-1:max_len-1:-1] + s


if __name__ == "__main__":
    # Prepare 10 diverse test inputs
    tests = []
    
    # 1. Empty string
    tests.append("")
    
    # 2. Single character
    tests.append("a")
    
    # 3. Already a palindrome with mixed repeated chars
    tests.append("aaabaaa")
    
    # 4. No palindromic prefix beyond first char
    tests.append("abcd")
    
    # 5. Typical example from problem statements
    tests.append("aacecaaa")
    
    # 6. Classic palindrome
    tests.append("racecar")
    
    # 7. Repeated pattern not a palindrome
    tests.append("abababab")
    
    # 8. Near-palindromic odd length
    tests.append("xyzzy")
    
    # 9. Medium-long mixed sequence
    t = []
    for i in xrange(2048):
        t.append(chr(ord('a') + (i % 26)))
    tests.append(''.join(t))
    
    # 10. Long string with large palindromic prefix potential
    t = []
    for i in xrange(2000):
        t.append(chr(ord('z') - (i % 26)))
    t.append("MIXED_case_12345!")
    for i in xrange(1999, -1, -1):
        t.append(chr(ord('z') - (i % 26)))
    tests.append(''.join(t))
    
    # Benchmark harness
    import time
    sol = Solution()
    checksum = 0
    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for s in tests:
            res = sol.shortestPalindrome(s)
            checksum ^= len(res)
            if res:
                checksum ^= (ord(res[0]) & 0xFF) << 1
                checksum ^= (ord(res[-1]) & 0xFF) << 2
    end = time.time()
    elapsed_ms = (end - start) * 1000.0
    
    print "Checksum: {}".format(checksum)
    print "Elapsed time (ms): {}".format(elapsed_ms)