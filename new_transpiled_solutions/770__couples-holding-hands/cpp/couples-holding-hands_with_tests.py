# Time:  O(n)
# Space: O(n)

class Solution(object):
    def minSwapsCouples(self, row):
        """
        :type row: List[int]
        :rtype: int
        """
        N = len(row)//2
        couples = [[] for _ in xrange(N)]
        for seat, num in enumerate(row):
            couples[num//2].append(seat//2)
        adj = [[] for _ in xrange(N)]
        for couch1, couch2 in couples:
            adj[couch1].append(couch2)
            adj[couch2].append(couch1)

        result = 0
        for couch in xrange(N):
            if not adj[couch]: continue
            couch1, couch2 = couch, adj[couch].pop()
            while couch2 != couch:
                result += 1
                adj[couch2].remove(couch1)
                couch1, couch2 = couch2, adj[couch2].pop()
        return result  # also equals to N - (# of cycles)


if __name__ == "__main__":
    import time
    import random

    def make_identity(n):
        return list(range(2 * n))

    def make_chain(n):
        # Pattern: [0, 2, 1, 4, 3, ..., 2n-2, 2n-3, 2n-1]
        out = [0]
        for k in xrange(1, n):
            out.append(2 * k)
            out.append(2 * k - 1)
        out.append(2 * n - 1)
        return out

    def make_pair_reversed(n):
        out = []
        for i in xrange(n):
            out.extend([2 * i + 1, 2 * i])
        return out

    def make_alternating(n):
        evens = [2 * i for i in xrange(n)]
        odds = [2 * i + 1 for i in xrange(n)]
        return evens + odds

    def make_random(n, seed):
        v = list(range(2 * n))
        rng = random.Random(seed)
        rng.shuffle(v)
        return v

    # Define 10 diverse test inputs
    tests = []
    tests.append(make_identity(1))            # [0,1]
    tests.append(make_chain(2))               # N=2 chain
    tests.append(make_chain(3))               # N=3 chain
    tests.append(make_pair_reversed(4))       # within-pair reversed
    tests.append(make_alternating(5))         # evens then odds
    tests.append(make_random(8, 42))          # random with fixed seed
    tests.append(make_identity(12))           # larger identity
    tests.append(make_chain(25))              # medium chain
    tests.append(make_random(60, 1234567))    # larger random
    tests.append(make_chain(1000))            # big chain

    solution = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for row in tests:
            checksum += solution.minSwapsCouples(row[:])

    end = time.time()
    elapsed_us = int(round((end - start) * 1e6))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", elapsed_us