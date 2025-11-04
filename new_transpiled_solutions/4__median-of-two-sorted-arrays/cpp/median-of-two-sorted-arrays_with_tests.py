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
    import timeit

    # Define INT_MIN and INT_MAX as in C++ 32-bit
    INT_MIN = -2147483648
    INT_MAX = 2147483647

    tests = []
    tests.append(([], [1]))
    tests.append(([], [1, 2, 3, 4]))
    tests.append(([1, 3], [2]))
    tests.append(([1, 2], [3, 4]))
    tests.append(([-5, -3, -1], [-2, 0, 2]))
    tests.append(([1, 1, 1, 1], [1, 1, 1]))
    tests.append(([INT_MIN, -1, 0, 1, INT_MAX], [-2, 2]))
    evens = []
    odds = []
    for i in xrange(100):
        evens.append(i * 2)
        odds.append(i * 2 + 1)
    tests.append((evens, odds))
    tests.append(([5], [1, 2, 3, 4, 6, 7, 8, 9, 10]))
    tests.append(([-10, -10, -5, 0, 0, 0, 5], [-7, -3, -3, 2, 4, 4, 20]))

    s = Solution()

    start = timeit.default_timer()
    checksum = 0.0
    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(len(tests)):
            checksum += s.findMedianSortedArrays(tests[i][0], tests[i][1])
    end = timeit.default_timer()

    elapsed_ms = (end - start) * 1000.0

    print "Checksum: %.6f" % checksum
    print "Elapsed time (ms): %.6f" % elapsed_ms