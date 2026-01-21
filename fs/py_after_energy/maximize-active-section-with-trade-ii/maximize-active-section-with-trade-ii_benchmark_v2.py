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
    tests = [
        {'s': '11111', 'queries': [[0, 0], [1, 3], [0, 4]]},
        {'s': '0000', 'queries': [[0, 0], [1, 2], [0, 3], [2, 3]]},
        {'s': '010101', 'queries': [[0, 5], [1, 4], [2, 3], [0, 1]]},
        {'s': '00111000', 'queries': [[0, 7], [0, 2], [3, 5], [2, 6], [1, 7]]},
        {'s': '10000100001', 'queries': [[0, 10], [1, 4], [5, 9], [2, 8], [3, 3], [10, 10]]},
        {'s': '101001110100', 'queries': [[0, 11], [4, 7], [2, 5], [6, 10], [1, 1], [9, 11]]},
        {'s': '010000010', 'queries': [[0, 8], [1, 7], [2, 6], [0, 0], [8, 8], [3, 5]]},
        {'s': '110011001100', 'queries': [[0, 11], [2, 9], [4, 7], [1, 10], [0, 3], [8, 11]]},
        {'s': '1010101010101010', 'queries': [[0, 15], [1, 14], [2, 13], [3, 12], [4, 11], [5, 10], [6, 9], [7, 8]]},
        {'s': '00110011100011110000', 'queries': [[0, 19], [0, 5], [6, 11], [12, 19], [3, 16], [8, 14], [4, 4], [15, 15]]}
    ]

    sol = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        checksum = 0
        for tc in tests:
            q = [list(pair) for pair in tc['queries']]
            res = sol.maxActiveSectionsAfterTrade(tc['s'], q)
            # for v in res:
            #     checksum += v
        #sink = checksum

    # print sink