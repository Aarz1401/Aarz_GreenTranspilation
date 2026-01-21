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
    tests = [
        {'nums': [1], 'threshold': 1},
        {'nums': [2, 3, 5], 'threshold': 6},
        {'nums': [2, 4, 6, 8, 10], 'threshold': 10},
        {'nums': [7, 14, 21, 28, 35], 'threshold': 36},
        {'nums': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 'threshold': 10},
        {'nums': [11, 22, 33], 'threshold': 10},
        {'nums': [5, 5, 5, 5], 'threshold': 5},
        {'nums': [4, 9, 16, 25, 36], 'threshold': 40},
        {'nums': [12, 1, 6, 3, 9], 'threshold': 12},
        {'nums': [100, 50, 25, 20, 10, 5, 4, 2, 1], 'threshold': 100}
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for i in xrange(len(tests)):
            checksum += sol.countComponents(tests[i]['nums'], tests[i]['threshold'])
        sink += checksum
    print(sink)