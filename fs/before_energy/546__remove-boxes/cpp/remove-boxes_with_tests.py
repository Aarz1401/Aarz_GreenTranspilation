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
    import time

    # Define 10 diverse test inputs
    tests = []
    tests.append([])  # empty
    tests.append([7])  # single element
    tests.append([1, 2])  # two different
    tests.append([1, 1, 1, 1, 1])  # all same
    tests.append([1, 2, 3, 4, 5, 6])  # all distinct, increasing
    tests.append([1, 1, 2, 2, 3, 3, 4, 4])  # pairs
    tests.append([1, 2, 2, 2, 1])  # merge same ends via middle block
    tests.append([3, 3, 2, 1, 2, 3, 3])  # symmetric groups with merges
    tests.append([1, 2, 1, 2, 1, 2, 1])  # alternating
    tests.append([1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 1, 1])  # larger mixed groups

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1000
    for _ in xrange(iterations):
        for t in tests:
            result = sol.removeBoxes(t[:])
            checksum += int(result)
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us