# coding: utf-8
import time

# ========== PASSING PYTHON 2 SOLUTION (100% UNMODIFIED) ==========
# Time:  O(n)
# Space: O(n)

# iterative dfs, manacher's algorithm
class Solution(object):
    def findAnswer(self, parent, s):
        """
        :type parent: List[int]
        :type s: str
        :rtype: List[bool]
        """
        def manacher(s):
            s = '^#' + '#'.join(s) + '#$'
            P = [0]*len(s)
            C, R = 0, 0
            for i in xrange(1, len(s)-1):
                i_mirror = 2*C-i
                if R > i:
                    P[i] = min(R-i, P[i_mirror])
                while s[i+1+P[i]] == s[i-1-P[i]]:
                    P[i] += 1
                if i+P[i] > R:
                    C, R = i, i+P[i]
            return P
    
        def iter_dfs(u):
            cnt = 0
            curr = []
            lookup = [None]*len(adj)
            stk = [(1, (0,))]
            while stk:
                step, args = stk.pop()
                if step == 1:
                    u = args[0]
                    stk.append((2, (u, cnt)))
                    for v in reversed(adj[u]):
                        stk.append((1, (v,)))
                elif step == 2:
                    u, left = args
                    curr.append(s[u])
                    lookup[u] = (left, cnt)
                    cnt += 1
            return curr, lookup

        adj = [[] for _ in xrange(len(parent))]
        for v in xrange(1, len(parent)):
            adj[parent[v]].append(v)
        curr, lookup = iter_dfs(0)
        P = manacher(curr)
        return [P[(2*(left+1)+2*(right+1))//2] >= right-left+1 for left, right in lookup]


# Time:  O(n)
# Space: O(n)
# dfs, manacher's algorithm
class Solution2(object):
    def findAnswer(self, parent, s):
        """
        :type parent: List[int]
        :type s: str
        :rtype: List[bool]
        """
        def manacher(s):
            s = '^#' + '#'.join(s) + '#$'
            P = [0]*len(s)
            C, R = 0, 0
            for i in xrange(1, len(s)-1):
                i_mirror = 2*C-i
                if R > i:
                    P[i] = min(R-i, P[i_mirror])
                while s[i+1+P[i]] == s[i-1-P[i]]:
                    P[i] += 1
                if i+P[i] > R:
                    C, R = i, i+P[i]
            return P
    
        def dfs(u):
            left = cnt[0]
            for v in adj[u]:
                dfs(v)
            curr.append(s[u])
            lookup[u] = (left, cnt[0])
            cnt[0] += 1

        adj = [[] for _ in xrange(len(parent))]
        for v in xrange(1, len(parent)):
            adj[parent[v]].append(v)
        cnt = [0]
        curr = []
        lookup = [None]*len(adj)
        dfs(0)
        P = manacher(curr)
        return [P[(2*(left+1)+2*(right+1))//2] >= right-left+1 for left, right in lookup]

# ==================================================================

# ========== TEST HARNESS ==========
def main():
    iterations = 1000

    # Test cases extracted from C++ (convert C++ syntax to Python 2)
    test_cases = [
        # 1) Single node
        ([0], "a"),

        # 2) Root with one child (star of size 2)
        ([0, 0], "ab"),

        # 3) Chain of length 3
        ([0, 0, 1], "aba"),  # 0->1->2

        # 4) Star with 3 children
        ([0, 0, 0, 0], "abba"),

        # 5) Chain of length 5 (palindromic)
        ([0, 0, 1, 2, 3], "abcba"),

        # 6) Balanced-ish size 6, choose chars so postorder is palindrome
        # Tree: 0->{1,2}, 1->{3,4}, 2->{5}
        ([0, 0, 0, 1, 1, 2], "acbabc"),  # Postorder sequence = [s3, s4, s1, s5, s2, s0] -> a b c c b a

        # 7) 8-node with all same chars
        # Tree: 0->{1,2}, 1->{3,4}, 2->{5,6}, 3->{7}
        ([0, 0, 0, 1, 1, 2, 2, 3], "aaaaaaaa"),

        # 8) Chain size 7 with alternating characters (non-palindromic)
        ([0, 0, 1, 2, 3, 4, 5], "abababc"),

        # 9) 9-node mixed branching
        # Tree: 0->{1,2,3}, 1->{4,5}, 2->{6,7}, 3->{8}
        ([0, 0, 0, 0, 1, 1, 2, 2, 3], "abcabcabc"),

        # 10) Star size 10 (root + 9 children) with children forming a palindrome
        ([0, 0, 0, 0, 0, 0, 0, 0, 0, 0], "xabacdcaba"),  # s[1..9] is a palindrome, root char 'x'
    ]

    # Warm-up
    sol = Solution2()
    for test in test_cases:
        if isinstance(test, tuple):
            sol.findAnswer(*test)
        else:
            sol.findAnswer(test)

    # Benchmark
    results = []
    start_time = time.time()

    for _ in xrange(iterations):
        sol = Solution2()
        for test in test_cases:
            if isinstance(test, tuple):
                result = sol.findAnswer(*test)
            else:
                result = sol.findAnswer(test)
            results.append(result)

    elapsed_time = time.time() - start_time
    checksum = sum(hash(str(r)) for r in results) % (10**9 + 7)
    print("Checksum: {}, Total time: {:.6f}s".format(checksum, elapsed_time))

if __name__ == "__main__":
    main()
