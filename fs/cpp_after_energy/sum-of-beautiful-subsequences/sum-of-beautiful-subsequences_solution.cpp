#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

static const int MOD = 1000000007;
static const int MAX_NUM = 70000;

class BIT {
public:
    // 0-indexed Fenwick tree
    BIT(int n) : bit(n + 1, 0) {}
    
    void add(int i, int val) {
        i += 1; // shift for dummy
        while (i < (int)bit.size()) {
            bit[i] += val;
            if (bit[i] >= MOD) bit[i] -= MOD;
            i += (i & -i);
        }
    }
    
    int query(int i) const {
        if (i < 0) return 0;
        i += 1; // shift for dummy
        int ret = 0;
        while (i > 0) {
            ret += bit[i];
            if (ret >= MOD) ret -= MOD;
            i -= (i & -i);
        }
        return ret;
    }
    
private:
    vector<int> bit;
};

const vector<vector<int>>& getFACTORS() {
    static vector<vector<int>> factors;
    if (factors.empty()) {
        factors.assign(MAX_NUM + 1, {});
        for (int i = 1; i <= MAX_NUM; ++i) {
            for (int j = i; j <= MAX_NUM; j += i) {
                factors[j].push_back(i);
            }
        }
    }
    return factors;
}

const vector<int>& getPHI() {
    static vector<int> phi;
    if (phi.empty()) {
        phi.resize(MAX_NUM + 1);
        for (int i = 0; i <= MAX_NUM; ++i) {
            phi[i] = i;
        }
        for (int i = 2; i <= MAX_NUM; ++i) {
            if (phi[i] == i) { // prime
                for (int j = i; j <= MAX_NUM; j += i) {
                    phi[j] -= phi[j] / i;
                }
            }
        }
    }
    return phi;
}

class Solution {
public:
    int totalBeauty(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        const auto& FACTORS = getFACTORS();
        const auto& PHI = getPHI();
        
        vector<vector<int>> lookup(mx + 1);
        for (int x : nums) {
            for (int d : FACTORS[x]) {
                lookup[d].push_back(x);
            }
        }
        
        vector<int> val_to_idx(mx + 1, 0);
        auto count = [&](const vector<int>& arr) -> int {
            int n = (int)arr.size();
            if (n == 0) return 0;
            vector<int> sorted_arr = arr;
            sort(sorted_arr.begin(), sorted_arr.end());
            for (int i = 0; i < n; ++i) {
                val_to_idx[sorted_arr[i]] = i; // last index for duplicates
            }
            BIT bit(n);
            for (int x : arr) {
                int idx = val_to_idx[x];
                int add = bit.query(idx - 1) + 1;
                if (add >= MOD) add -= MOD;
                bit.add(idx, add);
            }
            return bit.query(n - 1);
        };
        
        long long result = 0;
        for (int g = mx; g >= 1; --g) {
            int c = count(lookup[g]);
            result += (long long)PHI[g] * c % MOD;
            if (result >= MOD) result -= MOD;
        }
        return (int)result;
    }
};
