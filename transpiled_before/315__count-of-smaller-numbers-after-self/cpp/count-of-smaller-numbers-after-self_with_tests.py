# Time:  O(nlogn)
# Space: O(n)

class Solution(object):
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        def countAndMergeSort(num_idxs, start, end, counts):
            if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
                return

            mid = start + (end - start) // 2
            countAndMergeSort(num_idxs, start, mid, counts)
            countAndMergeSort(num_idxs, mid + 1, end, counts)
            r = mid + 1
            tmp = []
            for i in xrange(start, mid + 1):
                # Merge the two sorted arrays into tmp.
                while r <= end and num_idxs[r][0] < num_idxs[i][0]:
                    tmp.append(num_idxs[r])
                    r += 1
                tmp.append(num_idxs[i])
                counts[num_idxs[i][1]] += r - (mid + 1)

            # Copy tmp back to num_idxs
            num_idxs[start:start+len(tmp)] = tmp

        num_idxs = []
        counts = [0] * len(nums)
        for i, num in enumerate(nums):
            num_idxs.append((num, i))
        countAndMergeSort(num_idxs, 0, len(num_idxs) - 1, counts)
        return counts


# Time:  O(nlogn)
# Space: O(n)
# BIT solution.
class Solution2(object):
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
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

        # Get the place (position in the ascending order) of each number.
        sorted_nums = sorted(zip(nums, range(len(nums))))
        lookup = {i:new_i for new_i, (_, i) in enumerate(sorted_nums)}

        # Count the smaller elements after the number.
        result, bit = [0]*len(nums), BIT(len(nums))
        for i in reversed(xrange(len(nums))):
            result[i] = bit.query(lookup[i]-1)
            bit.add(lookup[i], 1)
        return result


# Time:  O(nlogn) ~ O(n^2)
# Space: O(n)
# BST solution.
class Solution3(object):
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        res = [0] * len(nums)
        bst = self.BST()
        # Insert into BST and get left count.
        for i in reversed(xrange(len(nums))):
            bst.insertNode(nums[i])
            res[i] = bst.query(nums[i])

        return res

    class BST(object):
        class BSTreeNode(object):
            def __init__(self, val):
                self.val = val
                self.count = 0
                self.left = self.right = None

        def __init__(self):
            self.root = None

        # Insert node into BST.
        def insertNode(self, val):
            node = self.BSTreeNode(val)
            if not self.root:
                self.root = node
                return
            curr = self.root
            while curr:
                # Insert left if smaller.
                if node.val < curr.val:
                    curr.count += 1  # Increase the number of left children.
                    if curr.left:
                        curr = curr.left
                    else:
                        curr.left = node
                        break
                else:  # Insert right if larger or equal.
                    if curr.right:
                        curr = curr.right
                    else:
                        curr.right = node
                        break

        # Query the smaller count of the value.
        def query(self, val):
            count = 0
            curr = self.root
            while curr:
                # Insert left.
                if val < curr.val:
                    curr = curr.left
                elif val > curr.val:
                    count += 1 + curr.count  # Count the number of the smaller nodes.
                    curr = curr.right
                else:  # Equal.
                    return count + curr.count
            return 0


if __name__ == "__main__":
    import time

    # INT limits as in C++
    INT_MAX = 2147483647
    INT_MIN = -2147483648

    # Minimal MT19937 implementation with uniform_int_distribution equivalent
    class MT19937(object):
        def __init__(self, seed):
            self.n = 624
            self.m = 397
            self.MT = [0] * self.n
            self.index = self.n
            self.lower_mask = 0x7FFFFFFF
            self.upper_mask = 0x80000000
            self.seed_mt(seed)

        def seed_mt(self, seed):
            self.index = self.n
            self.MT[0] = seed & 0xFFFFFFFF
            for i in range(1, self.n):
                self.MT[i] = (1812433253 * (self.MT[i - 1] ^ (self.MT[i - 1] >> 30)) + i) & 0xFFFFFFFF

        def twist(self):
            for i in range(self.n):
                x = (self.MT[i] & self.upper_mask) + (self.MT[(i + 1) % self.n] & self.lower_mask)
                xA = x >> 1
                if x & 1:
                    xA ^= 0x9908B0DF
                self.MT[i] = self.MT[(i + self.m) % self.n] ^ xA
            self.index = 0

        def rand32(self):
            if self.index >= self.n:
                self.twist()
            y = self.MT[self.index]
            y ^= (y >> 11)
            y ^= ((y << 7) & 0x9D2C5680)
            y ^= ((y << 15) & 0xEFC60000)
            y ^= (y >> 18)
            self.index += 1
            return y & 0xFFFFFFFF

        def randint(self, a, b):
            if a > b:
                a, b = b, a
            n = b - a + 1
            R = 0xFFFFFFFF
            bucket = (R + 1) // n
            limit = bucket * n - 1
            while True:
                r = self.rand32()
                if r <= limit:
                    return a + (r // bucket)

    # Prepare 10 diverse test inputs
    tests = []

    # 1. Empty
    tests.append([])

    # 2. Single element
    tests.append([42])

    # 3. Strictly ascending
    asc = []
    for i in range(1, 17):
        asc.append(i)
    tests.append(asc)

    # 4. Strictly descending
    desc = []
    for i in range(20, 0, -1):
        desc.append(i)
    tests.append(desc)

    # 5. All equal elements
    tests.append([7] * 12)

    # 6. Mixed negatives and duplicates
    tests.append([5, 2, 6, 1, -1, 2, 2, 3, 0, -2, 5, 1])

    # 7. Random (fixed seed), size 128
    rng = MT19937(123456)
    v = [rng.randint(-1000000, 1000000) for _ in range(128)]
    tests.append(v)

    # 8. Extremes including INT_MIN and INT_MAX
    tests.append([INT_MAX, INT_MIN, 0, -1, 1, INT_MAX, INT_MIN, 0, -2, 2])

    # 9. Alternating high/low pattern
    alt = []
    for i in range(20):
        if i % 2 == 0:
            alt.append(1000 - i)
        else:
            alt.append(-1000 + i)
    tests.append(alt)

    # 10. Another random (fixed seed), size 512
    rng2 = MT19937(789)
    v2 = [rng2.randint(-500000, 500000) for _ in range(512)]
    tests.append(v2)

    # Benchmark harness
    sol = Solution()
    checksum = 0

    start = time.time()

    iterations = 1000
    for it in range(iterations):
        for t, nums in enumerate(tests):
            res = sol.countSmaller(nums)
            for i, r in enumerate(res):
                checksum += long(r) * (long(i + 1) + (nums[i] & 0xFFFF))
            checksum ^= long(len(res)) << (t % 17)

    end = time.time()
    elapsed_ms = (end - start) * 1000.0

    print "Checksum:", checksum
    print "Elapsed time (ms):", elapsed_ms