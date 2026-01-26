# Time:  O(log(min(m, n)))
# Space: O(1)

class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        def binary_search(left, right, check):
            while left <= right:
                mid = left+(right-left)//2
                if check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return left

        def getKth(A, B, k):
            m, n = len(A), len(B)
            if m > n:
                m, n = n, m
                A, B = B, A
            i = binary_search(max(k-n, 0), min(m, k)-1, lambda i: A[i] >= B[k-1-i])
            return max(A[i-1] if i-1 >= 0 else float("-inf"), B[k-1-i] if k-1-i >= 0 else float("-inf"))

        len1, len2 = len(nums1), len(nums2)
        if (len1+len2) % 2 == 1:
            return getKth(nums1, nums2, (len1+len2)//2+1)
        else:
            return (getKth(nums1, nums2, (len1+len2)//2)+getKth(nums1, nums2, (len1+len2)//2+1))*0.5    


# Time:  O(log(max(m, n)) * log(max_val - min_val))
# Space: O(1)
# Generic solution.
class Solution_Generic(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        def binary_search(left, right, check):
            while left <= right:
                mid = left+(right-left)//2
                if check(mid):
                    right = mid-1
                else:
                    left = mid+1
            return left

        def getKth(arrays, k):
            def check(num):
                # count the number of values which are less or equal to num
                return sum(binary_search(0, len(arr)-1, lambda x: arr[x] > num) for arr in arrays) >= k
    
            return binary_search(min(arr[0] for arr in arrays if arr), max(arr[-1] for arr in arrays if arr), check)

        array = [nums1, nums2]
        total = sum(len(nums) for nums in array)
        if total % 2 == 1:
            return getKth(array, total//2+1)
        else:
            return (getKth(array, total//2)+getKth(array, total//2+1))*0.5


if __name__ == "__main__":
    tests = [
        [[1, 3], [2]],
        [[1, 2], [3, 4]],
        [[0, 0, 0, 0], [1, 2, 3]],
        [[-5, -3, -1], [-2, 0, 2, 4]],
        [[1, 1, 1, 1, 1], [1, 1, 2, 2, 2]],
        [[-2147483647, -1000000000, 0, 1000000000, 2147483647], [-999999999, -1, 1, 999999999]],
        [[1, 3, 5, 7, 9, 11, 13, 15], [2]],
        [[10], [20]],
        [[100, 200, 300], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]],
        [[1], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]]
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for iter in xrange(iterations):
        checksum = 0
        for t in xrange(len(tests)):
            a = tests[t][0]
            b = tests[t][1]
            res = sol.findMedianSortedArrays(a, b)
            checksum += int(res)
        sink += checksum
    print(sink)