# Time:  O(n)
# Space: O(h)

class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Codec(object):

    def serialize(self, root):
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        def serializeHelper(node):
            if not node:
                vals.append('#')
                return
            vals.append(str(node.val))
            serializeHelper(node.left)
            serializeHelper(node.right)
        vals = []
        serializeHelper(root)
        return ' '.join(vals)


    def deserialize(self, data):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        def deserializeHelper():
            val = next(vals)
            if val == '#':
                return None
            node = TreeNode(int(val))
            node.left = deserializeHelper()
            node.right = deserializeHelper()
            return node
        def isplit(source, sep):
            sepsize = len(sep)
            start = 0
            while True:
                idx = source.find(sep, start)
                if idx == -1:
                    yield source[start:]
                    return
                yield source[start:idx]
                start = idx + sepsize
        vals = iter(isplit(data, ' '))
        return deserializeHelper()


# time: O(n)
# space: O(n)

class Codec2(object):

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        def gen_preorder(node):
            if not node:
                yield '#'
            else:
                yield str(node.val)
                for n in gen_preorder(node.left):
                    yield n
                for n in gen_preorder(node.right):
                    yield n
                
        return ' '.join(gen_preorder(root))
        
    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        def builder(chunk_iter):
            val = next(chunk_iter)
            if val == '#':
                return None
            node = TreeNode(int(val))
            node.left = builder(chunk_iter)
            node.right = builder(chunk_iter)
            return node
        
        # https://stackoverflow.com/a/42373311/568901
        chunk_iter = iter(data.split())
        return builder(chunk_iter)


if __name__ == "__main__":
    tests = [
        "1 # # ",
        "2 1 # # 3 # # ",
        "4 3 2 1 # # # # # ",
        "1 # 2 # 3 # 4 # # ",
        "1 2 4 # # 5 # # 3 6 # # 7 # # ",
        "-10 -20 -30 # # -5 # # 15 0 # # 22 # # ",
        "1 1 1 # # # 1 1 # # 1 # # ",
        "8 4 2 1 # # 3 # # 6 5 # # 7 # # 12 10 9 # # 11 # # 14 13 # # 15 # # ",
        "5 2 # 3 # # 9 # 10 8 # # # ",
        "1 # 2 3 # 4 5 # # # # "
    ]

    # Run tests with Codec (strip trailing spaces to match its parser)
    codec = Codec()
    iterations = 1000
    sink = 0
    for iter in xrange(iterations):
        #checksum = 0
        for s in tests:
            root = codec.deserialize(s.rstrip())
            s2 = codec.serialize(root)
            #checksum += len(s2)
        #sink = checksum

    # # Run tests with Codec2
    # codec2 = Codec2()
    # sink2 = 0
    # for iter in xrange(iterations):
    #     checksum = 0
    #     for s in tests:
    #         root = codec2.deserialize(s)
    #         s2 = codec2.serialize(root)
    #     #     checksum += len(s2)
    #     # sink2 = checksum