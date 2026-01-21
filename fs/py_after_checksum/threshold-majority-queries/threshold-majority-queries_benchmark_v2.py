# Time:  O(nlogn + qlogq + (n + q) * sqrt(n) + q * n)
# Space: O(n + q)

# sort, coordinate compression, mo's algorithm
class Solution(object):
    def subarrayMajority(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # reference: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
        def mo_s_algorithm():  # Time: O(QlogQ + (N + Q) * sqrt(N) + Q * N)
            def add(i):  # Time: O(F) = O(1)
                idx = num_to_idx[nums[i]]
                if cnt[idx]:
                    cnt2[cnt[idx]] -= 1
                cnt[idx] += 1
                cnt2[cnt[idx]] += 1
                max_freq[0] = max(max_freq[0], cnt[idx])

            def remove(i):  # Time: O(F) = O(1)
                idx = num_to_idx[nums[i]]
                cnt2[cnt[idx]] -= 1
                if not cnt2[max_freq[0]]:
                    max_freq[0] -= 1
                cnt[idx] -= 1
                if cnt[idx]:
                    cnt2[cnt[idx]] += 1

            def get_ans(t):  # Time: O(A) = O(N)
                if max_freq[0] < t:
                    return -1
                i = next(i for i in xrange(len(cnt)) if cnt[i] == max_freq[0])
                return sorted_nums[i]

            cnt = [0]*len(num_to_idx)
            cnt2 = [0]*(len(nums)+1)
            max_freq = [0]
            result = [-1]*len(queries)
            block_size = int(len(nums)**0.5)+1  # O(S) = O(sqrt(N))
            idxs = range(len(queries))
            idxs.sort(key=lambda x: (queries[x][0]//block_size, queries[x][1] if (queries[x][0]//block_size)&1 else -queries[x][1]))  # Time: O(QlogQ)
            left, right = 0, -1
            for i in idxs:  # Time: O((N / S) * N * F + S * Q * F + Q * A) = O((N + Q) * sqrt(N) + Q * N), O(S) = O(sqrt(N)), O(F) = O(logN), O(A) = O(1)
                l, r, t = queries[i]
                while left > l:
                    left -= 1
                    add(left)
                while right < r:
                    right += 1
                    add(right)
                while left < l:
                    remove(left)
                    left += 1
                while right > r:
                    remove(right)
                    right -= 1
                result[i] = get_ans(t)
            return result

        sorted_nums = sorted(set(nums))
        num_to_idx = {x:i for i, x in enumerate(sorted_nums)}
        return mo_s_algorithm()


# Time:  O(nlogn + qlogq + (n + q) * sqrt(n) * logn)
# Space: O(n + q)
from sortedcontainers import SortedList


# sort, coordinate compression, mo's algorithm, sorted list
class Solution_TLE(object):
    def subarrayMajority(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # reference: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
        def mo_s_algorithm():  # Time: O(QlogQ + (N + Q) * sqrt(N) * logN)
            def add(i):  # Time: O(F) = O(logN)
                idx = num_to_idx[nums[i]]
                if cnt[idx]:
                    lookup[cnt[idx]].remove(nums[i])
                cnt[idx] += 1
                lookup[cnt[idx]].add(nums[i])
                max_freq[0] = max(max_freq[0], cnt[idx])

            def remove(i):  # Time: O(F) = O(logN)
                idx = num_to_idx[nums[i]]
                lookup[cnt[idx]].remove(nums[i])
                if not lookup[max_freq[0]]:
                    max_freq[0] -= 1
                cnt[idx] -= 1
                if cnt[idx]:
                    lookup[cnt[idx]].add(nums[i])

            def get_ans(t):  # Time: O(A) = O(logN)
                return lookup[max_freq[0]][0] if max_freq[0] >= t else -1

            cnt = [0]*len(num_to_idx)
            lookup = [SortedList() for _ in xrange(len(nums)+1)]
            max_freq = [0]
            result = [-1]*len(queries)
            block_size = int(len(nums)**0.5)+1  # O(S) = O(sqrt(N))
            idxs = range(len(queries))
            idxs.sort(key=lambda x: (queries[x][0]//block_size, queries[x][1] if (queries[x][0]//block_size)&1 else -queries[x][1]))  # Time: O(QlogQ)
            left, right = 0, -1
            for i in idxs:  # Time: O((N / S) * N * F + S * Q * F + Q * A) = O((N + Q) * sqrt(N) * logN), O(S) = O(sqrt(N)), O(F) = O(logN), O(A) = O(1)
                l, r, t = queries[i]
                while left > l:
                    left -= 1
                    add(left)
                while right < r:
                    right += 1
                    add(right)
                while left < l:
                    remove(left)
                    left += 1
                while right > r:
                    remove(right)
                    right -= 1
                result[i] = get_ans(t)
            return result

        num_to_idx = {x:i for i, x in enumerate(sorted(set(nums)))}
        return mo_s_algorithm()


if __name__ == "__main__":
    tests = []

    tests.append({
        'nums': [1],
        'queries': [[0, 0, 1], [0, 0, 2]]
    })

    tests.append({
        'nums': [7, 7, 7, 7, 7],
        'queries': [[0, 4, 3], [1, 3, 2], [2, 2, 1], [0, 4, 6]]
    })

    tests.append({
        'nums': [1, 2, 3, 4, 5],
        'queries': [[0, 4, 3], [1, 3, 2], [1, 1, 1]]
    })

    tests.append({
        'nums': [-5, -1, -5, -1, -5, 2],
        'queries': [[0, 5, 3], [1, 3, 2], [0, 2, 2]]
    })

    tests.append({
        'nums': [1, 2, 1, 2, 1, 2],
        'queries': [[0, 5, 3], [0, 3, 2], [1, 4, 2], [2, 3, 2], [2, 3, 1]]
    })

    tests.append({
        'nums': [1000000000, -1000000000, 1000000000, 5, 5, 5, 7],
        'queries': [[0, 6, 3], [0, 2, 2], [3, 6, 2], [1, 1, 1]]
    })

    tests.append({
        'nums': [3, 3, 3, 2, 2, 1, 1, 1, 1, 1],
        'queries': [[0, 9, 4], [0, 2, 3], [3, 4, 2], [5, 9, 3], [0, 9, 6]]
    })

    tests.append({
        'nums': [9, 8, 7, 6, 5, 4, 3, 2, 1, 0],
        'queries': [[0, 9, 1], [2, 5, 1], [4, 4, 1], [0, 9, 2]]
    })

    tests.append({
        'nums': [1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4],
        'queries': [[0, 11, 4], [0, 11, 5], [2, 8, 3], [8, 11, 3]]
    })

    tests.append({
        'nums': [5, 1, 5, 2, 5, 3, 5, 4, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5],
        'queries': [[0, 19, 7], [1, 18, 6], [10, 19, 4], [1, 3, 2], [0, 0, 1]]
    })

    sol = Solution()
    iterations = 1
    sink = 0
    for iter in range(iterations):
        checksum = 0
        for tc in tests:
            ans = sol.subarrayMajority(tc['nums'], tc['queries'])
            for v in ans:
                checksum += v
        sink += checksum
    print(sink)
    # print sink