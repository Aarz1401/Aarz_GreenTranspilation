# Time:  O(rlogr + qlogr), r = max(nums)
# Space: O(r)

import collections
import bisect


# number theory, freq table, prefix sum, binary search
class Solution(object):
    def gcdValues(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        cnt1 = collections.Counter(nums)
        cnt2 = [0]*(max(nums)+1)
        for g in reversed(xrange(1, len(cnt2))):
            c = sum(cnt1[ng] for ng in xrange(g, len(cnt2), g))
            cnt2[g] = c*(c-1)//2-sum(cnt2[ng] for ng in xrange(g+g, len(cnt2), g))
        prefix = [0]*(len(cnt2)+1)
        for i in xrange(len(prefix)-1):
            prefix[i+1] = prefix[i]+cnt2[i]
        return [bisect.bisect_right(prefix, q)-1 for q in queries]


if __name__ == "__main__":
    tests = []

    # Test 1
    tests.append({
        'nums': [1, 2],
        'queries': [0]
    })

    # Test 2
    tests.append({
        'nums': [2, 4, 6],
        'queries': [0, 1, 2]
    })

    # Test 3
    tests.append({
        'nums': [2, 3, 5, 7],
        'queries': [0, 3, 5]
    })

    # Test 4
    tests.append({
        'nums': [3, 6, 9, 12],
        'queries': [0, 2, 5]
    })

    # Test 5
    tests.append({
        'nums': [1, 2, 3, 4, 5],
        'queries': [0, 4, 9]
    })

    # Test 6
    tests.append({
        'nums': [10, 10, 5, 15, 20],
        'queries': [0, 5, 9]
    })

    # Test 7
    tests.append({
        'nums': [12, 18, 24, 30, 36],
        'queries': [0, 6, 9]
    })

    # Test 8
    tests.append({
        'nums': [8, 16, 32, 3, 6],
        'queries': [0, 1, 9]
    })

    # Test 9
    tests.append({
        'nums': [14, 21, 28, 35, 42, 49],
        'queries': [0, 7, 14]
    })

    # Test 10
    tests.append({
        'nums': [4, 6, 9, 10, 15, 25],
        'queries': [0, 5, 14]
    })

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for tc in tests:
            out = sol.gcdValues(tc['nums'], tc['queries'])
            for v in out:
                checksum += v
        sink += checksum
    print(sink)

    # print sink