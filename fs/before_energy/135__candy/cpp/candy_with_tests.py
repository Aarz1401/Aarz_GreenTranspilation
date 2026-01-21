# Time:  O(n)
# Space: O(n)

class Solution(object):
    # @param ratings, a list of integer
    # @return an integer
    def candy(self, ratings):
        candies = [1 for _ in xrange(len(ratings))]
        for i in xrange(1, len(ratings)):
            if ratings[i] > ratings[i - 1]:
                candies[i] = candies[i - 1] + 1

        for i in reversed(xrange(1, len(ratings))):
            if ratings[i - 1] > ratings[i] and candies[i - 1] <= candies[i]:
                candies[i - 1] = candies[i] + 1

        return sum(candies)

if __name__ == "__main__":
    import time

    tests = []

    # 1) Empty input
    tests.append([])

    # 2) Single element
    tests.append([5])

    # 3) Strictly increasing
    tests.append([1,2,3,4,5,6,7,8,9])

    # 4) Strictly decreasing
    tests.append([9,8,7,6,5,4,3,2,1])

    # 5) All equal
    tests.append([7] * 10)

    # 6) Peaks and valleys with plateaus
    tests.append([1,3,2,2,1,2,3,1])

    # 7) Alternating high/low
    tests.append([1,0,1,0,1,0,1,0,1,0])

    # 8) Plateau then drop then rise
    tests.append([2,2,2,2,1,2,2,3,3,2,1,1,2])

    # 9) Deterministic pseudo-random long input
    v9 = [0] * 2048
    for i in xrange(len(v9)):
        v9[i] = (i * 37 + 13) % 100
    tests.append(v9)

    # 10) Triangular wave pattern
    v10 = []
    for i in xrange(1000):
        phase = i % 40
        val = phase if phase < 20 else 39 - phase
        v10.append(val)
    tests.append(v10)

    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for _ in xrange(iterations):
        for t in tests:
            checksum += sol.candy(t)

    end = time.time()
    elapsed_us = int(round((end - start) * 1000000.0))

    print "Checksum: {}".format(checksum)
    print "Elapsed time (microseconds): {}".format(elapsed_us)