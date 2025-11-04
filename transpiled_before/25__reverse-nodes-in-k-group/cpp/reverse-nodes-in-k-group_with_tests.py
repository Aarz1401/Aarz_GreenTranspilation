# Time:  O(n)
# Space: O(1)

class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

    def __repr__(self):
        if self:
            return "{} -> {}".format(self.val, repr(self.next))

class Solution(object):
    # @param head, a ListNode
    # @param k, an integer
    # @return a ListNode
    def reverseKGroup(self, head, k):
        dummy = ListNode(-1)
        dummy.next = head

        cur, cur_dummy = head, dummy
        length = 0

        while cur:
            next_cur = cur.next
            length = (length + 1) % k

            if length == 0:
                next_dummy = cur_dummy.next
                self.reverse(cur_dummy, cur.next)
                cur_dummy = next_dummy

            cur = next_cur

        return dummy.next

    def reverse(self, begin, end):
            first = begin.next
            cur = first.next

            while cur != end:
                first.next = cur.next
                cur.next = begin.next
                begin.next = cur
                cur = first.next

def buildList(arr):
    if not arr:
        return None
    dummy = ListNode(0)
    cur = dummy
    for v in arr:
        node = ListNode(v)
        cur.next = node
        cur = node
    return dummy.next

def checksumList(head):
    mask = (1 << 64) - 1
    x = 1469598103934665603  # FNV-1a 64-bit offset basis
    fnv_prime = 1099511628211
    i = 0
    cur = head
    while cur:
        v = cur.val & mask
        mix = (v + 0x9e3779b97f4a7c15 + ((i << 6) & mask) + (i >> 2)) & mask
        x ^= mix
        x = (x * fnv_prime) & mask
        cur = cur.next
        i += 1
    x ^= i & mask
    x = (x * fnv_prime) & mask
    return x

def freeList(head):
    cur = head
    while cur:
        nxt = cur.next
        cur.next = None
        cur = nxt

if __name__ == "__main__":
    import time

    # Prepare 10 diverse test inputs (lists) and corresponding k values
    tests = [None] * 10
    tests[0] = []                                        # empty list
    tests[1] = [1]                                       # single element, k=1
    tests[2] = [5]                                       # single element, k>len
    tests[3] = [1, 2]                                    # exact group
    tests[4] = [1, 2, 3]                                 # partial group
    tests[5] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]           # ascending
    tests[6] = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]           # descending
    tests[7] = [1, 1, 1, 1, 1, 1]                        # duplicates
    tests[8] = [0, -1, 2, -3, 4, -5, 6]                  # mixed negatives/positives
    tests[9] = [0] * 100                                 # larger test
    for i in xrange(100):
        tests[9][i] = (i * 7 + (-i if (i % 3 == 0) else i)) - 50

    ks = [3, 1, 2, 2, 2, 3, 4, 2, 3, 5]

    sol = Solution()

    total_checksum = 0
    mask = (1 << 64) - 1
    const64 = 0x9e3779b97f4a7c15

    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        for i in xrange(10):
            head = buildList(tests[i])
            res = sol.reverseKGroup(head, ks[i])
            h = checksumList(res) & mask
            prev = total_checksum & mask
            mix = (h + const64 + ((prev << 6) & mask) + (prev >> 2)) & mask
            total_checksum = (prev ^ mix) & mask
            freeList(res)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum:", total_checksum
    print "Elapsed time (us):", elapsed_us