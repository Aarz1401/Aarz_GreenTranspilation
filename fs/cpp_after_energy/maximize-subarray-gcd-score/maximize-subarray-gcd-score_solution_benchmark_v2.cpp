#include <vector>
#include <algorithm>
#include <unordered_map>
#include <array>
#include <climits>
#include <numeric>
#include <cstdint>
#include <utility>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

struct PairHash {
    size_t operator()(const pair<int, int>& p) const noexcept {
        return (static_cast<uint64_t>(static_cast<uint32_t>(p.first)) << 32) ^ static_cast<uint32_t>(p.second);
    }
};

class Solution {
public:
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        vector<int> lookup(n, 0);
        for (int i = 0; i < n; ++i) {
            while ((nums[i] & 1) == 0) {
                nums[i] >>= 1;
                lookup[i] += 1;
            }
        }
        int maxe = 0;
        for (int e : lookup) maxe = max(maxe, e);
        vector<vector<int>> lookup2(maxe + 1);
        for (int i = 0; i < n; ++i) {
            lookup2[lookup[i]].push_back(i);
        }

        long long result = 0;
        unordered_map<pair<int, int>, array<int, 2>, PairHash> dp;

        for (int i = 0; i < n; ++i) {
            unordered_map<pair<int, int>, array<int, 2>, PairHash> new_dp;
            // Initialize state starting at i
            pair<int, int> base_key = {nums[i], lookup[i]};
            new_dp.emplace(base_key, array<int,2>{i, i});

            // Transition from previous states
            for (const auto& kv : dp) {
                int g = kv.first.first;
                int e = kv.first.second;
                int v0 = kv.second[0];

                int ng = std::gcd(g, nums[i]);
                int ne = min(e, lookup[i]);
                pair<int,int> key = {ng, ne};

                auto it = new_dp.find(key);
                if (it == new_dp.end()) {
                    it = new_dp.emplace(key, array<int,2>{INT_MAX/4, INT_MAX/4}).first;
                }
                // Update earliest left index
                it->second[0] = min(it->second[0], v0);

                // Compute left index to ensure occurrences of exponent ne in [left..i] <= k
                const vector<int>& idxs = lookup2[ne];
                int left_idx = static_cast<int>(lower_bound(idxs.begin(), idxs.end(), v0) - idxs.begin());
                int right_idx = static_cast<int>(upper_bound(idxs.begin(), idxs.end(), i) - idxs.begin()) - 1;
                int cnt = (right_idx >= left_idx) ? (right_idx - left_idx + 1) : 0;

                int candidateLeft;
                if (cnt <= k) {
                    candidateLeft = v0;
                } else {
                    candidateLeft = idxs[right_idx - k] + 1;
                }
                it->second[1] = min(it->second[1], candidateLeft);
            }

            dp = std::move(new_dp);

            // Update result using current states ending at i
            for (const auto& kv : dp) {
                int g = kv.first.first;
                int e = kv.first.second;
                int v0 = kv.second[0];
                int v1 = kv.second[1];

                long long term1 = 1LL * g * (i - v0 + 1);
                term1 <<= e;
                result = max(result, term1);

                if (v1 <= i) {
                    long long term2 = 1LL * g * (i - v1 + 1);
                    term2 <<= (e + 1);
                    result = max(result, term2);
                }
            }
        }

        return result;
    }
};

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1}, 0},
        {{2}, 0},
        {{3, 6, 12, 24, 5, 10}, 1},
        {{7, 7, 7, 7}, 0},
        {{8, 4, 2, 1, 16, 32}, 2},
        {{9, 15, 21, 27, 33, 39, 45}, 3},
        {{100000, 50000, 25000, 12500}, 1},
        {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, 0},
        {{6, 10, 14, 22, 26, 34, 38}, 2},
        {{12, 18, 4, 9, 2, 3, 8, 6, 5, 7}, 1}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            vector<int> v = t.first;
            int k = t.second;
            long long r = sol.maxGCDScore(v, k);
            DoNotOptimize(r);
            //checksum += static_cast<int>(r);
        }
        //sink = checksum;
    }

    return 0;
}