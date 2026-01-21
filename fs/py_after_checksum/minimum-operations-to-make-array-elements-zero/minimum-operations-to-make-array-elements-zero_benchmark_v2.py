# Time:  O(qlogr)
# Space: O(1)

# greedy
class Solution(object):
    def minOperations(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: int
        """
        result = 0
        for l, r in queries:
            total = 0
            base = i = 1
            while base <= r:
                nl, nr = max(l, base), min(r, 4*base-1)
                if nl <= nr:
                    total += i*(nr-nl+1)
                i += 1
                base *= 4
            result += (total+1)//2
        return result


if __name__ == "__main__":
    tests = [
        [[1, 1]],
        [[4, 4]],
        [[2, 5]],
        [[1, 16]],
        [[1, 3], [4, 7], [8, 15]],
        [[10, 100]],
        [[5, 5], [6, 20], [21, 64]],
        [[1, 1000000]],
        [[2147483600, 2147483647]],
        [[123456, 123789], [999999, 1000010]]
    ]

    sol = Solution()
    sink = 0
    iterations = 1
    for iter in range(iterations):
        checksum = 0
        for qs in tests:
            res = sol.minOperations(qs)
            checksum += int(res)
        sink += checksum
    print(sink)
    # print sink