# Time:  O(n + k^2)
# Space: O(n + k)

# dp, prefix sum
class Solution(object):
    def possibleStringCount(self, word, k):
        MOD = 10**9+7
        cnt = [0]
        for i in xrange(len(word)):
            cnt[-1] += 1
            if i+1 == len(word) or word[i+1] != word[i]:
                cnt.append(0)
        cnt.pop()
        result = reduce(lambda accu, x: accu*x%MOD, cnt, 1)
        if k <= len(cnt):
            return result
        dp = [0]*(k-len(cnt))
        dp[0] = 1
        for l in cnt:
            for i in xrange(len(dp)-1):
                dp[i+1] = (dp[i+1]+dp[i])%MOD
            for i in reversed(xrange(l, len(dp))):
                dp[i] = (dp[i]-dp[i-l])%MOD
        return reduce(lambda accu, x: (accu-x)%MOD, dp, result)

if __name__ == "__main__":
    tests = [
        ("a", 1),
        ("aaab", 3),
        ("abc", 3),
        ("aabbcc", 5),
        ("ababab", 4),
        ("zzzzzzzzzz", 7),
        ("mississippi", 10),
        ("qwertyuiopasdfghjkl", 20),
        ("aaaabbbbccccddddeeee", 2),
        ("b", 100)
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for tc in tests:
            checksum ^= sol.possibleStringCount(tc[0], tc[1])
        sink += checksum
    print(sink)

    # print sink