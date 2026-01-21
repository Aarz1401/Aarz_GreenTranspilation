
# Time:  precompute: O((logr) * log(logr) + log*(r) * (logr)) = O((logr) * log(logr)), r = max(n)
#        runtime:    O(nlogr + max_k * n + nlogn + qlogn)
# Space: O(logr + max_k * n)

# fenwick tree
def popcount(x):
    return bin(x).count('1')


def ceil_log2(x):
    return (x-1).bit_length()


class BIT(object):  # 0-indexed.
    def __init__(self, n):
        self.__bit = [0]*(n+1)  # Extra one for dummy node.

    def add(self, i, val):
        i += 1  # Extra one for dummy node.
        while i < len(self.__bit):
            self.__bit[i] += val
            i += (i & -i)

    def query(self, i):
        i += 1  # Extra one for dummy node.
        ret = 0
        while i > 0:
            ret += self.__bit[i]
            i -= (i & -i)
        return ret


MAX_N = 10**15
MAX_BIT_LEN = MAX_N.bit_length()
D = [0]*(MAX_BIT_LEN+1)
for i in xrange(2, MAX_BIT_LEN+1):
    D[i] = D[popcount(i)]+1
MAX_K = 0
while MAX_N != 1:  # O(log*(MAX_N)) times
    MAX_N = ceil_log2(MAX_N)
    MAX_K += 1
class Solution(object):
    def popcountDepth(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def count(x):
            return D[popcount(x)]+1 if x != 1 else 0
        
        bit = [BIT(len(nums)) for _ in xrange(MAX_K+1)]
        for i in xrange(len(nums)):
            bit[count(nums[i])].add(i, +1)
        result = []
        for q in queries:
            if q[0] == 1:
                _, l, r, k = q
                assert(k < len(bit))
                result.append(bit[k].query(r)-bit[k].query(l-1))
            else:
                _, i, x = q
                old_d = count(nums[i])
                new_d = count(x)
                if new_d != old_d:
                    bit[old_d].add(i, -1)
                    bit[new_d].add(i, +1)
                nums[i] = x
        return result


if __name__ == "__main__":
    tests = []

    t = {}
    t['nums'] = [1]
    t['queries'] = [
        [1, 0, 0, 0],
        [2, 0, 2],
        [1, 0, 0, 1]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [2, 3, 4]
    t['queries'] = [
        [1, 0, 2, 1],
        [1, 1, 2, 2],
        [2, 2, 7],
        [1, 0, 2, 3]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [1, 2, 15, 16, 31]
    t['queries'] = [
        [1, 0, 4, 0],
        [1, 0, 4, 1],
        [1, 0, 4, 2],
        [1, 0, 4, 3],
        [1, 0, 4, 4],
        [2, 0, 1024],
        [1, 0, 4, 0]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [6, 10, 12, 24]
    t['queries'] = [
        [1, 0, 3, 2],
        [2, 1, 10],
        [1, 1, 2, 2],
        [2, 3, 5],
        [1, 0, 3, 2]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [999999999999999, 500000000000000, 1, 2, 3, 4]
    t['queries'] = [
        [1, 0, 5, 5],
        [1, 2, 5, 0],
        [2, 2, 8],
        [1, 0, 5, 0],
        [1, 0, 5, 1]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [5, 7, 9, 11, 13, 17, 21, 33]
    t['queries'] = [
        [1, 0, 7, 3],
        [2, 4, 1],
        [1, 0, 7, 0],
        [1, 3, 5, 2]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [1, 3, 7, 15, 31, 63, 127, 255, 511, 1023]
    t['queries'] = [
        [1, 0, 9, 4],
        [2, 9, 1],
        [1, 0, 9, 0],
        [1, 0, 9, 3]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [1 << 49, 1 << 48, 1 << 47, 1 << 46, 1 << 45]
    t['queries'] = [
        [1, 0, 4, 1],
        [2, 2, 3],
        [1, 0, 4, 2],
        [1, 1, 3, 1]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [123456789012345, 98765432109876, 555555555555555, 222222222222222, 99999999999999, 314159265358979, 271828182845904]
    t['queries'] = [
        [1, 0, 6, 3],
        [2, 5, 1],
        [1, 0, 6, 0],
        [2, 0, 2],
        [1, 0, 3, 1]
    ]
    tests.append(t)

    t = {}
    t['nums'] = [1, 2, 3, 4, 5, 6]
    t['queries'] = [
        [1, 0, 5, 0],
        [1, 0, 5, 1],
        [2, 0, 7],
        [1, 0, 2, 3],
        [2, 4, 1],
        [1, 0, 5, 0]
    ]
    tests.append(t)

    sink = 0
    iterations = 1000
    for iter in range(iterations):
        checksum = 0
        for ti in range(len(tests)):
            cur = tests[ti]
            sol = Solution()
            out = sol.popcountDepth(cur['nums'], cur['queries'])
            #for v in out:
                #checksum += v
            #checksum += len(out)
        #sink = checksum
    # print sink
