# Time:  O(n^2)
# Space: O(n^2)

class Solution(object):
    def canCross(self, stones):
        """
        :type stones: List[int]
        :rtype: bool
        """
        if stones[1] != 1:
            return False

        last_jump_units = {s: set() for s in stones}
        last_jump_units[1].add(1)
        for s in stones[:-1]:
            for j in last_jump_units[s]:
                for k in (j-1, j, j+1):
                    if k > 0 and s+k in last_jump_units:
                        last_jump_units[s+k].add(k)
        return bool(last_jump_units[stones[-1]])

if __name__ == "__main__":
    tests = [
        [0,1,3,5,6,8,12,17],
        [0,1,2,3,4,8,9,11],
        [0,1],
        [0,2],
        [0,1,2,4,7,11,16,22,29],
        [0,1,3,6,10,15,16,21],
        [0,1,3,4,5,7,9,10,12],
        [0,1,2,3,4,5,6,7,8,9,10],
        [0,1,4,9,16,25,36,49,64,81,100],
        [0,1,2,3,5,8,12,17,23,30]
    ]

    s = Solution()
    sink = 0

    iterations = 1000
    for iter in xrange(iterations):
        #checksum = 0
        for t in tests:
            r = s.canCross(t)
        #sink = checksum