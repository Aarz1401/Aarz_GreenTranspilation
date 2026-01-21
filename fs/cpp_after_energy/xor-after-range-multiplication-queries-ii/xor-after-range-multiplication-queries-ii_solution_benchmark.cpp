#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <cstdint>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1000000007;
        auto mod_pow = [&](long long a, long long e) -> long long {
            a %= MOD;
            long long res = 1 % MOD;
            while (e > 0) {
                if (e & 1) res = (res * a) % MOD;
                a = (a * a) % MOD;
                e >>= 1;
            }
            return res;
        };
        auto inv = [&](long long x) -> long long {
            return mod_pow(x, MOD - 2);
        };

        int n = (int)nums.size();
        int block_size = (int)std::sqrt((double)n) + 1;

        unordered_map<int, vector<int>> diffs; // k -> diff array of size n initialized to 1

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = (int)((long long)q[3] % MOD);
            if (k <= block_size) {
                auto& diff = diffs[k];
                if (diff.empty()) diff.assign(n, 1);
                diff[l] = (int)((long long)diff[l] * v % MOD);
                int rprime = r + (k - ((r - l) % k));
                if (rprime < n) {
                    long long inv_v = inv(v);
                    diff[rprime] = (int)((long long)diff[rprime] * inv_v % MOD);
                }
            } else {
                for (int i = l; i <= r; i += k) {
                    nums[i] = (int)((long long)nums[i] * v % MOD);
                }
            }
        }

        for (auto& kv : diffs) {
            int k = kv.first;
            auto& diff = kv.second;
            for (int i = 0; i < n; ++i) {
                if (i - k >= 0) {
                    diff[i] = (int)((long long)diff[i] * diff[i - k] % MOD);
                }
                nums[i] = (int)((long long)nums[i] * diff[i] % MOD);
            }
        }

        int result = 0;
        for (int x : nums) {
            result ^= x;
        }
        return result;
    }
};

struct TestCase {
    vector<int> nums;
    vector<vector<int>> queries;
};

int main() {
    // Helper lambda to create diverse arrays
    auto makeArray = [](int n, int base, int modval) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (int)(((long long)i * base + 17) % modval) + 1;
        }
        return a;
    };

    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: Single element, small k, boundary v values
    {
        TestCase tc;
        tc.nums = {42};
        tc.queries = {
            {0, 0, 1, 2},
            {0, 0, 1, 1000000006}
        };
        tests.push_back(std::move(tc));
    }

    // Test 2: Small array with mixed ks
    {
        TestCase tc;
        tc.nums = {1, 2, 3, 4, 5};
        tc.queries = {
            {0, 4, 1, 3},
            {1, 3, 2, 5},
            {2, 2, 1, 7},
            {0, 4, 4, 11}
        };
        tests.push_back(std::move(tc));
    }

    // Test 3: n=100, mixed small/large ks
    {
        TestCase tc;
        tc.nums = makeArray(100, 37, 1000);
        tc.queries = {
            {0, 99, 50, 2},
            {10, 90, 60, 3},
            {5, 5, 1000, 1000000006},
            {20, 80, 7, 13},
            {0, 99, 11, 17}
        };
        tests.push_back(std::move(tc));
    }

    // Test 4: n=200, varied patterns and ks including boundaries
    {
        TestCase tc;
        tc.nums = makeArray(200, 73, 10000);
        tc.queries = {
            {0, 199, 2, 5},
            {50, 150, 3, 7},
            {1, 8, 3, 11},
            {20, 180, 4, 13},
            {0, 199, 100, 17},
            {50, 150, 10, 19},
            {0, 199, 5, 23},
            {10, 190, 97, 29}
        };
        tests.push_back(std::move(tc));
    }

    // Test 5: Empty array (no-op)
    {
        TestCase tc;
        tc.nums = {};
        tc.queries = {};
        tests.push_back(std::move(tc));
    }

    // Test 6: n=32, k at block boundary and beyond
    {
        TestCase tc;
        tc.nums = makeArray(32, 29, 2000);
        tc.queries = {
            {0, 31, 6, 7},
            {0, 31, 7, 11},
            {5, 25, 6, 17},
            {10, 10, 1000, 19},
            {3, 29, 6, 23}
        };
        tests.push_back(std::move(tc));
    }

    // Test 7: n=64, multiple overlapping small ks
    {
        TestCase tc;
        tc.nums = makeArray(64, 17, 5000);
        tc.queries = {
            {0, 63, 1, 3},
            {1, 62, 2, 5},
            {2, 60, 4, 7},
            {3, 59, 8, 11},
            {0, 63, 16, 13},
            {5, 55, 3, 97},
            {10, 20, 1, 1000000006},
            {0, 0, 64, 23}
        };
        tests.push_back(std::move(tc));
    }

    // Test 8: n=120, direct and diff mix, single index updates
    {
        TestCase tc;
        tc.nums = makeArray(120, 31, 1000);
        tc.queries = {
            {0, 0, 500, 2},
            {119, 119, 1000, 3},
            {0, 119, 5, 29},
            {10, 110, 25, 37},
            {5, 115, 6, 41},
            {20, 80, 11, 43},
            {50, 60, 100, 47}
        };
        tests.push_back(std::move(tc));
    }

    // Test 9: n=15, rprime >= n cases (no inverse placement)
    {
        TestCase tc;
        tc.nums = makeArray(15, 7, 100);
        tc.queries = {
            {0, 14, 5, 2},
            {0, 10, 5, 3},
            {1, 13, 4, 5},
            {2, 12, 6, 7}
        };
        tests.push_back(std::move(tc));
    }

    // Test 10: n=256, heavier mix including boundary and large ks
    {
        TestCase tc;
        tc.nums = makeArray(256, 67, 10000);
        tc.queries = {
            {0, 255, 17, 2},
            {0, 255, 18, 3},
            {100, 200, 5, 5},
            {50, 220, 9, 7},
            {0, 255, 64, 11},
            {10, 245, 32, 13},
            {123, 123, 1000, 97},
            {0, 255, 1, 1000000006},
            {5, 250, 7, 89},
            {80, 160, 40, 101}
        };
        tests.push_back(std::move(tc));
    }

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;

    auto start = high_resolution_clock::now();

    Solution sol;
    long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<int> nums = tests[i].nums;
            vector<vector<int>> queries = tests[i].queries;
            int res = sol.xorAfterQueries(nums, queries);
            checksum += (res ^ static_cast<int>(i));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}