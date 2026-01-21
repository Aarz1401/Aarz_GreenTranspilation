
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


if __name__ == "__main__":
    def shash(s):
        if not s:
            return 0
        h = 0
        for ch in s:
            h = (h * 131 + ord(ch)) & 0xffffffff
        return h

    tests = []

    # Test 1
    tests.append([
        ('I', 'a'), ('I', 'b'), ('I', 'a'), ('I', 'c'), ('I', 'b'), ('I', 'a')
    ])

    # Test 2
    tests.append([
        ('I', 'apple'), ('I', 'apple'), ('I', 'apple'), ('I', 'apple'), ('I', 'apple'),
        ('I', 'banana'), ('I', 'banana'), ('I', 'banana'),
        ('I', 'cherry'),
        ('I', 'date'), ('I', 'date')
    ])

    # Test 3
    tests.append([
        ('I', 'x'), ('I', 'x'), ('I', 'x'), ('I', 'x'),
        ('I', 'y'),
        ('I', 'z'), ('I', 'z'), ('I', 'z')
    ])

    # Test 4
    tests.append([
        ('I', 'm'), ('I', 'm'),
        ('I', 'n'), ('I', 'n'),
        ('D', 'n'), ('D', 'n'),
        ('I', 'n'),
        ('I', 'o'), ('D', 'o')
    ])

    # Test 5
    tests.append([
        ('I', 'k1'), ('I', 'k1'), ('I', 'k1'), ('I', 'k1'), ('I', 'k1'),
        ('I', 'k1'), ('I', 'k1'), ('I', 'k1'), ('I', 'k1'), ('I', 'k1'),
        ('I', 'k2'), ('I', 'k2'), ('I', 'k2'), ('I', 'k2'), ('I', 'k2'),
        ('I', 'k2'), ('I', 'k2'), ('I', 'k2'), ('I', 'k2'),
        ('I', 'k3'), ('I', 'k3'), ('I', 'k3'), ('I', 'k3'), ('I', 'k3'),
        ('I', 'k3'), ('I', 'k3'), ('I', 'k3'),
        ('I', 'k4'), ('I', 'k4'), ('I', 'k4'), ('I', 'k4'), ('I', 'k4'),
        ('I', 'k4'), ('I', 'k4'),
        ('I', 'k5'), ('I', 'k5'), ('I', 'k5'), ('I', 'k5'), ('I', 'k5'), ('I', 'k5')
    ])

    # Test 6
    tests.append([
        ('I', 'alpha'), ('I', 'alpha'),
        ('I', 'beta'), ('I', 'beta'), ('I', 'beta'),
        ('D', 'alpha'),
        ('D', 'beta'),
        ('I', 'gamma'), ('I', 'gamma'), ('I', 'gamma'), ('I', 'gamma'),
        ('D', 'gamma'), ('D', 'gamma'),
        ('I', 'beta')
    ])

    # Test 7
    tests.append([
        ('I', 'aa'),
        ('I', 'bb'), ('I', 'bb'), ('I', 'bb'), ('I', 'bb'),
        ('I', 'cc'), ('I', 'cc'),
        ('I', 'dd'), ('I', 'dd'), ('I', 'dd')
    ])

    # Test 8
    tests.append([
        ('I', 't1'), ('I', 't1'), ('I', 't1'),
        ('I', 't2'), ('I', 't2'),
        ('I', 't3'), ('I', 't3'), ('I', 't3'), ('I', 't3'), ('I', 't3'), ('I', 't3'),
        ('I', 't4'), ('I', 't4'), ('I', 't4'),
        ('D', 't3'), ('D', 't3'),
        ('I', 't1'), ('I', 't1'),
        ('I', 't3'), ('I', 't3'), ('I', 't3'),
        ('D', 't4'),
        ('D', 't2')
    ])

    # Test 9
    tests.append([
        ('I', 'k0'), ('I', 'k0'), ('I', 'k0'), ('I', 'k0'), ('I', 'k0'),
        ('I', 'k0'), ('I', 'k0'), ('I', 'k0'), ('I', 'k0'),
        ('I', 'k1'),
        ('I', 'k2'), ('I', 'k2'), ('I', 'k2'), ('I', 'k2'),
        ('I', 'k3'), ('I', 'k3'), ('I', 'k3'), ('I', 'k3'), ('I', 'k3'), ('I', 'k3')
    ])

    # Test 10
    tests.append([
        ('I', 'w1'), ('I', 'w1'), ('I', 'w1'),
        ('I', 'w2'), ('I', 'w2'), ('D', 'w2'),
        ('I', 'w3'), ('I', 'w3'),
        ('I', 'w4'), ('I', 'w4'), ('I', 'w4'), ('I', 'w4'), ('I', 'w4'),
        ('I', 'w5'), ('I', 'w5'), ('I', 'w5'), ('I', 'w5')
    ])

    sink = 0
    iterations = 1
    for _ in xrange(iterations):
        checksum = 0
        for ops in tests:
            ds = AllOne()
            for op in ops:
                if op[0] == 'I':
                    ds.inc(op[1])
                elif op[0] == 'D':
                    ds.dec(op[1])
            mx = ds.getMaxKey()
            mn = ds.getMinKey()
            checksum += shash(mx) + shash(mn)
        sink += checksum
    print(sink)

    #print(sink)
