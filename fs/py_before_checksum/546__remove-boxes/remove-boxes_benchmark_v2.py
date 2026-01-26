# Time:  O(n^3) ~ O(n^4)
# Space: O(n^3)

class Solution(object):
    def removeBoxes(self, boxes):
        """
        :type boxes: List[int]
        :rtype: int
        """
        def dfs(boxes, l, r, k, lookup):
            if l > r: return 0
            if lookup[l][r][k]: return lookup[l][r][k]

            ll, kk = l, k
            while l < r and boxes[l+1] == boxes[l]:
                l += 1
                k += 1
            result = dfs(boxes, l+1, r, 0, lookup) + (k+1) ** 2
            for i in xrange(l+1, r+1):
                if boxes[i] == boxes[l]:
                    result = max(result, dfs(boxes, l+1, i-1, 0, lookup) + dfs(boxes, i, r, k+1, lookup))
            lookup[ll][r][kk] = result
            return result

        lookup = [[[0]*len(boxes) for _ in xrange(len(boxes)) ] for _ in xrange(len(boxes)) ]
        return dfs(boxes, 0, len(boxes)-1, 0, lookup)

if __name__ == "__main__":
    tests = [
        [1],
        [2, 2],
        [1, 2],
        [1, 2, 3],
        [5, 5, 5],
        [1, 3, 1],
        [1, 1, 2, 2, 1],
        [1, 2, 2, 2, 1],
        [1, 3, 2, 2, 3, 1],
        [2, 2, 1, 3, 3, 1, 2]
    ]

    sink = 0
    sol = Solution()

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in tests:
            checksum += sol.removeBoxes(list(t))
        sink += checksum
    print(sink)