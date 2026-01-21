#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <cstdint>
#include <algorithm>

class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper) {
        int n = static_cast<int>(nums.size());
        std::vector<long long> sums(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            sums[i + 1] = sums[i] + static_cast<long long>(nums[i]);
        }
        long long res = countAndMergeSort(sums, 0, static_cast<int>(sums.size()), static_cast<long long>(lower), static_cast<long long>(upper));
        return static_cast<int>(res);
    }
    
private:
    long long countAndMergeSort(std::vector<long long>& sums, int start, int end, long long lower, long long upper) {
        if (end - start <= 1) {  // The size of range [start, end) less than 2 is always with count 0.
            return 0;
        }
        int mid = start + (end - start) / 2;
        long long count = countAndMergeSort(sums, start, mid, lower, upper) +
                          countAndMergeSort(sums, mid, end, lower, upper);
        int j = mid, k = mid, r = mid;
        std::vector<long long> tmp;
        tmp.reserve(end - start);
        for (int i = start; i < mid; ++i) {
            // Count the number of range sums that lie in [lower, upper].
            while (k < end && sums[k] - sums[i] < lower) {
                ++k;
            }
            while (j < end && sums[j] - sums[i] <= upper) {
                ++j;
            }
            count += (j - k);

            // Merge the two sorted arrays into tmp.
            while (r < end && sums[r] < sums[i]) {
                tmp.push_back(sums[r]);
                ++r;
            }
            tmp.push_back(sums[i]);
        }
        // Copy tmp back to sums.
        for (int i = 0; i < static_cast<int>(tmp.size()); ++i) {
            sums[start + i] = tmp[i];
        }
        return count;
    }
};