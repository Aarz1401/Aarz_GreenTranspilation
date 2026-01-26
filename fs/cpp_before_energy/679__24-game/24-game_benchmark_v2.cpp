#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <cmath>
using namespace std;

// Time:  O(n^3 * 4^n) = O(1), n = 4
// Space: O(n^2) = O(1)
class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<double> a(nums.begin(), nums.end());
        return dfs(a);
    }

private:
    static constexpr double EPS = 1e-6;

    bool dfs(vector<double>& nums) {
        if (nums.size() == 1) {
            return fabs(nums[0] - 24.0) < EPS;
        }
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                vector<double> next;
                next.reserve(n - 1);
                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) next.push_back(nums[k]);
                }
                for (int op = 0; op < 4; ++op) {
                    // Skip duplicate computations for commutative ops (+, *)
                    if ((op == 0 || op == 2) && j > i) continue;
                    // Avoid division by zero
                    if (op == 3 && fabs(nums[j]) < EPS) continue;

                    double val = 0.0;
                    switch (op) {
                        case 0: val = nums[i] + nums[j]; break; // add
                        case 1: val = nums[i] - nums[j]; break; // sub
                        case 2: val = nums[i] * nums[j]; break; // mul
                        case 3: val = nums[i] / nums[j]; break; // truediv
                    }
                    next.push_back(val);
                    if (dfs(next)) return true;
                    next.pop_back();
                }
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> tests = {
        {4, 1, 8, 7},  // true
        {1, 2, 3, 4},  // true
        {3, 3, 8, 8},  // true
        {6, 6, 6, 6},  // true
        {1, 3, 4, 6},  // true
        {9, 1, 3, 4},  // true
        {7, 3, 1, 5},  // true
        {1, 1, 1, 1},  // false
        {2, 2, 2, 2},  // false
        {1, 1, 2, 2}   // false
    };

    Solution s;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& v : tests) {
            int r = s.judgePoint24(v);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}