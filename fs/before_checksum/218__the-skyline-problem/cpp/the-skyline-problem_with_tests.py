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
    import time

    # Define 10 diverse test inputs
    datasets = []

    # 1) Empty input
    datasets.append([])

    # 2) Single building
    datasets.append([
        [2, 9, 10]
    ])

    # 3) Disjoint non-overlapping buildings
    datasets.append([
        [1, 2, 1],
        [3, 4, 2],
        [6, 7, 3]
    ])

    # 4) Fully nested overlaps with increasing heights
    datasets.append([
        [1, 10, 3],
        [2, 9, 5],
        [3, 8, 7]
    ])

    # 5) Touching endpoints with same heights
    datasets.append([
        [1, 3, 3],
        [3, 5, 3],
        [5, 7, 3]
    ])

    # 6) Partial overlaps with same heights
    datasets.append([
        [1, 5, 3],
        [2, 6, 3],
        [4, 8, 3]
    ])

    # 7) Overlapping chain with ascending heights
    datasets.append([
        [1, 3, 1],
        [2, 4, 2],
        [3, 5, 3],
        [4, 6, 4]
    ])

    # 8) Overlapping chain with descending heights
    datasets.append([
        [1, 5, 4],
        [2, 6, 3],
        [3, 7, 2],
        [4, 8, 1]
    ])

    # 9) Large coordinates and mixed overlaps
    datasets.append([
        [100000, 200000, 100],
        [150000, 250000, 120],
        [300000, 400000, 80],
        [400000, 500000, 200]
    ])

    # 10) Complex mixed case
    datasets.append([
        [0, 2, 3],
        [1, 4, 4],
        [2, 3, 5],
        [6, 7, 2],
        [7, 8, 4],
        [8, 9, 1],
        [9, 12, 3],
        [10, 11, 6]
    ])

    sol = Solution()

    checksum = 0
    MASK = (1 << 64) - 1
    CONST = 1315423911
    XOR_CONST = 0x9e3779b97f4a7c15

    t_start = time.time()

    iterations = 1
    for iter in range(iterations):
        for ds in datasets:
            buildings = [b[:] for b in ds]
            res = sol.getSkyline(buildings)
            for p in res:
                checksum = (checksum * CONST) & MASK
                checksum = (checksum + (int(p[0]) * 733 + int(p[1]))) & MASK
            checksum = (checksum ^ ((len(res) + XOR_CONST) & MASK)) & MASK

    t_end = time.time()
    elapsed_ns = int((t_end - t_start) * 1000000000.0)

    print "Checksum: " + str(checksum)
    print "Elapsed time (ns): " + str(elapsed_ns)