# Time:  O(1), per operation
# Space: O(k)

class Node(object):
    """
    double linked list node
    """
    def __init__(self, value, keys):
        self.value = value
        self.keys = keys
        self.prev = None
        self.next = None


class LinkedList(object):
    def __init__(self):
        self.head, self.tail = Node(0, set()), Node(0, set())
        self.head.next, self.tail.prev = self.tail, self.head

    def insert(self, pos, node):
        node.prev, node.next = pos.prev, pos
        pos.prev.next, pos.prev = node, node
        return node

    def erase(self, node):
        node.prev.next, node.next.prev = node.next, node.prev
        del node

    def empty(self):
        return self.head.next is self.tail

    def begin(self):
        return self.head.next

    def end(self):
        return self.tail

    def front(self):
        return self.head.next

    def back(self):
        return self.tail.prev


class AllOne(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.bucket_of_key = {}
        self.buckets = LinkedList()

    def inc(self, key):
        """
        Inserts a new key <Key> with value 1. Or increments an existing key by 1.
        :type key: str
        :rtype: void
        """
        if key not in self.bucket_of_key:
            self.bucket_of_key[key] = self.buckets.insert(self.buckets.begin(), Node(0, set([key])))

        bucket, next_bucket = self.bucket_of_key[key], self.bucket_of_key[key].next
        if next_bucket is self.buckets.end() or next_bucket.value > bucket.value+1:
            next_bucket = self.buckets.insert(next_bucket, Node(bucket.value+1, set()))
        next_bucket.keys.add(key)
        self.bucket_of_key[key] = next_bucket

        bucket.keys.remove(key)
        if not bucket.keys:
            self.buckets.erase(bucket)

    def dec(self, key):
        """
        Decrements an existing key by 1. If Key's value is 1, remove it from the data structure.
        :type key: str
        :rtype: void
        """
        if key not in self.bucket_of_key:
            return

        bucket, prev_bucket = self.bucket_of_key[key], self.bucket_of_key[key].prev
        self.bucket_of_key.pop(key, None)
        if bucket.value > 1:
            if bucket is self.buckets.begin() or prev_bucket.value < bucket.value-1:
                prev_bucket = self.buckets.insert(bucket, Node(bucket.value-1, set()))
            prev_bucket.keys.add(key)
            self.bucket_of_key[key] = prev_bucket

        bucket.keys.remove(key)
        if not bucket.keys:
            self.buckets.erase(bucket)

    def getMaxKey(self):
        """
        Returns one of the keys with maximal value.
        :rtype: str
        """
        if self.buckets.empty():
            return ""
        return iter(self.buckets.back().keys).next()

    def getMinKey(self):
        """
        Returns one of the keys with Minimal value.
        :rtype: str
        """
        if self.buckets.empty():
            return ""
        return iter(self.buckets.front().keys).next()


def str_checksum(s):
    total = 0
    for i, ch in enumerate(s):
        total = (total + (i + 1) * ord(ch)) % 0x7fffffff
    total = (total + len(s)) % 0x7fffffff
    return total

def runTest(tc):
    ao = AllOne()
    total = 0
    for op, arg in tc:
        if op == 'inc':
            ao.inc(arg)
        elif op == 'dec':
            ao.dec(arg)
        elif op == 'getMaxKey':
            s = ao.getMaxKey()
            total += str_checksum(s) * 1000003
        elif op == 'getMinKey':
            s = ao.getMinKey()
            total += str_checksum(s) * 1000033
    return total

def buildTests():
    tests = []

    # Test 0: empty structure queries
    tests.append([
        ('getMaxKey', None),
        ('getMinKey', None),
    ])

    # Test 1: simple, ensuring unique min/max at query points
    tests.append([
        ('inc', 'a'),
        ('getMaxKey', None),   # a
        ('getMinKey', None),   # a
        ('inc', 'b'),
        ('inc', 'b'),
        ('getMaxKey', None),   # b
        ('getMinKey', None),   # a
        ('inc', 'c'),
        ('dec', 'a'),          # remove a
        ('getMinKey', None),   # c
        ('dec', 'b'),          # b becomes 1
        ('inc', 'c'),          # c becomes 2
        ('getMaxKey', None),   # c
        ('getMinKey', None),   # b
    ])

    # Test 2: more operations with careful unique min/max queries
    tests.append([
        ('dec', 'q'),          # non-existent key
        ('inc', 'x'), ('inc', 'x'), ('inc', 'x'),            # x=3
        ('inc', 'y'), ('inc', 'y'), ('inc', 'y'), ('inc', 'y'), ('inc', 'y'),  # y=5
        ('inc', 'z'), ('inc', 'z'),                          # z=2
        ('getMaxKey', None),   # y
        ('getMinKey', None),   # z
        ('dec', 'y'),          # y=4
        ('getMaxKey', None),   # y
        ('dec', 'z'),          # z=1
        ('getMinKey', None),   # z
        ('dec', 'x'), ('dec', 'x'),                          # x=1
        # min is ambiguous now (x=1, z=1) => no query
        ('inc', 'z'),                                          # z=2
        ('getMinKey', None),   # x
        ('dec', 'y'), ('dec', 'y'), ('dec', 'y'),            # y=1
        ('getMaxKey', None),   # z
        ('dec', 'x'),                                          # remove x
        ('getMinKey', None),   # y
        ('dec', 'y'),                                          # remove y
        ('getMaxKey', None),   # z
        ('getMinKey', None),   # z
        ('dec', 'z'), ('dec', 'z'),                          # remove z -> empty
        ('getMaxKey', None),   # ""
        ('getMinKey', None),   # ""
    ])

    return tests


if __name__ == "__main__":
    import time

    tests = buildTests()
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for tc in tests:
            checksum += runTest(tc)

    end = time.time()
    elapsed = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed