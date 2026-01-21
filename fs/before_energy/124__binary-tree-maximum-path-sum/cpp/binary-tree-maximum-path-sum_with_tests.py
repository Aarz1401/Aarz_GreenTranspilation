# Time:  O(n)
# Space: O(h), h is height of binary tree

class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution(object):
    # @param root, a tree node
    # @return an integer
    def maxPathSum(self, root):
        def iter_dfs(node):
            result = float("-inf")
            max_sum = [0]
            stk = [(1, [node, max_sum])]
            while stk:
                step, params = stk.pop()
                if step == 1:
                    node, ret = params
                    if not node:
                        continue
                    ret1, ret2 = [0], [0]
                    stk.append((2, [node, ret1, ret2, ret]))
                    stk.append((1, [node.right, ret2]))
                    stk.append((1, [node.left, ret1]))
                elif step == 2:
                    node, ret1, ret2, ret = params
                    result = max(result, node.val+max(ret1[0], 0)+max(ret2[0], 0))
                    ret[0] = node.val+max(ret1[0], ret2[0], 0)
            return result
        
        return iter_dfs(root)


# Time:  O(n)
# Space: O(h), h is height of binary tree
class Solution2(object):
    # @param root, a tree node
    # @return an integer
    def maxPathSum(self, root):
        def dfs(node):
            if not node:
                return (float("-inf"), 0)
            max_left, curr_left = dfs(node.left)
            max_right, curr_right = dfs(node.right)
            return (max(max_left, max_right, node.val+max(curr_left, 0)+max(curr_right, 0)),
                    node.val+max(curr_left, curr_right, 0))
        
        return dfs(root)[0]


if __name__ == "__main__":
    import time

    tests = []

    # 1) Single node
    r = TreeNode(5)
    tests.append(r)

    # 2) Small balanced positive
    r = TreeNode(1)
    r.left = TreeNode(2)
    r.right = TreeNode(3)
    tests.append(r)

    # 3) Classic mixed with negatives
    r = TreeNode(-10)
    r.left = TreeNode(9)
    r.right = TreeNode(20)
    r.right.left = TreeNode(15)
    r.right.right = TreeNode(7)
    tests.append(r)

    # 4) All negatives
    r = TreeNode(-3)
    r.left = TreeNode(-2)
    r.right = TreeNode(-1)
    r.left.left = TreeNode(-4)
    r.left.right = TreeNode(-5)
    tests.append(r)

    # 5) Left-skewed increasing
    r = TreeNode(5)
    r.left = TreeNode(4)
    r.left.left = TreeNode(3)
    r.left.left.left = TreeNode(2)
    r.left.left.left.left = TreeNode(1)
    tests.append(r)

    # 6) Right-skewed negatives
    r = TreeNode(-1)
    r.right = TreeNode(-2)
    r.right.right = TreeNode(-3)
    r.right.right.right = TreeNode(-4)
    r.right.right.right.right = TreeNode(-5)
    tests.append(r)

    # 7) Mixed with zeros
    r = TreeNode(0)
    r.left = TreeNode(1)
    r.right = TreeNode(-1)
    r.left.left = TreeNode(2)
    r.left.right = TreeNode(-2)
    r.right.left = TreeNode(3)
    r.right.right = TreeNode(-3)
    tests.append(r)

    # 8) Larger positives forming a long cross-root path
    r = TreeNode(10)
    r.left = TreeNode(2)
    r.right = TreeNode(10)
    r.right.left = TreeNode(20)
    r.right.right = TreeNode(1)
    tests.append(r)

    # 9) Full tree depth ~3 with multiple branches
    r = TreeNode(5)
    r.left = TreeNode(4)
    r.right = TreeNode(8)
    r.left.left = TreeNode(11)
    r.left.left.left = TreeNode(7)
    r.left.left.right = TreeNode(2)
    r.right.left = TreeNode(13)
    r.right.right = TreeNode(4)
    r.right.right.left = TreeNode(5)
    r.right.right.right = TreeNode(1)
    tests.append(r)

    # 10) Mixed positives and negatives with both subtrees
    r = TreeNode(2)
    r.left = TreeNode(-1)
    r.right = TreeNode(-2)
    r.left.left = TreeNode(3)
    r.left.right = TreeNode(4)
    r.right.left = TreeNode(-5)
    r.right.right = TreeNode(1)
    tests.append(r)

    solver = Solution()

    checksum = 0
    iterations = 1000
    start = time.time()
    for _ in xrange(iterations):
        for root in tests:
            checksum += solver.maxPathSum(root)
    end = time.time()

    elapsed_us = int((end - start) * 1000000.0)

    print "Checksum: %d" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us