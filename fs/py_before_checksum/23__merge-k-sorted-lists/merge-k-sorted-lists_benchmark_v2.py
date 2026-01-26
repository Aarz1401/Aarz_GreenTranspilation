
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
    tests = [
        [[1, 2, 3, 4, 5]],
        [[1, 4, 7], [2, 3, 6, 8]],
        [[1, 1, 1], [1, 1], [1]],
        [[-5, -3, 0, 2], [-4, -1, 3], [-2, 2, 5], [-6, -6, 7]],
        [[0, 10000], [5, 10, 15], [1, 2, 3, 4], [9999, 10000], [6]],
        [[3], [1], [2], [5], [4], [0]],
        [[1, 3, 5, 7, 9], [2, 4, 6, 8, 10], [0, 11, 12]],
        [[2, 2, 2, 2], [2, 2, 2]],
        [[-10, -9, -9, -8], [-8, -8], [-7], [-10, -5], [-6, -6, -6], [-4, -3, -3, -3], [-2, -1, 0]],
        [[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]
    ]

    sol = Solution()
    sink = 0

    iterations = 1
    for _ in range(iterations):
        checksum = 0

        for test in tests:
            lists = []
            for seq in test:
                head = ListNode(seq[0])
                tail = head
                for i in range(1, len(seq)):
                    tail.next = ListNode(seq[i])
                    tail = tail.next
                lists.append(head)

            merged = sol.mergeKLists(lists)
            while merged:
                checksum += merged.val
                merged = merged.next

        sink += checksum
    print(sink)

    # print sink
