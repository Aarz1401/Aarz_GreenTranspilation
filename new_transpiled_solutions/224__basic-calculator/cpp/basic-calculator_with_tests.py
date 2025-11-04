# Time:  O(n)
# Space: O(n)

import operator


class Solution(object):
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        def compute(operands, operators):
            right, left = operands.pop(), operands.pop()
            operands.append(ops[operators.pop()](left, right))

        ops = {'+':operator.add, '-':operator.sub, '*':operator.mul, '/':operator.div}
        precedence = {'+':0, '-':0, '*':1, '/':1}
        operands, operators, operand = [], [], 0
        for i in xrange(len(s)):
            if s[i].isdigit():
                operand = operand*10 + int(s[i])
                if i == len(s)-1 or not s[i+1].isdigit():
                    operands.append(operand)
                    operand = 0
            elif s[i] == '(':
                operators.append(s[i])
            elif s[i] == ')':
                while operators[-1] != '(':
                    compute(operands, operators)
                operators.pop()
            elif s[i] in precedence:
                while operators and operators[-1] in precedence and \
                      precedence[operators[-1]] >= precedence[s[i]]:
                    compute(operands, operators)
                operators.append(s[i])
        while operators:
            compute(operands, operators)
        return operands[-1]


# Time:  O(n)
# Space: O(n)
class Solution2(object):
    # @param {string} s
    # @return {integer}
    def calculate(self, s):
        operands, operators = [], []
        operand = ""
        for i in reversed(xrange(len(s))):
            if s[i].isdigit():
                operand += s[i]
                if i == 0 or not s[i-1].isdigit():
                    operands.append(int(operand[::-1]))
                    operand = ""
            elif s[i] == ')' or s[i] == '+' or s[i] == '-':
                operators.append(s[i])
            elif s[i] == '(':
                while operators[-1] != ')':
                    self.compute(operands, operators)
                operators.pop()

        while operators:
            self.compute(operands, operators)

        return operands[-1]

    def compute(self, operands, operators):
        left, right = operands.pop(), operands.pop()
        op = operators.pop()
        if op == '+':
            operands.append(left + right)
        elif op == '-':
            operands.append(left - right)


if __name__ == "__main__":
    import time

    tests = [
        "3+2*2",
        " 3/2 ",
        " 3+5 / 2 ",
        "(1+(4+5+2)-3)+(6+8)",
        "14-3/2",
        "2*(5+5*2)/3+(6/2+8)",
        "1-(2+3*(4-5))+6/2",
        "((10+20)-(30-40))/5",
        "1000000*3/2",
        " (  7 + (8/  4) * (  3 + 5 )  ) - 6 "
    ]

    solver = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for iter in range(iterations):
        for s in tests:
            checksum += solver.calculate(s)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: {}".format(checksum)
    print "Elapsed time (us): {}".format(elapsed_us)