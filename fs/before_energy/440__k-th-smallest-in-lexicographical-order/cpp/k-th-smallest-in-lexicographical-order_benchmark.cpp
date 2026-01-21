#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <functional>
#include <chrono>

class Solution {
public:
    int findKthNumber(int n, int k) {
        long long result = 0;

        // Precompute counts
        std::vector<long long> cnts(11, 0);
        for (int i = 1; i <= 10; ++i) {
            cnts[i] = cnts[i - 1] * 10 + 1;
        }

        // Extract digits of n (least significant first)
        std::vector<int> nums;
        long long temp = n;
        while (temp) {
            nums.push_back(static_cast<int>(temp % 10));
            temp /= 10;
        }

        long long total = n, target = 0;
        int i = static_cast<int>(nums.size()) - 1;
        long long kk = k;
        while (i >= 0 && kk > 0) {
            target = target * 10 + nums[i];
            int start = (i == static_cast<int>(nums.size()) - 1) ? 1 : 0;
            for (int j = start; j <= 9; ++j) {
                long long candidate = result * 10 + j;
                long long num = 0;
                if (candidate < target) {
                    num = cnts[i + 1];
                } else if (candidate > target) {
                    num = cnts[i];
                } else {
                    num = total - cnts[i + 1] * (j - start) - cnts[i] * (9 - j);
                }
                if (kk > num) {
                    kk -= num;
                } else {
                    result = candidate;
                    kk -= 1;
                    total = num - 1;
                    break;
                }
            }
            --i;
        }

        return static_cast<int>(result);
    }
};

// Alternative solution for reference
class Solution2 {
public:
    int findKthNumber(int n, int k) {
        auto count = [](long long n, long long prefix) {
            long long result = 0, number = 1;
            while (prefix <= n) {
                result += number;
                prefix *= 10;
                number *= 10;
            }
            result -= std::max(number / 10 - (n - prefix / 10 + 1), 0LL);
            return result;
        };

        std::function<std::pair<long long, long long>(long long, long long, long long, long long)> helper =
            [&](long long n, long long k, long long cur, long long index) -> std::pair<long long, long long> {
                if (cur) {
                    index += 1;
                    if (index == k) {
                        return {cur, index};
                    }
                }

                int i = (cur == 0) ? 1 : 0;
                while (i <= 9) {
                    cur = cur * 10 + i;
                    long long cnt = count(n, cur);
                    if (k > cnt + index) {
                        index += cnt;
                    } else if (cur <= n) {
                        auto res = helper(n, k, cur, index);
                        if (res.first) {
                            return res;
                        }
                    }
                    ++i;
                    cur /= 10;
                }
                return {0, index};
            };

        return static_cast<int>(helper(n, k, 0, 0).first);
    }
};

int main() {
    Solution solver;

    // 10 diverse test inputs (n, k)
    std::vector<std::pair<int, int>> tests = {
        {1, 1},
        {13, 2},
        {1000, 1},
        {1000, 1000},
        {999999937, 123456789},
        {1000000000, 1000000000},
        {500000000, 250000000},
        {10, 10},
        {271828182, 31415926},
        {987654321, 87654321}
    };

    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        long long local_sum = 0;
        for (const auto& tc : tests) {
            local_sum += solver.findKthNumber(tc.first, tc.second);
        }
        checksum += local_sum;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << std::endl;
    std::cout << "Elapsed time (ns): " << elapsed_ns << std::endl;

    return 0;
}