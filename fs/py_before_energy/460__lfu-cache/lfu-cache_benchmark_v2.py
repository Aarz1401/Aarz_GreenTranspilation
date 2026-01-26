# Time:  O(1), per operation
# Space: O(k), k is the capacity of cache

import collections


# using OrderedDict
class LFUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.__capa = capacity
        self.__size = 0
        self.__min_freq = float("inf")
        self.__freq_to_nodes = collections.defaultdict(collections.OrderedDict)
        self.__key_to_freq = {}

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key not in self.__key_to_freq:
            return -1
        value = self.__freq_to_nodes[self.__key_to_freq[key]][key]
        self.__update(key, value)
        return value

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        if self.__capa <= 0:
            return

        if key not in self.__key_to_freq and self.__size == self.__capa:
            del self.__key_to_freq[self.__freq_to_nodes[self.__min_freq].popitem(last=False)[0]]
            if not self.__freq_to_nodes[self.__min_freq]:
                del self.__freq_to_nodes[self.__min_freq]
            self.__size -= 1
        self.__update(key, value)
        
    def __update(self, key, value):
        freq = 0
        if key in self.__key_to_freq:
            freq = self.__key_to_freq[key]
            del self.__freq_to_nodes[freq][key]
            if not self.__freq_to_nodes[freq]:
                del self.__freq_to_nodes[freq]
                if self.__min_freq == freq:
                    self.__min_freq += 1
            self.__size -= 1

        freq += 1
        self.__min_freq = min(self.__min_freq, freq)
        self.__key_to_freq[key] = freq
        self.__freq_to_nodes[freq][key] = value
        self.__size += 1


# Time:  O(1), per operation
# Space: O(k), k is the capacity of cache
import collections


class ListNode(object):
    def __init__(self, key, value, freq):
        self.key = key
        self.val = value
        self.freq = freq
        self.next = None
        self.prev = None


class LinkedList(object):
    def __init__(self):
        self.head = None
        self.tail = None

    def append(self, node):
        node.next, node.prev = None, None  # avoid dirty node
        if self.head is None:
            self.head = node
        else:
            self.tail.next = node
            node.prev = self.tail
        self.tail = node

    def delete(self, node):
        if node.prev:
            node.prev.next = node.next
        else:
            self.head = node.next
        if node.next:
            node.next.prev = node.prev
        else:
            self.tail = node.prev
        node.next, node.prev = None, None  # make node clean


class LFUCache2(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.__capa = capacity
        self.__size = 0
        self.__min_freq = float("inf")
        self.__freq_to_nodes = collections.defaultdict(LinkedList)
        self.__key_to_node = {}

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key not in self.__key_to_node:
            return -1
        value = self.__key_to_node[key].val
        self.__update(key, value)
        return value

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        if self.__capa <= 0:
            return

        if key not in self.__key_to_node and self.__size == self.__capa:
            del self.__key_to_node[self.__freq_to_nodes[self.__min_freq].head.key]
            self.__freq_to_nodes[self.__min_freq].delete(self.__freq_to_nodes[self.__min_freq].head)
            if not self.__freq_to_nodes[self.__min_freq].head:
                del self.__freq_to_nodes[self.__min_freq]
            self.__size -= 1
        self.__update(key, value)
        
    def __update(self, key, value):
        freq = 0
        if key in self.__key_to_node:
            old_node = self.__key_to_node[key]
            freq = old_node.freq
            self.__freq_to_nodes[freq].delete(old_node)
            if not self.__freq_to_nodes[freq].head:
                del self.__freq_to_nodes[freq]
                if self.__min_freq == freq:
                    self.__min_freq += 1
            self.__size -= 1

        freq += 1
        self.__min_freq = min(self.__min_freq, freq)
        self.__key_to_node[key] = ListNode(key, value, freq)
        self.__freq_to_nodes[freq].append(self.__key_to_node[key])
        self.__size += 1


if __name__ == "__main__":
    tests = []

    # 1
    tests.append((2, [
        ('p',1,1), ('p',2,2), ('g',1,0), ('p',3,3), ('g',2,0),
        ('g',3,0), ('p',4,4), ('g',1,0), ('g',3,0), ('g',4,0)
    ]))

    # 2
    tests.append((1, [
        ('p',1,10), ('g',1,0), ('p',2,20), ('g',1,0), ('g',2,0),
        ('p',2,200), ('g',2,0)
    ]))

    # 3
    tests.append((3, [
        ('p',1,1), ('p',2,2), ('p',3,3), ('g',1,0), ('g',2,0),
        ('p',4,4), ('g',3,0), ('g',4,0), ('g',1,0), ('p',5,5),
        ('g',2,0), ('g',5,0)
    ]))

    # 4
    tests.append((3, [
        ('p',1,100), ('p',2,200), ('p',3,300), ('g',1,0), ('g',1,0),
        ('g',1,0), ('g',2,0), ('p',4,400), ('g',3,0), ('g',1,0), ('g',4,0)
    ]))

    # 5
    tests.append((2, [
        ('p',1,1), ('p',2,2), ('g',1,0), ('p',1,10), ('g',1,0),
        ('p',3,3), ('g',2,0), ('g',3,0)
    ]))

    # 6
    tests.append((4, [
        ('p',1,1), ('p',2,2), ('p',3,3), ('p',4,4), ('g',1,0), ('g',2,0),
        ('p',5,5), ('g',3,0), ('g',4,0), ('p',6,6), ('g',4,0), ('g',5,0), ('g',6,0)
    ]))

    # 7
    tests.append((3, [
        ('p',1,10), ('p',2,20), ('p',3,30), ('g',2,0), ('p',4,40),
        ('g',1,0), ('g',3,0), ('g',2,0)
    ]))

    # 8
    tests.append((5, [
        ('p',1,10), ('p',2,20), ('p',3,30), ('p',4,40), ('p',5,50),
        ('g',1,0), ('g',1,0), ('p',1,100), ('g',1,0), ('p',6,60),
        ('g',2,0), ('g',6,0)
    ]))

    # 9
    tests.append((2, [
        ('p',1,1), ('g',1,0), ('g',1,0), ('g',1,0), ('g',1,0), ('g',1,0),
        ('p',2,2), ('p',3,3), ('g',1,0), ('g',2,0), ('g',3,0)
    ]))

    # 10
    tests.append((3, [
        ('p',0,0), ('p',1,1), ('p',2,2), ('g',0,0), ('g',1,0),
        ('p',3,3), ('g',2,0), ('p',0,5), ('g',0,0)
    ]))

    sink = 0
    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for test in tests:
            cache = LFUCache(test[0])
            #local = 0
            for op in test[1]:
                if op[0] == 'p':
                    cache.put(op[1], op[2])
                elif op[0] == 'g':
                    r = cache.get(op[1])
            #checksum += local
        #sink = checksum
    # print sink