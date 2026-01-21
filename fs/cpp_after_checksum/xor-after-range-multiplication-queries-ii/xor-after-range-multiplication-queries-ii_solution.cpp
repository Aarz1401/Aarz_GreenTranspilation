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
