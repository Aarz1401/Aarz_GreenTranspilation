#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <climits>

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

struct TestCase {
    std::vector<int> nums;
    int lower;
    int upper;
};

int main() {
    // Prepare 10 diverse test cases
    std::vector<TestCase> tests;
    tests.reserve(10);

    // 1) Empty array
    tests.push_back(TestCase{std::vector<int>{}, 0, 0});

    // 2) Single positive element
    tests.push_back(TestCase{std::vector<int>{5}, 5, 5});

    // 3) Single negative element
    tests.push_back(TestCase{std::vector<int>{-3}, -3, -2});

    // 4) All zeros
    {
        std::vector<int> zeros(100, 0);
        tests.push_back(TestCase{zeros, 0, 0});
    }

    // 5) Increasing sequence
    {
        std::vector<int> inc(50);
        for (int i = 0; i < 50; ++i) inc[i] = i + 1;
        tests.push_back(TestCase{inc, 10, 100});
    }

    // 6) Decreasing negative sequence
    {
        std::vector<int> dec(50);
        for (int i = 0; i < 50; ++i) dec[i] = -(i + 1);
        tests.push_back(TestCase{dec, -100, -10});
    }

    // 7) Large magnitude values near int boundaries
    {
        std::vector<int> big = {INT_MAX, -INT_MAX, INT_MAX, -INT_MAX};
        tests.push_back(TestCase{big, -1000000000, 1000000000});
    }

    // 8) Deterministic pseudo-random values in [-100, 100], size 200
    {
        std::vector<int> rnd;
        rnd.reserve(200);
        uint32_t s = 123456789u;
        for (int i = 0; i < 200; ++i) {
            s = s * 1664525u + 1013904223u;
            int val = static_cast<int>(static_cast<int32_t>(s % 201) - 100);
            rnd.push_back(val);
        }
        tests.push_back(TestCase{rnd, -50, 50});
    }

    // 9) Repeating pattern, size 500
    {
        std::vector<int> pattern;
        pattern.reserve(500);
        int base[] = {-3, -1, 0, 1, 3, 5, -5};
        for (int i = 0; i < 500; ++i) {
            pattern.push_back(base[i % 7]);
        }
        tests.push_back(TestCase{pattern, -10, 10});
    }

    // 10) Sparse spikes with large positives/negatives
    {
        std::vector<int> sparse(300, 0);
        for (int i = 0; i < 300; ++i) {
            if (i % 30 == 0) sparse[i] += 1000;
            if (i % 45 == 0) sparse[i] -= 1200;
        }
        tests.push_back(TestCase{sparse, -1500, 1500});
    }

    Solution sol;

    // Benchmark
    const int iterations = 1000;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.countRangeSum(tests[i].nums, tests[i].lower, tests[i].upper);
            // Mix into checksum to avoid optimization
            checksum += static_cast<long long>(res) ^ (static_cast<long long>(iter) * 1315423911LL + static_cast<long long>(i));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}