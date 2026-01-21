# Time:  O((m + n) * k), where m is string length, n is dictionary size, k is word length
# Space: O(n * k)

import collections


class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not words:
            return []

        result, m, n, k = [], len(s), len(words), len(words[0])
        if m < n*k:
            return result

        lookup = collections.defaultdict(int)
        for i in words:
            lookup[i] += 1                # Space: O(n * k)

        for i in xrange(k):               # Time:  O(k)
            left, count = i, 0
            tmp = collections.defaultdict(int)
            for j in xrange(i, m-k+1, k): # Time:  O(m / k)
                s1 = s[j:j+k]             # Time:  O(k)
                if s1 in lookup:
                    tmp[s1] += 1
                    count += 1
                    while tmp[s1] > lookup[s1]:
                        tmp[s[left:left+k]] -= 1
                        count -= 1
                        left += k
                    if count == n:
                        result.append(left)
                else:
                    tmp = collections.defaultdict(int)
                    count = 0
                    left = j+k
        return result


# Time:  O(m * n * k), where m is string length, n is dictionary size, k is word length
# Space: O(n * k)
class Solution2(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        result, m, n, k = [], len(s), len(words), len(words[0])
        if m < n*k:
            return result

        lookup = collections.defaultdict(int)
        for i in words:
            lookup[i] += 1                            # Space: O(n * k)

        for i in xrange(m+1-k*n):                     # Time: O(m)
            cur, j = collections.defaultdict(int), 0
            while j < n:                              # Time: O(n)
                word = s[i+j*k:i+j*k+k]               # Time: O(k)
                if word not in lookup:
                    break
                cur[word] += 1
                if cur[word] > lookup[word]:
                    break
                j += 1
            if j == n:
                result.append(i)

        return result


if __name__ == "__main__":
    import time

    # Test cases
    tests = []
    # 1) Basic example with multiple matches
    tests.append(("barfoothefoobarman", ["foo", "bar"]))
    # 2) Repeated word counts
    tests.append(("wordgoodgoodgoodbestword", ["word", "good", "best", "good"]))
    # 3) All words identical, exact fit
    tests.append(("aaaaaa", ["aa", "aa", "aa"]))
    # 4) No match because one word not present
    tests.append(("abcabcabc", ["abc", "abd"]))
    # 5) Multiple overlapping matches
    tests.append(("catdogcatdog", ["cat", "dog"]))
    # 6) Shared prefixes "aaa"
    tests.append(("aaaaaa", ["aaa", "aaa"]))
    # 7) Mixed alphanumeric and uppercase
    tests.append(("A1B2A1B2A1", ["A1", "B2", "A1"]))
    # 8) Single-character words
    tests.append(("ababaabbababa", ["a", "b", "a"]))

    # 9) Larger input with repeated pattern
    s9 = ""
    for i in range(60):
        s9 += "barfoofoobar"
    tests.append((s9, ["foo", "bar"]))

    # 10) Long words length 10 with multiple matches
    s10 = "abcdefghij" + "klmnopqrst" + "abcdefghij" + "zzzzzzzzzz" + "klmnopqrst" + "abcdefghij" + "abcdefghij"
    tests.append((s10, ["abcdefghij", "klmnopqrst", "abcdefghij"]))

    sol = Solution()
    checksum = 0
    MASK = (1 << 64) - 1

    start = time.time()

    iterations = 1
    for _ in range(iterations):
        for s, words in tests:
            res = sol.findSubstring(s, list(words))
            checksum = (checksum + len(res)) & MASK
            for idx in res:
                checksum = (checksum * 1315423911 + (idx + 1)) & MASK

    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us