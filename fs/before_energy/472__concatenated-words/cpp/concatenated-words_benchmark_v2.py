# Time:  O(n * l^2)
# Space: O(n * l)

class Solution(object):
    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        lookup = set(words)
        result = []
        for word in words:
            dp = [False] * (len(word)+1)
            dp[0] = True
            for i in xrange(len(word)):
                if not dp[i]:
                    continue

                for j in xrange(i+1, len(word)+1):
                    if j - i < len(word) and word[i:j] in lookup:
                        dp[j] = True

                if dp[len(word)]:
                    result.append(word)
                    break

        return result

if __name__ == "__main__":
    tests = [
        ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"],
        ["a","b","ab","abc","cd","abcd","ef","abcdef"],
        ["cat","dog","catdog","dogcat","catdogcat","dogcatdog","c","at","do","g","catcat"],
        ["aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","aaaaaaaaaaa"],
        ["tree","tre","e","tr","ee","treetree","trtreee","eetree","treee"],
        ["a","b","c","ab","bc","abc","abcd","bcda","cab","cabcab","abcabc"],
        ["rock","star","rockstar","super","superstar","stars","tar","ro","ck","starrock","starstar"],
        ["news","paper","newspaper","newsnews","papernews","new","sp","apers","newspapern","n"],
        ["leet","code","leetcode","le","et","co","de","leetco","decode","leetcodede","leetleetcode"],
        ["home","work","homework","frame","workframe","framework","me","or","k","framehomework"]
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for i in xrange(10):
            t = tests[i]
            res = sol.findAllConcatenatedWordsInADict(t)
            #checksum += int(len(res))
        #sink = checksum

    # print sink