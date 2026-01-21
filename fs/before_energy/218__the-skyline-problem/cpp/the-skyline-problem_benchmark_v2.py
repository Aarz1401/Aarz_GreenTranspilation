# Time:  O(nlogn)
# Space: O(n)

start, end, height = 0, 1, 2
class Solution(object):
    # @param {integer[][]} buildings
    # @return {integer[][]}
    def getSkyline(self, buildings):
        intervals = self.ComputeSkylineInInterval(buildings, 0, len(buildings))

        res = []
        last_end = -1
        for interval in intervals:
            if last_end != -1 and last_end < interval[start]:
                res.append([last_end, 0])
            res.append([interval[start], interval[height]])
            last_end = interval[end]
        if last_end != -1:
            res.append([last_end, 0])

        return res

    # Divide and Conquer.
    def ComputeSkylineInInterval(self, buildings, left_endpoint, right_endpoint):
        if right_endpoint - left_endpoint <= 1:
            return buildings[left_endpoint:right_endpoint]
        mid = left_endpoint + ((right_endpoint - left_endpoint) / 2)
        left_skyline = self.ComputeSkylineInInterval(buildings, left_endpoint, mid)
        right_skyline = self.ComputeSkylineInInterval(buildings, mid, right_endpoint)
        return self.MergeSkylines(left_skyline, right_skyline)

    # Merge Sort.
    def MergeSkylines(self, left_skyline, right_skyline):
        i, j = 0, 0
        merged = []

        while i < len(left_skyline) and j < len(right_skyline):
            if left_skyline[i][end] < right_skyline[j][start]:
                merged.append(left_skyline[i])
                i += 1
            elif right_skyline[j][end] < left_skyline[i][start]:
                merged.append(right_skyline[j])
                j += 1
            elif left_skyline[i][start] <= right_skyline[j][start]:
                i, j = self.MergeIntersectSkylines(merged, left_skyline[i], i,\
                                                   right_skyline[j], j)
            else: # left_skyline[i][start] > right_skyline[j][start].
                j, i = self.MergeIntersectSkylines(merged, right_skyline[j], j, \
                                                   left_skyline[i], i)

        # Insert the remaining skylines.
        merged += left_skyline[i:]
        merged += right_skyline[j:]
        return merged

    # a[start] <= b[start]
    def MergeIntersectSkylines(self, merged, a, a_idx, b, b_idx):
        if a[end] <= b[end]:
            if a[height] > b[height]:   # |aaa|
                if b[end] != a[end]:    # |abb|b
                    b[start] = a[end]
                    merged.append(a)
                    a_idx += 1
                else:             # aaa
                    b_idx += 1    # abb
            elif a[height] == b[height]:  # abb
                b[start] = a[start]       # abb
                a_idx += 1
            else:  # a[height] < b[height].
                if a[start] != b[start]:                            #    bb
                    merged.append([a[start], b[start], a[height]])  # |a|bb
                a_idx += 1
        else:  # a[end] > b[end].
            if a[height] >= b[height]:  # aaaa
                b_idx += 1              # abba
            else:
                #    |bb|
                # |a||bb|a
                if a[start] != b[start]:
                    merged.append([a[start], b[start], a[height]])
                a[start] = b[end]
                merged.append(b)
                b_idx += 1
        return a_idx, b_idx

if __name__ == "__main__":
    tests = [
        [[2, 9, 10]],
        [[1, 2, 1], [3, 4, 2]],
        [[2, 6, 4], [4, 8, 6]],
        [[1, 3, 4], [3, 5, 4], [5, 8, 4]],
        [[1, 4, 5], [2, 6, 7], [5, 8, 6], [7, 9, 4], [3, 5, 8]],
        [[1, 2, 1], [2, 3, 2], [3, 4, 3], [4, 5, 4], [5, 6, 5]],
        [[1, 10, 5], [1, 7, 9], [1, 3, 8], [1, 5, 3]],
        [[50, 120, 5], [100, 200, 10], [150, 250, 20], [240, 300, 15], [310, 320, 10]],
        [[1, 2, 3], [2, 4, 3], [3, 5, 2], [4, 6, 4], [5, 7, 3], [6, 8, 5]],
        [[1, 2, 1], [10, 12, 2], [20, 25, 3], [30, 40, 1]]
    ]

    sol = Solution()
    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for buildings in tests:
            res = sol.getSkyline([b[:] for b in buildings])
            #checksum += int(len(res))
        #sink = checksum
    # print sink