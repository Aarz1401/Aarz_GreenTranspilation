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
    from timeit import default_timer as timer

    tests = [
        (["with","example","science"], "thehat"),
        (["notice","possible"], "basicbasic"),
        (["these","guess","about","garden","him"], "atomher"),
        (["a","b","c"], "abccba"),
        (["ab","bc","ca"], "abccab"),
        (["aaaa","b","c","d"], "aaaaa"),
        (["abc","abd","acd","bcd"], "abcd"),
        (["with","out","input","stickers"], "withoutstickers"),
        (["the","quick","brown","fox","jumps","over","lazy","dog"], "thequickbrownfox"),
        (["abc","def"], ""),
    ]

    sol = Solution()
    checksum = 0
    start = timer()
    iterations = 1000
    for iter in xrange(iterations):
        for i, (stickers, target) in enumerate(tests):
            res = sol.minStickers(stickers, target)
            checksum += res * (i + 1)
    end = timer()

    elapsed_ns = int((end - start) * 1e9)
    print "Checksum: " + str(checksum)
    print "Elapsed time (ns): " + str(elapsed_ns)