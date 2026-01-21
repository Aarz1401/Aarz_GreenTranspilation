# Time:  O(nlogn + nlogk) = O(nlogn), k is the length of the result.
# Space: O(1)

class Solution(object):
    def maxEnvelopes(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        def insert(target):
            left, right = 0, len(result) - 1
            while left <= right:
                mid = left + (right - left) / 2
                if result[mid] >= target:
                    right = mid - 1
                else:
                    left = mid + 1
            if left == len(result):
                result.append(target)
            else:
                result[left] = target

        result = []

        envelopes.sort(lambda x, y: y[1] - x[1] if x[0] == y[0] else \
                                    x[0] - y[0])
        for envelope in envelopes:
            insert(envelope[1])

        return len(result)

if __name__ == "__main__":
    sol = Solution()
    tests = [
        [[1,1]],
        [[5,4],[6,4],[6,7],[2,3]],
        [[1,10],[1,9],[1,8],[1,7]],
        [[4,5],[4,6],[6,7],[2,3],[1,1],[7,8]],
        [[8,9],[5,6],[6,7],[2,3],[3,4]],
        [[2,100],[3,200],[4,300],[5,500],[5,400],[5,250],[6,370],[6,360],[7,380]],
        [[10,10],[9,9],[8,8],[7,7],[6,6]],
        [[1,2],[2,2],[3,2],[4,2]],
        [[10000,10000],[9999,10001],[10001,9999],[10002,10002]],
        [[2,2],[3,3],[3,2],[4,3],[5,5],[5,4],[6,7],[7,6]]
    ]

    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for t in tests:
            input = [x[:] for x in t]
            r = sol.maxEnvelopes(input)
        #sink = checksum