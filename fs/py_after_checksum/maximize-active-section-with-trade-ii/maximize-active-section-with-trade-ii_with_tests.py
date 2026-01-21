# Time:  O(nlogn + q)
# Space: O(nlogn)

# sparse table
class Solution(object):
    def maxActiveSectionsAfterTrade(self, s, queries):
        """
        :type s: str
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # RMQ - Sparse Table
        # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
        # Time:  ctor:  O(NlogN) * O(fn)
        #        query: O(fn)
        # Space: O(NlogN)
        class SparseTable(object):
            def __init__(self, arr, fn):
                self.fn = fn
                self.bit_length = [0]
                n = len(arr)
                k = n.bit_length()-1  # log2_floor(n)
                for i in xrange(k+1):
                    self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
                self.st = [[0]*n for _ in xrange(k+1)]
                if not self.st:
                    return
                self.st[0] = arr[:]
                for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                    for j in xrange((n-(1<<i))+1):
                        self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
        
            def query(self, L, R):  # Time: O(fn)
                i = self.bit_length[R-L+1]-1
                return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])

        lookup = [-1]*len(s)
        idxs = []
        cnt1 = 0
        for i, x in enumerate(s):
            if x == '0':
                if i-1 >= 0 and s[i-1] == '0':
                    idxs[-1][1] += 1
                else:
                    idxs.append([i, 1])
            else:
                cnt1 += 1
            lookup[i] = len(idxs)-1
        if not idxs:
            return [cnt1]*len(queries)
        arr = [0]*(len(idxs)-1)
        for i in xrange(len(idxs)-1):
            arr[i] = idxs[i][1]+idxs[i+1][1]
        st = SparseTable(arr, max)
        result = [cnt1]*len(queries)
        for i, (l, r) in enumerate(queries):
            left, right  = lookup[l]+1, lookup[r]-int(s[r] == '0')
            left_cnt = idxs[lookup[l]][1]-(l-idxs[lookup[l]][0]) if lookup[l] != -1 else -1
            right_cnt = r-idxs[lookup[r]][0]+1 if lookup[r] != -1 else -1
            if left <= right-1:
                result[i] = max(result[i], cnt1 + st.query(left, right-1))
            if s[l] == '0' and s[r] == '0' and lookup[l]+1 == lookup[r]:
                result[i] = max(result[i], cnt1+left_cnt+right_cnt)
            if s[l] == '0' and lookup[l]+1 <= right:
                result[i] = max(result[i], cnt1+left_cnt+idxs[lookup[l]+1][1])
            if s[r] == '0' and left <= lookup[r]-1:
                result[i] = max(result[i], cnt1+right_cnt+idxs[lookup[r]-1][1])
        return result


if __name__ == "__main__":
    import time

    tests = []

    # 1) All zeros
    tc = {}
    tc['s'] = "0" * 10
    tc['queries'] = [
        [0, 9], [0, 0], [9, 9], [2, 7], [1, 2]
    ]
    tests.append(tc)

    # 2) All ones
    tc = {}
    tc['s'] = "1" * 10
    tc['queries'] = [
        [0, 9], [1, 1], [4, 7], [0, 0], [9, 9]
    ]
    tests.append(tc)

    # 3) Alternating pattern
    tc = {}
    n = 31
    tc['s'] = ''.join('0' if i % 2 == 0 else '1' for i in range(n))
    tc['queries'] = [
        [0, 30], [1, 29], [2, 2], [15, 15], [8, 23], [10, 20]
    ]
    tests.append(tc)

    # 4) Clustered runs of zeros and ones
    tc = {}
    tc['s'] = "000111000111000111"
    tc['queries'] = [
        [0, 5], [3, 8], [6, 11], [12, 17], [9, 15], [0, 17]
    ]
    tests.append(tc)

    # 5) Zeros at ends, ones in middle
    tc = {}
    tc['s'] = "00011111000"
    tc['queries'] = [
        [0, 10], [0, 2], [8, 10], [3, 7], [2, 8]
    ]
    tests.append(tc)

    # 6) Single zero
    tc = {}
    tc['s'] = "0"
    tc['queries'] = [
        [0, 0]
    ]
    tests.append(tc)

    # 7) Single one
    tc = {}
    tc['s'] = "1"
    tc['queries'] = [
        [0, 0]
    ]
    tests.append(tc)

    # 8) Mixed small with zero blocks at ends
    tc = {}
    tc['s'] = "0011100"
    tc['queries'] = [
        [0, 6], [0, 1], [5, 6], [2, 4], [1, 5]
    ]
    tests.append(tc)

    # 9) Irregular pattern with varying run lengths
    tc = {}
    tc['s'] = "101010001110000101011110000"
    tc['queries'] = [
        [0, 26], [3, 5], [7, 14], [10, 16], [20, 26], [12, 12]
    ]
    tests.append(tc)

    # 10) Large patterned case
    tc = {}
    pattern = "00001111"
    repeats = 625  # 8 * 625 = 5000
    tc['s'] = pattern * repeats
    q = []
    q.append([0, len(tc['s']) - 1])
    for seg in range(10):
        l = seg * 500
        r = min(len(tc['s']) - 1, l + 300)
        q.append([l, r])
    for seg in range(10):
        l = seg * 250
        r = min(len(tc['s']) - 1, l + 200)
        q.append([l, r])
    q.append([123, 4567])
    q.append([1000, 2000])
    q.append([2500, 3500])
    q.append([4000, 4500])
    q.append([0, 0])
    q.append([len(tc['s']) - 1, len(tc['s']) - 1])
    tc['queries'] = q
    tests.append(tc)

    sol = Solution()
    checksum = 0

    start = time.time()
    iterations = 1
    for iter in range(iterations):
        for ti in range(len(tests)):
            res = sol.maxActiveSectionsAfterTrade(tests[ti]['s'], tests[ti]['queries'])
            for i in range(len(res)):
                checksum += res[i] + iter + ti + i
    end = time.time()

    elapsed_us = int(round((end - start) * 1000000.0))
    print "Checksum: %s" % checksum
    print "Elapsed time (microseconds): %d" % elapsed_us