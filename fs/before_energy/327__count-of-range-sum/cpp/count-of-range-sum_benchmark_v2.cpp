#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>

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

struct Test {
    std::vector<int> nums;
    int lower;
    int upper;
};

int main() {
    std::vector<Test> tests = {
        { {-2, 5, -1}, -2, 2 },
        { {1, 2, 3, 4}, 3, 6 },
        { {-1, -2, -3}, -5, -2 },
        { {0, 0, 0}, 0, 0 },
        { {5}, 5, 5 },
        { {2147483647, -2147483647, 2147483647}, 2147483647, 2147483647 },
        { {3, -1, 2, -2, 5, -3, 1, -4, 2}, -1, 3 },
        { {-1000, -1000, -1000, -1000, -1000}, -3000, -1000 },
        { {1000000000, -1000000000, 1000000000, -1000000000, 1}, -1, 1 },
        { {7, -5, 4, -2, 8, -6, 3, -1, 0, 2}, 0, 8 }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = sol.countRangeSum(t.nums, t.lower, t.upper);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}