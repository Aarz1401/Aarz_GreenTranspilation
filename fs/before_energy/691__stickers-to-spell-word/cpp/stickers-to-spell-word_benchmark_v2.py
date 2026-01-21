# Time:  O(T * S^T)
# Space: O(T * S^T)

import collections


class Solution(object):
    def minStickers(self, stickers, target):
        """
        :type stickers: List[str]
        :type target: str
        :rtype: int
        """
        def minStickersHelper(sticker_counts, target, dp):
            if "".join(target) in dp:
                return dp["".join(target)]
            target_count = collections.Counter(target)
            result = float("inf")
            for sticker_count in sticker_counts:
                if sticker_count[target[0]] == 0:
                    continue
                new_target = []
                for k in target_count.keys():
                    if target_count[k] > sticker_count[k]:
                       new_target += [k]*(target_count[k] - sticker_count[k])
                if len(new_target) != len(target):
                    num = minStickersHelper(sticker_counts, new_target, dp)
                    if num != -1:
                        result = min(result, 1+num)
            dp["".join(target)] = -1 if result == float("inf") else result
            return dp["".join(target)]

        sticker_counts = map(collections.Counter, stickers)
        dp = { "":0 }
        return minStickersHelper(sticker_counts, target, dp)


if __name__ == "__main__":
    tests = []
    tests.append({'stickers': ["with", "example", "science"], 'target': "thehat"})
    tests.append({'stickers': ["notice", "possible"], 'target': "basicbasic"})
    tests.append({'stickers': ["these", "guess", "about", "garden", "him"], 'target': "atomher"})
    tests.append({'stickers': ["travel", "broadcast", "player", "game"], 'target': "goal"})
    tests.append({'stickers': ["aaaa", "bbbb", "cc", "dd"], 'target': "abcd"})
    tests.append({'stickers': ["ab", "bc", "cd"], 'target': "abcd"})
    tests.append({'stickers': ["ab", "ab", "ab"], 'target': "aabb"})
    tests.append({'stickers': ["hello", "world", "leetcode"], 'target': "hold"})
    tests.append({'stickers': ["abc", "abd", "cde", "def"], 'target': "feed"})
    tests.append({'stickers': ["letter", "collection", "stickers", "random", "words", "for", "testing"], 'target': "score"})

    sink = 0
    sol = Solution()

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for tc in tests:
            res = sol.minStickers(list(tc['stickers']), tc['target'])
            #checksum += res
        #sink = checksum

    # print sink