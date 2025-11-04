# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n + m)
# Space: O(n + m)

import collections


# kmp, two pointers, sliding window, deque, greedy
class Solution(object):
    def generateString(self, str1, str2):
        """
        :type str1: str
        :type str2: str
        :rtype: str
        """
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

        n, m = len(str1), len(str2)
        candidate = ['*']*(n+m-1)
        prefix = getPrefix(str2)
        prev = -m
        for i, x in enumerate(str1):
            if x != 'T':
                continue
            diff = i-prev
            if diff < m:
                if prefix[m-1]+1 == m-diff:
                    candidate[prev+m:i+m] = str2[m-diff:]
                else:
                    return ""
            else:
                candidate[i:i+m] = str2
            prev = i
        result = list(str2)+['#']+candidate
        idxs = []
        for i in xrange(m+1, len(result)):
            if result[i] == '*':
                result[i] = 'a'
                idxs.append(i)
        prefix = getPrefix(result)
        dq = collections.deque()
        i, j = m+1, 0
        while i-(m+1) < n:
            while dq and dq[0] < i:
                dq.popleft()
            while j < len(idxs) and idxs[j] <= i+(m-1):
                dq.append(idxs[j])
                j += 1
            if str1[i-(m+1)] == 'F' and prefix[i+(m-1)]+1 == m:
                if not dq:
                    return ""
                result[dq[-1]] = 'b'
                i += m
            else:
                i += 1
        return "".join(result[m+1:])


# Time:  O(n + m)
# Space: O(n + m)
import collections


# z-function, two pointers, sliding window, deque, greedy
class Solution2(object):
    def generateString(self, str1, str2):
        """
        :type str1: str
        :type str2: str
        :rtype: str
        """
        # Template: https://cp-algorithms.com/string/z-function.html
        def z_function(s):  # Time: O(n), Space: O(n)
            z = [0]*len(s)
            l, r = 0, 0
            for i in xrange(1, len(z)):
                if i <= r:
                    z[i] = min(r-i+1, z[i-l])
                while i+z[i] < len(z) and s[z[i]] == s[i+z[i]]:
                    z[i] += 1
                if i+z[i]-1 > r:
                    l, r = i, i+z[i]-1
            return z

        n, m = len(str1), len(str2)
        candidate = ['*']*(n+m-1)
        z = z_function(str2)
        prev = -m
        for i, x in enumerate(str1):
            if x != 'T':
                continue
            diff = i-prev
            if diff < m:
                if z[diff] == m-diff:
                    candidate[prev+m:i+m] = str2[m-diff:]
                else:
                    return ""
            else:
                candidate[i:i+m] = str2
            prev = i
        result = list(str2)+['#']+candidate
        idxs = []
        for i in xrange(m+1, len(result)):
            if result[i] == '*':
                result[i] = 'a'
                idxs.append(i)
        z = z_function(result)
        dq = collections.deque()
        i, j = m+1, 0
        while i-(m+1) < n:
            while dq and dq[0] < i:
                dq.popleft()
            while j < len(idxs) and idxs[j] <= i+(m-1):
                dq.append(idxs[j])
                j += 1
            if str1[i-(m+1)] == 'F' and z[i] == m:
                if not dq:
                    return ""
                result[dq[-1]] = 'b'
                i += m
            else:
                i += 1
        return "".join(result[m+1:])

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ("FFFFF", "ab"),       # Only F's, simple str2
        ("TT", "aba"),         # Overlap conflict -> should return ""
        ("TFTFTF", "abab"),    # Valid overlaps with alternating T/F
        ("FFFFFF", "aaa"),     # Many F's, str2 with repeats to force b-insertions
        ("FFFFF", "a"),        # m = 1, frequent matches
        ("TFFFFFTF", "xyz"),   # T's far apart, mixed F's
        ("TTTT", "abac"),      # Multiple T's with conflicting overlaps -> ""
        ("TFTT", "aaa"),       # T coverage removes wildcards; F forces dq empty -> ""
        ("F", "abcde"),        # Single F with larger m
        ("TFTF", "baba"),      # Valid overlapping pattern
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.generateString(*test)
        else:
            sol.generateString(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.generateString(*test)
            else:
                result = sol.generateString(test)
            results.append(result)

    elapsed_time = time.time() - start_time

    # Compute checksum similar to the C++ logic (64-bit operations)
    mask = (1 << 64) - 1
    checksum = 0
    for r in results:
        s = r if isinstance(r, basestring) else str(r)
        checksum = (checksum + len(s)) & mask
        if s:
            checksum ^= ord(s[0]) & 0xFF
            checksum &= mask
            checksum = (((checksum << 1) & mask) | (checksum >> 63)) & mask
            checksum ^= (ord(s[-1]) & 0xFF) << 8
            checksum &= mask

    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()