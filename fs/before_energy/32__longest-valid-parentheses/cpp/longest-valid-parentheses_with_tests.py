# Time:  O(n)
# Space: O(1)

class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        def length(it, start, c):
            depth, longest = 0, 0
            for i in it:
                if s[i] == c:
                    depth += 1
                else:
                    depth -= 1
                    if depth < 0:
                        start, depth = i, 0
                    elif depth == 0:
                        longest = max(longest, abs(i - start))
            return longest

        return max(length(xrange(len(s)), -1, '('), \
                   length(reversed(xrange(len(s))), len(s), ')'))


# Time:  O(n)
# Space: O(n)
class Solution2(object):
    # @param s, a string
    # @return an integer
    def longestValidParentheses(self, s):
        longest, last, indices = 0, -1, []
        for i in xrange(len(s)):
            if s[i] == '(':
                indices.append(i)
            elif not indices:
                last = i
            else:
                indices.pop()
                if not indices:
                    longest = max(longest, i - last)
                else:
                    longest = max(longest, i - indices[-1])
        return longest


if __name__ == "__main__":
    from time import time

    inputs = []
    inputs.append("")
    inputs.append("(" * 10)
    inputs.append(")" * 10)
    inputs.append("()")
    inputs.append("(())")
    inputs.append(")()())")
    inputs.append("(()")
    inputs.append("())(())")
    inputs.append("(" * 100 + ")" * 100)
    alt = []
    for i in xrange(300):
        alt.append('(' if i % 2 == 0 else ')')
    inputs.append(''.join(alt))

    sol = Solution()
    checksum = 0

    start = time()
    iterations = 1000
    for iter in xrange(iterations):
        for s in inputs:
            res = sol.longestValidParentheses(s)
            checksum += res
    end = time()

    elapsed_ns = int((end - start) * 1e9)
    print "Checksum:", checksum
    print "Elapsed time (ns):", elapsed_ns