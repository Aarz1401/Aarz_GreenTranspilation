#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

int main() {
    Solution sol;
    vector<vector<int>> tests;
    tests.push_back({1,2,3,4,5,6,7,8,9,10});
    tests.push_back(vector<int>(20, 7));
    tests.push_back({2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97});
    tests.push_back({1,2,4,8,16,32,64,128,256,512});
    tests.push_back({12,18,6,3,9,15,21,27,24,30,36,42,45,48,54,60});
    tests.push_back({999,1000,996,972,945,930,875,840,768,720,660,648,600,588,576});
    tests.push_back({60,59,58,57,56,55,54,53,52,51,50});
    tests.push_back({2000,1995,1980,1920,1800,1600,1500,1400,1350,1300});
    tests.push_back({101,103,107,109,113,127,131,137,139,149});
    tests.push_back({2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3});

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            int res = sol.totalBeauty(tests[i]);
            checksum += res;
            if (checksum >= MOD) checksum -= MOD;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}