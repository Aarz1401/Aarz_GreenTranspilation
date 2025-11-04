# Time:  O(n)
# Space: O(n)

import collections
import itertools


class Solution(object):
    def findSecretWord(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        possible = range(len(wordlist))
        n = 0
        while n < 6:
            count = [collections.Counter(w[i] for w in wordlist) for i in xrange(6)]
            guess = max(possible, key=lambda x: sum(count[i][c] for i, c in enumerate(wordlist[x])))
            n = master.guess(wordlist[guess])
            possible = [j for j in possible if sum(a == b for a, b in itertools.izip(wordlist[guess], wordlist[j])) == n]


# Time:  O(n^2)
# Space: O(n)
class Solution2(object):
    def findSecretWord(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        def solve(H, possible):
            min_max_group, best_guess = possible, None
            for guess in possible:
                groups = [[] for _ in xrange(7)]
                for j in possible:
                    if j != guess:
                        groups[H[guess][j]].append(j)
                max_group = max(groups, key=len)
                if len(max_group) < len(min_max_group):
                    min_max_group, best_guess = max_group, guess
            return best_guess

        H = [[sum(a == b for a, b in itertools.izip(wordlist[i], wordlist[j]))
                  for j in xrange(len(wordlist))]
                  for i in xrange(len(wordlist))]
        possible = range(len(wordlist))
        n = 0
        while n < 6:
            guess = solve(H, possible)
            n = master.guess(wordlist[guess])
            possible = [j for j in possible if H[guess][j] == n]


# Time:  O(n^2)
# Space: O(n)
class Solution3(object):
    def findSecretWord(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        def solve(H, possible):
            min_max_group, best_guess = possible, None
            for guess in possible:
                groups = [[] for _ in xrange(7)]
                for j in possible:
                    if j != guess:
                        groups[H[guess][j]].append(j)
                max_group = groups[0]
                if len(max_group) < len(min_max_group):
                    min_max_group, best_guess = max_group, guess
            return best_guess

        H = [[sum(a == b for a, b in itertools.izip(wordlist[i], wordlist[j]))
                  for j in xrange(len(wordlist))]
                  for i in xrange(len(wordlist))]
        possible = range(len(wordlist))
        n = 0
        while n < 6:
            guess = solve(H, possible)
            n = master.guess(wordlist[guess])
            possible = [j for j in possible if H[guess][j] == n]


if __name__ == "__main__":
    # Python2 code to mirror the C++ benchmark test harness structure.

    class TestCase(object):
        def __init__(self, words, secret):
            self.words = words
            self.secret = secret

    def makeTestCases():
        # Sample test cases
        return [
            TestCase(
                words=["acckzz", "ccbazz", "eiowzz", "abcczz"],
                secret="acckzz"
            ),
            TestCase(
                words=["abcdef", "abcdee", "abzdef", "abceef", "bbcdef", "zzzdef"],
                secret="abcdee"
            ),
            TestCase(
                words=["aaaaaa", "aaaabb", "aaabba", "aabaaa", "baaaaa", "bbbbbb"],
                secret="aabaaa"
            ),
            TestCase(
                words=["silver", "simmer", "singer", "finger", "ginger", "danger"],
                secret="singer"
            ),
            TestCase(
                words=["animal", "banana", "canary", "damage", "eagerx", "fables"],
                secret="damage"
            ),
        ]

    # Generate tests
    tests = makeTestCases()

    # Optional: Master API and benchmark harness compatible with the original Python2 solution.
    class Master(object):
        def __init__(self, secret):
            self._secret = secret
            self._attempts = 0

        def guess(self, word):
            self._attempts += 1
            return sum(1 for a, b in zip(self._secret, word) if a == b)

        def attempts(self):
            return self._attempts

    # Benchmark loop (runs only if Solution is defined globally)
    if 'Solution' in globals():
        solver = Solution()
        checksum = 0

        import time
        start = time.time()

        iterations = 1000
        for _ in xrange(iterations):
            for tc in tests:
                master = Master(tc.secret)
                words = list(tc.words)  # make a modifiable copy
                solver.findSecretWord(words, master)
                checksum += master.attempts()

        end = time.time()
        elapsed_us = int((end - start) * 1e6)

        print("Checksum: %d" % checksum)
        print("Elapsed time (microseconds): %d" % elapsed_us)