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
    sol = Solution()
    tests = [
        [1],
        [1,2,3,4,5],
        [5,4,3,2,1],
        [1,0,2],
        [1,2,2],
        [2,2,2,2,2],
        [1,3,4,5,2],
        [1,3,2,2,1],
        [1,6,10,8,7,3,2],
        [1,2,87,87,87,2,1]
    ]

    sink = 0

    iterations = 1000
    for _ in xrange(iterations):
        #checksum = 0
        for i in xrange(len(tests)):
            r = sol.candy(tests[i])
        #sink = checksum

    # print sink