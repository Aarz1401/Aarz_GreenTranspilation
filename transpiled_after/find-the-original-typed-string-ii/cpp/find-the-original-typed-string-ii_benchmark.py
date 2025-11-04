# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
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

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        ("", 1),
        ("a", 1),
        ("aaaaa", 3),
        ("abcde", 2),
        ("aaabbcdddde", 7),
        ("ababababab", 5),
        ("zzzzzyyyyyxxxxx", 8),
        ("q", 10),
        ("mississippi", 6),
        ("aabbccddeeffgg", 9)
    ]

    # Warm-up
    sol = Solution()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.possibleStringCount(*test)
        else:
            sol.possibleStringCount(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.possibleStringCount(*test)
            else:
                result = sol.possibleStringCount(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()