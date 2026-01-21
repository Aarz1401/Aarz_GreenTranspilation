# Time:  O(nlogk)
# Space: O(1)

class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

    def __repr__(self):		
        if self:		
            return "{} -> {}".format(self.val, self.next)


# Merge two by two solution.
class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        def mergeTwoLists(l1, l2):
            curr = dummy = ListNode(0)
            while l1 and l2:
                if l1.val < l2.val:
                    curr.next = l1
                    l1 = l1.next
                else:
                    curr.next = l2
                    l2 = l2.next
                curr = curr.next
            curr.next = l1 or l2
            return dummy.next

        if not lists:
            return None
        left, right = 0, len(lists) - 1
        while right > 0:
            lists[left] = mergeTwoLists(lists[left], lists[right])
            left += 1
            right -= 1
            if left >= right:
                left = 0
        return lists[0]


# Time:  O(nlogk)
# Space: O(logk)
# Divide and Conquer solution.
class Solution2(object):
    # @param a list of ListNode
    # @return a ListNode
    def mergeKLists(self, lists):
        def mergeTwoLists(l1, l2):
            curr = dummy = ListNode(0)
            while l1 and l2:
                if l1.val < l2.val:
                    curr.next = l1
                    l1 = l1.next
                else:
                    curr.next = l2
                    l2 = l2.next
                curr = curr.next
            curr.next = l1 or l2
            return dummy.next

        def mergeKListsHelper(lists, begin, end):
            if begin > end:
                return None
            if begin == end:
                return lists[begin]
            return mergeTwoLists(mergeKListsHelper(lists, begin, (begin + end) / 2), \
                                 mergeKListsHelper(lists, (begin + end) / 2 + 1, end))

        return mergeKListsHelper(lists, 0, len(lists) - 1)


# Time:  O(nlogk)
# Space: O(k)
# Heap solution.
import heapq
class Solution3(object):
    # @param a list of ListNode
    # @return a ListNode
    def mergeKLists(self, lists):
        dummy = ListNode(0)
        current = dummy

        heap = []
        for sorted_list in lists:
            if sorted_list:
                heapq.heappush(heap, (sorted_list.val, sorted_list))

        while heap:
            smallest = heapq.heappop(heap)[1]
            current.next = smallest
            current = current.next
            if smallest.next:
                heapq.heappush(heap, (smallest.next.val, smallest.next))

        return dummy.next


if __name__ == "__main__":
    import time

    def buildLists(vv):
        heads = []
        for arr in vv:
            if not arr:
                heads.append(None)
                continue
            dummy = ListNode(0)
            p = dummy
            for x in arr:
                node = ListNode(x)
                p.next = node
                p = node
            heads.append(dummy.next)
        return heads

    def freeList(node):
        while node is not None:
            nxt = node.next
            node.next = None
            node = nxt

    tests = []

    # 1. No lists
    tests.append([])
    # 2. Single empty list
    tests.append([[]])
    # 3. Multiple empty lists
    tests.append([[], [], []])
    # 4. Single sorted list
    tests.append([[1, 2, 3, 4]])
    # 5. Mixed positive lists (classic sample)
    tests.append([[1, 4, 5], [1, 3, 4], [2, 6]])
    # 6. Negative and positive numbers
    tests.append([[-10, -5, 0], [-6, -3, 2, 9], [-7, -3, 0, 1]])
    # 7. Varying lengths and empties
    tests.append([[5], [], [1,2,3,4,5,6,7,8,9,10], [2,2,2,2,2], [1000]])
    # 8. Heavy duplicates
    tests.append([[1,1,1,1], [1,1,1], [1,1], [1]])
    # 9. Many small single-node lists
    tests.append([[0],[-1],[-2],[-3],[-4],[-5],[-6],[-7],[-8],[-9]])
    # 10. Larger case: 5 lists of 100 elements each
    big = []
    for j in range(5):
        arr = []
        for i in range(100):
            arr.append(j * 1000 + i * 3 - j)
        big.append(arr)
    tests.append(big)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in range(iterations):
        for t in range(len(tests)):
            lists = buildLists(tests[t])
            merged = sol.mergeKLists(lists)

            sum_val = 0
            count = 0
            p = merged
            while p is not None:
                sum_val += p.val
                count += 1
                p = p.next

            checksum += (sum_val ^ (count * 1315423911L)) + long(t * 17 + iter)

            freeList(merged)

    end = time.time()
    elapsed_ms = int((end - start) * 1000.0)

    print "Checksum: %d" % (checksum,)
    print "Elapsed time (ms): %d" % (elapsed_ms,)