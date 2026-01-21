
# Time:  O(l * nlogn)
# Space: O(n)

# sort, sliding window, prefix sum
class Solution(object):
    def longestCommonPrefix(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[int]
        """
        idxs = range(len(words))
        idxs.sort(key=lambda x: words[x])
        def longest_common_prefix(k):
            lcp = [0]*len(words)
            for i in xrange(len(words)-(k-1)):
                left = words[idxs[i]]
                right = words[idxs[i+(k-1)]]
                l = min(len(left), len(right))
                lcp[i] = next((j for j in xrange(l) if left[j] != right[j]), l)
            return lcp
        
        lcp = longest_common_prefix(k)
        prefix = [0]*len(words)
        prefix[0] = lcp[0]
        for i in xrange(len(prefix)-1):
            prefix[i+1] = max(prefix[i], lcp[i+1])
        suffix = [0]*len(words)
        suffix[-1] = lcp[-1]
        for i in reversed(xrange(len(suffix)-1)):
            suffix[i] = max(suffix[i+1], lcp[i])
        result = [0]*len(words)
        mx = max(longest_common_prefix(k+1))
        for i in xrange(len(words)):
            idx = idxs[i]
            mx1 = prefix[i-k] if i-k >= 0 else 0
            mx2 = suffix[i+1] if i+1 < len(words) else 0
            result[idx] = max(mx, mx1, mx2)
        return result
        

# Time:  O(n * l)
# Space: O(t)
# trie
class Solution2(object):
    def longestCommonPrefix(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[int]
        """
        class Trie(object):
            def __init__(self):
                self.__root = self.__new_node()
            
            def __new_node(self):
                return {"cnt":0, "max":0}

            def update(self, w, d, k):
                path = [None]*(len(w)+1)
                path[0] = curr = self.__root
                for i, x in enumerate(w, 1):
                    if x not in curr:
                        curr[x] = self.__new_node()
                    path[i] = curr = curr[x]
                for i in reversed(xrange(len(path))):
                    curr = path[i]
                    curr["cnt"] += d
                    curr["max"] = i if curr["cnt"] >= k else 0
                    for x in curr.iterkeys():
                        if len(x) == 1:
                            curr["max"] = max(curr["max"], curr[x]["max"])

            def query(self):
                return self.__root["max"]
        

        trie = Trie()
        for w in words:
            trie.update(w, +1, k)
        result = [0]*len(words)
        for i in xrange(len(words)):
            trie.update(words[i], -1, k)
            result[i] = trie.query()
            trie.update(words[i], +1, k)
        return result


# Time:  O(n * l)
# Space: O(t)
# trie
class Solution_TLE(object):
    def longestCommonPrefix(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[int]
        """
        class Trie(object):
            def __init__(self):
                self.__nodes = []
                self.__cnt = []
                self.__mx = []
                self.__new_node()
            
            def __new_node(self):
                self.__nodes.append([-1]*26)
                self.__cnt.append(0)
                self.__mx.append(0)
                return len(self.__nodes)-1

            def update(self, w, d, k):
                path = [-1]*(len(w)+1)
                path[0] = curr = 0
                for i, c in enumerate(w, 1):
                    x = ord(c)-ord('a')
                    if self.__nodes[curr][x] == -1:
                        self.__nodes[curr][x] = self.__new_node()
                    path[i] = curr = self.__nodes[curr][x]
                for i in reversed(xrange(len(path))):
                    curr = path[i]
                    self.__cnt[curr] += d
                    self.__mx[curr] = i if self.__cnt[curr] >= k else 0
                    for x in xrange(len(self.__nodes[curr])):
                        if self.__nodes[curr][x] != -1:
                            self.__mx[curr]= max(self.__mx[curr], self.__mx[self.__nodes[curr][x]])

            def query(self):
                return self.__mx[0]
        

        result = [0]*len(words)
        trie = Trie()
        for w in words:
            trie.update(w, +1, k)
        for i in xrange(len(words)):
            trie.update(words[i], -1, k)
            result[i] = trie.query()
            trie.update(words[i], +1, k)
        return result


if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs
    tests = []

    # 1. Empty list
    tests.append(([], 1))

    # 2. Single word
    tests.append((["hello"], 1))

    # 3. All same words
    tests.append((["aaa", "aaa", "aaa", "aaa"], 2))

    # 4. No common prefixes
    tests.append((["dog", "cat", "bird", "fish"], 2))

    # 5. Common prefixes among many
    tests.append((["interview", "interval", "internal", "internet"], 3))

    # 6. k equals n
    tests.append((["alpha", "alpine", "altar", "altruist", "algebra"], 5))

    # 7. k greater than n
    tests.append((["abc", "abd"], 3))

    # 8. Chain of prefixes
    tests.append((["a", "ab", "abc", "abcd", "abcde"], 4))

    # 9. Case sensitivity and ordering
    tests.append((["Apple", "application", "app", "App", "apply"], 2))

    # 10. Long strings
    x1000 = "x" * 1000
    a = x1000 + "a"
    b = x1000 + "b"
    c = ("x" * 999) + "y"
    d = "z" * 1000
    tests.append(([a, b, c, d], 2))

    sol = Solution()
    sol2 = Solution2()
    checksum = 0

    start = time.time()

    iterations = 1
    for iter in xrange(iterations):
        for t in tests:
            words, k = t
            try:
                res = sol.longestCommonPrefix(words, k)
            except Exception:
                res = sol2.longestCommonPrefix(words, k)
            for v in res:
                checksum += v
            checksum += len(words) * 131 + k

    end = time.time()
    duration_ns = int((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % duration_ns
