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
    tests = [
        {'N': 1, 'blacklist': []},
        {'N': 2, 'blacklist': [1]},
        {'N': 3, 'blacklist': [0]},
        {'N': 4, 'blacklist': [2]},
        {'N': 5, 'blacklist': [0, 4]},
        {'N': 10, 'blacklist': [1, 2, 3, 4, 5, 6, 7, 8]},
        {'N': 7, 'blacklist': [5, 6]},
        {'N': 1000, 'blacklist': []},
        {'N': 1000, 'blacklist': [0, 10, 999, 500, 250, 750, 333, 666, 100, 900]},
        {'N': 100000, 'blacklist': [0, 1, 2, 3, 4, 5, 42, 123, 4567, 54321, 75000, 99998, 99999]},
    ]

    sink = 0
    iterations = 1
    for _iter in xrange(iterations):
        checksum = 0
        for t in tests:
            sol = Solution(t['N'], t['blacklist'])
            checksum += sol.pick()
        sink += checksum
    print(sink)