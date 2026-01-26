# Time:  O(n^2)
# Space: O(n^2)

class Solution(object):
    def evaluate(self, expression):
        """
        :type expression: str
        :rtype: int
        """
        def getval(lookup, x):
            return lookup.get(x, x)

        def evaluate(tokens, lookup):
            if tokens[0] in ('add', 'mult'):
                a, b = map(int, map(lambda x: getval(lookup, x), tokens[1:]))
                return str(a+b if tokens[0] == 'add' else a*b)
            for i in xrange(1, len(tokens)-1, 2):
                if tokens[i+1]:
                    lookup[tokens[i]] = getval(lookup, tokens[i+1])
            return getval(lookup, tokens[-1])

        tokens, lookup, stk = [''], {}, []
        for c in expression:
            if c == '(':
                if tokens[0] == 'let':
                    evaluate(tokens, lookup)
                stk.append((tokens, dict(lookup)))
                tokens =  ['']
            elif c == ' ':
                tokens.append('')
            elif c == ')':
                val = evaluate(tokens, lookup)
                tokens, lookup = stk.pop()
                tokens[-1] += val
            else:
                tokens[-1] += c
        return int(tokens[0])


if __name__ == "__main__":
    tests = [
        "(add 1 2)",
        "(mult 3 (add 2 3))",
        "(let x 2 (mult x 5))",
        "(let x 3 x 2 x)",
        "(let x 1 y 2 (add x y))",
        "(let x 2 (let x 3 (let x 4 x)))",
        "(let x 2 (add (let x 3 x) x))",
        "(let a -3 b 2 (mult a (add b 5)))",
        "(add (add 1 2) (mult 3 4))",
        "(let x 2 y (add x 3) z (mult y x) (add z (mult x y)))"
    ]

    sol = Solution()
    iterations = 1000
    for iter in range(iterations):
        #checksum = 0
        for expr in tests:
            r = sol.evaluate(expr)
        #sink = checksum