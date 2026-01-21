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
    t1 = TreeNode(42)

    t2 = TreeNode(1)
    t2.left = TreeNode(2)

    t3 = TreeNode(-10)
    t3.left = TreeNode(9)
    t3.right = TreeNode(20)
    t3.right.left = TreeNode(15)
    t3.right.right = TreeNode(7)

    t4 = TreeNode(-3)
    t4.left = TreeNode(-2)
    t4.right = TreeNode(-4)

    t5 = TreeNode(1)
    t5.left = TreeNode(2)
    t5.left.left = TreeNode(3)
    t5.left.left.left = TreeNode(4)
    t5.left.left.left.left = TreeNode(5)

    t6 = TreeNode(-1)
    t6.right = TreeNode(2)
    t6.right.right = TreeNode(3)
    t6.right.right.right = TreeNode(-4)
    t6.right.right.right.right = TreeNode(5)

    t7 = TreeNode(5)
    t7.left = TreeNode(4)
    t7.right = TreeNode(8)
    t7.left.left = TreeNode(11)
    t7.left.left.left = TreeNode(7)
    t7.left.left.right = TreeNode(2)
    t7.right.left = TreeNode(13)
    t7.right.right = TreeNode(4)
    t7.right.right.right = TreeNode(1)

    t8 = TreeNode(0)
    t8.left = TreeNode(-3)
    t8.right = TreeNode(0)
    t8.right.left = TreeNode(0)
    t8.right.right = TreeNode(-2)

    t9 = TreeNode(1)
    t9.left = TreeNode(2)
    t9.right = TreeNode(3)
    t9.left.left = TreeNode(4)
    t9.left.right = TreeNode(5)
    t9.right.left = TreeNode(6)
    t9.right.right = TreeNode(7)

    t10 = TreeNode(10)
    t10.left = TreeNode(-2)
    t10.right = TreeNode(7)
    t10.left.left = TreeNode(8)
    t10.left.right = TreeNode(-4)
    t10.right.left = TreeNode(-1)
    t10.right.right = TreeNode(3)

    tests = [t1, t2, t3, t4, t5, t6, t7, t8, t9, t10]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for root in tests:
            r = sol.maxPathSum(root)
        #sink = checksum