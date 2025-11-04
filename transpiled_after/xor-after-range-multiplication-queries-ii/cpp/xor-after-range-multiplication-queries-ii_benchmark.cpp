#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <chrono>

using namespace std;

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
    // Define 10 diverse test cases
    vector<TestCase> tests;

    // Test 1: Single element, simple small-k update
    tests.push_back(TestCase{
        {5},
        {
            {0, 0, 1, 3}
        }
    });

    // Test 2: Mixed small and large k on small array
    tests.push_back(TestCase{
        {1, 2, 3, 4, 5},
        {
            {0, 4, 1, 2},  // small k=1
            {0, 4, 4, 3},  // large k=4
            {1, 3, 2, 5}   // small k=2
        }
    });

    // Test 3: rprime both < n and >= n, mixed k
    tests.push_back(TestCase{
        {0,1,2,3,4,5,6,7,8,9},
        {
            {0, 3, 2, 7},   // small k=2, rprime < n
            {2, 8, 3, 11},  // small k=3, rprime >= n
            {1, 9, 7, 13}   // large k=7
        }
    });

    // Test 4: Single index updates, large multiplier near MOD, inverse used
    tests.push_back(TestCase{
        {2,3,5,7,11,13,17,19},
        {
            {3, 3, 2, 17},          // small k=2, rprime < n
            {0, 7, 4, 1000000006},  // large k=4, v = MOD-1
            {1, 6, 3, 29}           // small k=3, rprime < n
        }
    });

    // Test 5: Include zero multiplier on large-k, mix with small-k
    tests.push_back(TestCase{
        {1,2,3,4,5,6,7,8,9,10,11,12},
        {
            {0, 11, 5, 0},     // large k=5, zero multiplier
            {0, 11, 1, 2},     // small k=1
            {2, 10, 6, 123456} // large k=6
        }
    });

    // Test 6: Negative multiplier, large and small k, MOD-1
    tests.push_back(TestCase{
        {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
        {
            {0, 15, 4, -3},          // small k=4, negative multiplier
            {5, 10, 6, 9},           // large k=6
            {2, 14, 5, 1000000006}   // small k=5, v = MOD-1
        }
    });

    // Test 7: Two elements, small and large k
    tests.push_back(TestCase{
        {42, 7},
        {
            {0, 1, 2, 3},  // small k=2
            {0, 1, 3, 5}   // large k=3
        }
    });

    // Test 8: k equals block size, big v, mixed k
    tests.push_back(TestCase{
        {3,1,4,1,5,9,2,6,5},
        {
            {0, 8, 4, 2147483647}, // small k=4, big v
            {2, 7, 5, 123456789},  // large k=5
            {1, 1, 1, 37}          // small k=1, rprime < n
        }
    });

    // Test 9: No queries
    tests.push_back(TestCase{
        {0, 0, 0},
        {
            // empty
        }
    });

    // Test 10: Larger array, multiple mixed queries
    tests.push_back(TestCase{
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {
            {0, 19, 1, 999999937}, // small k=1
            {5, 15, 5, 77},        // small k=5
            {2, 18, 6, 12345},     // large k=6
            {3, 17, 2, 31}         // small k=2, rprime < n
        }
    });

    Solution sol;
    const int iterations = 1000;
    long long accumulator = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            vector<int> nums = tc.nums; // copy because function mutates nums
            // queries are not modified by the function; pass directly
            int res = sol.xorAfterQueries(nums, tc.queries);
            accumulator ^= res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Accumulator: " << accumulator << "\n";
    std::cout << "Elapsed time (ms): " << elapsed << "\n";

    return 0;
}