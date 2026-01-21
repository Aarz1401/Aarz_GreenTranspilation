# Time:  O(nlogn)
# Space: O(n)

class Solution(object):
    def intersectionSizeTwo(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key = lambda s_e: (s_e[0], -s_e[1]))
        cnts = [2] * len(intervals)
        result = 0
        while intervals:
            (start, _), cnt = intervals.pop(), cnts.pop()
            for s in xrange(start, start+cnt):
                for i in xrange(len(intervals)):
                    if cnts[i] and s <= intervals[i][1]:
                        cnts[i] -= 1
            result += cnt
        return result

if __name__ == "__main__":
    tests = [
        [[1,3],[1,4],[2,5],[3,5]],
        [[1,2],[4,5],[7,8]],
        [[0,10],[0,9],[1,8],[2,7],[3,6],[4,5]],
        [[5,10]],
        [[1,2],[2,3],[3,4],[4,5]],
        [[10,20],[15,25],[18,22],[21,30],[5,12],[0,3]],
        [[1000000,1000002],[999998,1000001],[500000,700000]],
        [[2,6],[2,7],[2,8],[3,9],[0,5]],
        [[0,1],[1,2],[2,3],[3,4],[4,6],[5,7],[6,8]],
        [[8,10],[1,3],[2,5],[6,9],[4,7],[0,2]]
    ]

    sol = Solution()
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            in_list = [pair[:] for pair in t]
            r = sol.intersectionSizeTwo(in_list)
        #sink = checksum