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
    tests = [
        {"s": "barfoothefoobarman", "words": ["foo", "bar"]},
        {"s": "wordgoodgoodgoodbestword", "words": ["word", "good", "best", "word"]},
        {"s": "barfoofoobarthefoobarman", "words": ["bar", "foo", "the"]},
        {"s": "lingmindraboofooowingdingbarrwingmonkeypoundcake", "words": ["fooo", "barr", "wing", "ding", "wing"]},
        {"s": "aaaaaa", "words": ["aa", "aa", "aa"]},
        {"s": "abababab", "words": ["ab", "ba", "ab"]},
        {"s": "abcabcabc", "words": ["a", "b", "c"]},
        {"s": "catcatdogcatdog", "words": ["cat", "dog", "cat"]},
        {"s": "short", "words": ["longg", "words"]},
        {"s": "foobarfoobar", "words": ["foo", "bar", "foo"]},
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for t in tests:
            r = sol.findSubstring(t["s"], t["words"])
            checksum += int(len(r))
        sink += checksum
    print(sink)
    # print sink