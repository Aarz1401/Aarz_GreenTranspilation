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
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
private:
    vector<int> gcdValuesImpl(const vector<int>& nums, const vector<long long>& queries) {
        if (nums.empty()) return vector<int>(queries.size(), 0);
        int r = *max_element(nums.begin(), nums.end());
        vector<long long> freq(r + 1, 0);
        for (int x : nums) {
            ++freq[x];
        }
        vector<long long> cnt2(r + 1, 0);
        for (int g = r; g >= 1; --g) {
            long long c = 0;
            for (int ng = g; ng <= r; ng += g) {
                c += freq[ng];
            }
            long long s = 0;
            for (int ng = g + g; ng <= r; ng += g) {
                s += cnt2[ng];
            }
            cnt2[g] = c * (c - 1) / 2 - s;
        }
        vector<long long> prefix(r + 2, 0);
        for (int i = 0; i <= r; ++i) {
            prefix[i + 1] = prefix[i] + cnt2[i];
        }
        vector<int> result;
        result.reserve(queries.size());
        for (long long q : queries) {
            auto it = upper_bound(prefix.begin(), prefix.end(), q);
            int idx = static_cast<int>(it - prefix.begin()) - 1;
            result.push_back(idx);
        }
        return result;
    }
public:
    vector<int> gcdValues(vector<int>& nums, vector<int>& queries) {
        vector<long long> qll(queries.size());
        for (size_t i = 0; i < queries.size(); ++i) qll[i] = static_cast<long long>(queries[i]);
        return gcdValuesImpl(nums, qll);
    }
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        return gcdValuesImpl(nums, queries);
    }
};
