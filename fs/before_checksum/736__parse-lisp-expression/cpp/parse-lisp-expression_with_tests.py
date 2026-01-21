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
    import time

    tests = [
        "(add 1 2)",
        "(mult 3 4)",
        "(add 1 (mult 2 3))",
        "(let x 2 (add x 3))",
        "(let x 2 (let y (mult x 5) (add y x)))",
        "(let x 1 (let x 2 (add x x)))",
        "(let x 5 (add (let x 3 x) x))",
        "(let x 1 y 2 z 3 (add x (add y z)))",
        "(add -3 (mult -2 4))",
        "(let x 2 x (add x 3) x (mult x 2) x)"
    ]

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1
    for _ in xrange(iterations):
        for expr in tests:
            checksum += sol.evaluate(expr)

    end = time.time()
    elapsed_ns = int((end - start) * 1e9)

    print "Checksum: %d" % checksum
    print "Elapsed time (ns): %d" % elapsed_ns