# Time:  ctor: O(b)
#        pick: O(1)
# Space: O(b)

import random


class Solution(object):
    
    def __init__(self, N, blacklist):
        """
        :type N: int
        :type blacklist: List[int]
        """
        self.__n = N-len(blacklist)
        self.__lookup = {}
        white = iter(set(range(self.__n, N))-set(blacklist))
        for black in blacklist:
            if black < self.__n:
                self.__lookup[black] = next(white)
        
        
    def pick(self):
        """
        :rtype: int
        """
        index = random.randint(0, self.__n-1)
        return self.__lookup[index] if index in self.__lookup else index


# Time:  ctor: O(blogb)
#        pick: O(logb)
# Space: O(b)
import random

class Solution2(object):
    
    def __init__(self, N, blacklist):
        """
        :type N: int
        :type blacklist: List[int]
        """
        self.__n = N-len(blacklist)
        blacklist.sort()
        self.__blacklist = blacklist
        
    def pick(self):
        """
        :rtype: int
        """
        index = random.randint(0, self.__n-1)
        left, right = 0, len(self.__blacklist)-1
        while left <= right:
            mid = left+(right-left)//2
            if index+mid < self.__blacklist[mid]:
                right = mid-1
            else:
                left = mid+1
        return index+left

if __name__ == "__main__":
    import time

    # Define 10 diverse test inputs
    tests = []

    # 1) N=1, empty blacklist
    tests.append((1, []))

    # 2) N=2, single blacklisted element at top
    tests.append((2, [1]))

    # 3) N=10, empty blacklist
    tests.append((10, []))

    # 4) N=10, first half blacklisted
    tests.append((10, [0, 1, 2, 3, 4]))

    # 5) N=10, second half blacklisted
    tests.append((10, [5, 6, 7, 8, 9]))

    # 6) N=1000, even numbers blacklisted
    bl = []
    for i in range(0, 1000, 2):
        bl.append(i)
    tests.append((1000, bl))

    # 7) N=1000, upper half blacklisted
    bl = []
    for i in range(500, 1000):
        bl.append(i)
    tests.append((1000, bl))

    # 8) N=100000, 200 pseudo-random unique blacklisted indices
    N = 100000
    s = set()
    i = 0
    while len(s) < 200:
        val = (i * 7919 + 12345) % N
        s.add(val)
        i += 1
    bl = []
    for v in s:
        bl.append(v)
    tests.append((N, bl))

    # 9) N=100000, first 10000 numbers blacklisted
    N = 100000
    bl = []
    for i in range(10000):
        bl.append(i)
    tests.append((N, bl))

    # 10) N=9973, mixed regions blacklisted
    N = 9973
    bl = []
    for i in range(9000, min(9200, N)):
        bl.append(i)
    for i in range(0, 300, 35):
        bl.append(i)
    tests.append((N, bl))

    checksum = 0

    start = time.time()
    iterations = 1000
    for iter in range(iterations):
        for i in range(len(tests)):
            N, bl = tests[i]
            sol = Solution(N, bl)

            # Perform several picks to exercise the picker
            local = 0
            for k in range(32):
                local += sol.pick()
            # Mix in some variation with additional picks
            local ^= sol.pick()
            checksum += ((local + N) ^ i)
    end = time.time()

    elapsed_us = int((end - start) * 1000000.0)
    print "Checksum: %d" % checksum
    print "Elapsed time (us): %d" % elapsed_us