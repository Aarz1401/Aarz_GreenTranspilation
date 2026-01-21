# Time:  O(n + tlogt), t = threshold
# Space: O(t)

# union find, number theory
class UnionFind(object):  # Time: O(n * alpha(n)), Space: O(n)
    def __init__(self, n):
        self.set = range(n)
        self.rank = [0]*n

    def find_set(self, x):
        stk = []
        while self.set[x] != x:  # path compression
            stk.append(x)
            x = self.set[x]
        while stk:
            self.set[stk.pop()] = x
        return x

    def union_set(self, x, y):
        x, y = self.find_set(x), self.find_set(y)
        if x == y:
            return False
        if self.rank[x] > self.rank[y]:  # union by rank
            x, y = y, x
        self.set[x] = self.set[y]
        if self.rank[x] == self.rank[y]:
            self.rank[y] += 1
        return True


class Solution(object):
    def countComponents(self, nums, threshold):
        """
        :type nums: List[int]
        :type threshold: int
        :rtype: int
        """
        uf = UnionFind(threshold)
        lookup = [-1]*threshold
        result = len(nums)
        for x in nums:
            if x-1 >= threshold:
                continue
            for i in xrange(x, threshold+1, x):
                if lookup[i-1] == -1:
                    lookup[i-1] = x-1
                    continue
                if uf.union_set(lookup[i-1], x-1):
                    result -= 1
                if i == x:
                    break
        return result


# Time:  O(n + tlogt), t = threshold
# Space: O(t)
# union find, number theory
class Solution2(object):
    def countComponents(self, nums, threshold):
        """
        :type nums: List[int]
        :type threshold: int
        :rtype: int
        """
        uf = UnionFind(threshold)
        lookup = [-1]*threshold
        for x in nums:
            if x-1 >= threshold:
                continue
            for i in xrange(x+x, threshold+1, x):
                uf.union_set(i-1, x-1)
        return sum(x-1 >= threshold or uf.find_set(x-1) == x-1 for x in nums)


if __name__ == "__main__":
    import sys
    import timeit

    # Define 10 diverse test inputs
    testNums = [
        [1],                                           # small, threshold = 1
        [2, 3, 4, 9, 6],                               # mixed small numbers
        [5, 5, 5, 5, 5],                               # duplicates
        [100, 200, 300],                               # all > threshold
        [1, 2, 3, 4, 5, 6],                            # consecutive
        [2, 3, 5, 7, 11, 13],                          # primes
        [4, 8, 12, 16, 20, 24, 28, 32],                # multiples
        [1, 2, 3],                                     # threshold = 0 edge
        [10000, 9999, 5000, 2500, 1250, 1, 2, 4, 8, 16], # large threshold mix
        []                                             # empty nums
    ]
    thresholds = [
        1,     # for test 1
        10,    # for test 2
        5,     # for test 3
        50,    # for test 4
        6,     # for test 5
        15,    # for test 6
        32,    # for test 7
        0,     # for test 8
        10000, # for test 9
        100    # for test 10
    ]

    # Check we have exactly 10 test inputs
    if len(testNums) != 10 or len(thresholds) != 10:
        sys.stderr.write("Error: Need exactly 10 test inputs.\n")
        sys.exit(1)

    checksum = 0

    start = timeit.default_timer()

    iterations = 1000
    for iter in xrange(iterations):
        sol = Solution()
        for i in xrange(len(testNums)):
            checksum += sol.countComponents(testNums[i], thresholds[i])

    end = timeit.default_timer()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum:", checksum
    print "Elapsed time (ns):", elapsed_ns