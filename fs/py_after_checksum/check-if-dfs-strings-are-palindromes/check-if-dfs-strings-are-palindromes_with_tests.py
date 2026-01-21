
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


if __name__ == "__main__":
    import time
    import random

    rnd = random.Random(123456789)

    def generateParent(n):
        if n <= 0:
            return []
        p = [-1] + [0] * (n - 1)
        for v in xrange(1, n):
            p[v] = rnd.randint(0, v - 1)
        return p

    def generateString(n):
        letters = "abcdefghijklmnopqrstuvwxyz"
        return ''.join(letters[rnd.randint(0, 25)] for _ in xrange(n))

    # Define 10 diverse test inputs

    # 1) Single node
    parent1 = [-1]
    s1 = "a"

    # 2) Two-node chain
    parent2 = [-1, 0]
    s2 = "ab"

    # 3) Chain of 5
    parent3 = [-1, 0, 1, 2, 3]
    s3 = "abcde"

    # 4) Balanced binary tree with palindrome string
    parent4 = [-1, 0, 0, 1, 1, 2, 2]
    s4 = "racecar"

    # 5) Star tree of 10 nodes
    parent5 = [-1, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    s5 = "abcdefghij"

    # 6) Random-like tree n=50
    n6 = 50
    parent6 = generateParent(n6)
    s6 = generateString(n6)

    # 7) Random-like tree n=100
    n7 = 100
    parent7 = generateParent(n7)
    s7 = generateString(n7)

    # 8) Random-like tree n=300
    n8 = 300
    parent8 = generateParent(n8)
    s8 = generateString(n8)

    # 9) Random-like tree n=700
    n9 = 700
    parent9 = generateParent(n9)
    s9 = generateString(n9)

    # 10) Random-like tree n=1200
    n10 = 1200
    parent10 = generateParent(n10)
    s10 = generateString(n10)

    parents = [
        parent1, parent2, parent3, parent4, parent5,
        parent6, parent7, parent8, parent9, parent10
    ]
    strings = [s1, s2, s3, s4, s5, s6, s7, s8, s9, s10]

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in xrange(iterations):
        for i in xrange(len(parents)):
            res = sol.findAnswer(parents[i], strings[i])
            local = 0
            for j in xrange(len(res)):
                if res[j]:
                    local += (j + 1)
            local ^= (len(res) * (i + 1))
            checksum += local
    end = time.time()

    elapsed_ns = int(round((end - start) * 1e9))

    print "Checksum: " + str(checksum)
    print "Elapsed (ns): " + str(elapsed_ns)
