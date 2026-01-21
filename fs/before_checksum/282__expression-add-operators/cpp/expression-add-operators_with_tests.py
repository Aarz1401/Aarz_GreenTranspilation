# Time:  O(4^n)
# Space: O(n)

class Solution(object):
    def addOperators(self, num, target):
        """
        :type num: str
        :type target: int
        :rtype: List[str]
        """
        result, expr = [], []
        val, i = 0, 0
        val_str = ""
        while i < len(num):
            val = val * 10 + ord(num[i]) - ord('0')
            val_str += num[i]
            # Avoid "00...".
            if str(val) != val_str:
                break
            expr.append(val_str)
            self.addOperatorsDFS(num, target, i + 1, 0, val, expr, result)
            expr.pop()
            i += 1
        return result

    def addOperatorsDFS(self, num, target, pos, operand1, operand2, expr, result):
        if pos == len(num) and operand1 + operand2 == target:
            result.append("".join(expr))
        else:
            val, i = 0, pos
            val_str = ""
            while i < len(num):
                val = val * 10 + ord(num[i]) - ord('0')
                val_str += num[i]
                # Avoid "00...".
                if str(val) != val_str:
                    break

                # Case '+':
                expr.append("+" + val_str)
                self.addOperatorsDFS(num, target, i + 1, operand1 + operand2, val, expr, result)
                expr.pop()

                # Case '-':
                expr.append("-" + val_str)
                self.addOperatorsDFS(num, target, i + 1, operand1 + operand2, -val, expr, result)
                expr.pop()

                # Case '*':
                expr.append("*" + val_str)
                self.addOperatorsDFS(num, target, i + 1, operand1, operand2 * val, expr, result)
                expr.pop()

                i += 1

if __name__ == "__main__":
    from timeit import default_timer

    tests = [
        ("123", 6),
        ("232", 8),
        ("105", 5),
        ("00", 0),
        ("00", 1),
        ("3456", 21),
        ("9999", 100),
        ("12345", 15),
        ("1005", 5),
        ("214", 9)
    ]

    sol = Solution()
    checksum = 0

    start = default_timer()
    iterations = 1
    for iter in xrange(iterations):
        for tc in tests:
            res = sol.addOperators(tc[0], tc[1])
            checksum += len(res)
            for s in res:
                checksum += len(s)
                if s:
                    checksum += ord(s[0])
    end = default_timer()

    elapsed_ns = int((end - start) * 1e9)
    print("Checksum: %d" % checksum)
    print("Elapsed time (ns): %d" % elapsed_ns)