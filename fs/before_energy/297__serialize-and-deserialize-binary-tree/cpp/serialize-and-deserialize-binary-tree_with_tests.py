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


def build_complete_tree(vals):
    nodes = [TreeNode(v) if v is not None else None for v in vals]
    n = len(nodes)
    for i in xrange(n):
        if nodes[i] is not None:
            li, ri = 2*i + 1, 2*i + 2
            if li < n:
                nodes[i].left = nodes[li]
            if ri < n:
                nodes[i].right = nodes[ri]
    return nodes[0] if nodes else None

def buildTestTrees():
    trees = []

    # 1) Empty tree
    trees.append(None)

    # 2) Single node
    t_single = TreeNode(1)
    trees.append(t_single)

    # 3) Left-skewed
    t_left = TreeNode(1)
    t_left.left = TreeNode(2)
    t_left.left.left = TreeNode(3)
    t_left.left.left.left = TreeNode(4)
    trees.append(t_left)

    # 4) Right-skewed
    t_right = TreeNode(1)
    t_right.right = TreeNode(2)
    t_right.right.right = TreeNode(3)
    t_right.right.right.right = TreeNode(4)
    trees.append(t_right)

    # 5) Perfectly balanced (depth 2)
    t_bal = TreeNode(1)
    t_bal.left = TreeNode(2)
    t_bal.right = TreeNode(3)
    t_bal.left.left = TreeNode(4)
    t_bal.left.right = TreeNode(5)
    t_bal.right.left = TreeNode(6)
    t_bal.right.right = TreeNode(7)
    trees.append(t_bal)

    # 6) Mixed shape
    t_mixed = TreeNode(5)
    t_mixed.left = TreeNode(3)
    t_mixed.right = TreeNode(8)
    t_mixed.left.right = TreeNode(4)
    t_mixed.right.left = TreeNode(7)
    t_mixed.right.right = TreeNode(9)
    trees.append(t_mixed)

    # 7) With negatives and zero
    t_neg = TreeNode(0)
    t_neg.left = TreeNode(-1)
    t_neg.right = TreeNode(1)
    t_neg.left.left = TreeNode(-2)
    t_neg.right.right = TreeNode(2)
    trees.append(t_neg)

    # 8) Duplicates
    t_dup = TreeNode(2)
    t_dup.left = TreeNode(2)
    t_dup.right = TreeNode(2)
    t_dup.left.left = TreeNode(2)
    t_dup.left.right = TreeNode(2)
    trees.append(t_dup)

    # 9) Unbalanced irregular
    t_unbal = TreeNode(10)
    t_unbal.left = TreeNode(5)
    t_unbal.left.right = TreeNode(7)
    t_unbal.left.right.left = TreeNode(6)
    t_unbal.right = TreeNode(20)
    t_unbal.right.left = TreeNode(15)
    trees.append(t_unbal)

    # 10) Complete tree of 15 nodes
    t_complete15 = build_complete_tree([i for i in xrange(1, 16)])
    trees.append(t_complete15)

    # 11) Sparse tree using array representation
    # indices:        0   1   2   3    4    5    6    7    8
    t_sparse = build_complete_tree([1, 2, 3, 4, None, 6, None, None, 5])
    trees.append(t_sparse)

    return trees

def deleteTree(root):
    # Post-order cleanup of references
    if root is None:
        return
    stack = [root]
    visited = set()
    while stack:
        node = stack[-1]
        if node is None:
            stack.pop()
            continue
        if id(node) in visited:
            stack.pop()
            node.left = None
            node.right = None
            continue
        visited.add(id(node))
        stack.append(node.right)
        stack.append(node.left)


if __name__ == "__main__":
    import time

    # Build test inputs
    tests = buildTestTrees()

    # Instances of the provided classes (unmodified)
    codec = Codec()
    codec2 = Codec2()

    # Accumulator to prevent optimization
    checksum = 0

    # Timing
    start = time.time()

    iterations = 1000
    for iter in xrange(iterations):
        # Run serialize/deserialize for each test input
        for t in tests:
            # Codec
            s1 = codec.serialize(t)
            d1 = codec.deserialize(s1)
            checksum += len(s1)
            checksum += (d1.val if d1 is not None else 0)

            # Codec2
            s2 = codec2.serialize(t)
            d2 = codec2.deserialize(s2)
            checksum += len(s2)
            checksum += (d2.val if d2 is not None else 0)

            # Clean up deserialized trees
            try:
                deleteTree(d1)
            except NameError:
                pass
            try:
                deleteTree(d2)
            except NameError:
                pass

    end = time.time()
    elapsed_ns = int((end - start) * 1000000000)

    # Clean up original test trees
    for t in tests:
        try:
            deleteTree(t)
        except NameError:
            pass

    print "Checksum: {}".format(checksum)
    print "Elapsed time (ns): {}".format(elapsed_ns)