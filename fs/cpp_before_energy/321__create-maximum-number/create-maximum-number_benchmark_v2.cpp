#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// Time:  O(k * (m + n + k)) ~ O(k * (m + n + k^2))
// Space: O(m + n + k^2)

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        auto get_max_digits = [&](const vector<int>& nums, int start, int end, vector<vector<int>>& max_digits) {
            if (start > end) return;
            max_digits[end] = max_digit(nums, end);
            for (int i = end - 1; i >= start; --i) {
                max_digits[i] = delete_digit(max_digits[i + 1]);
            }
        };

        auto merge_vec = [&](const vector<int>& a, const vector<int>& b) {
            vector<int> res;
            res.reserve(a.size() + b.size());
            int i = 0, j = 0;
            while (i < (int)a.size() || j < (int)b.size()) {
                if (greater_sub(a, i, b, j)) {
                    res.push_back(a[i++]);
                } else {
                    res.push_back(b[j++]);
                }
            }
            return res;
        };

        int m = nums1.size(), n = nums2.size();

        vector<vector<int>> max_digits1(k + 1), max_digits2(k + 1);
        int start1 = max(0, k - n), end1 = min(k, m);
        int start2 = max(0, k - m), end2 = min(k, n);

        get_max_digits(nums1, start1, end1, max_digits1);
        get_max_digits(nums2, start2, end2, max_digits2);

        vector<int> best;
        for (int i = start1; i <= end1; ++i) {
            int j = k - i;
            vector<int> candidate = merge_vec(max_digits1[i], max_digits2[j]);
            if (best.empty() || greater_sub(candidate, 0, best, 0)) {
                best = move(candidate);
            }
        }
        return best;
    }

private:
    static vector<int> max_digit(const vector<int>& nums, int k) {
        int drop = (int)nums.size() - k;
        vector<int> res;
        res.reserve(nums.size());
        for (int num : nums) {
            while (drop && !res.empty() && res.back() < num) {
                res.pop_back();
                --drop;
            }
            res.push_back(num);
        }
        if ((int)res.size() > k) res.resize(k);
        return res;
    }

    static vector<int> delete_digit(const vector<int>& nums) {
        vector<int> res(nums);
        for (int i = 0; i < (int)res.size(); ++i) {
            if (i == (int)res.size() - 1 || res[i] < res[i + 1]) {
                res.erase(res.begin() + i);
                break;
            }
        }
        return res;
    }

    static bool greater_sub(const vector<int>& a, int i, const vector<int>& b, int j) {
        int n = a.size(), m = b.size();
        while (i < n && j < m && a[i] == b[j]) {
            ++i; ++j;
        }
        if (j == m) return true;      // b exhausted -> a is >= b
        if (i == n) return false;     // a exhausted -> a is < b
        return a[i] > b[j];
    }
};

struct TestCase {
    vector<int> a;
    vector<int> b;
    int k;
};

int main() {
    Solution sol;
    vector<TestCase> tests = {
        {{3,4,6,5}, {9,1,2,5,8,3}, 5},
        {{6,7}, {6,0,4}, 5},
        {{3,9}, {8,9}, 3},
        {{1,2,3,4,5}, {5,4,3,2,1}, 5},
        {{9,9,9,9}, {9,9,9}, 6},
        {{1}, {2,3,4,5,6,7,8,9}, 4},
        {{8,6,9}, {1,7,5}, 5},
        {{2,5,6,4,4,0}, {7,3,8,0,6,5,7,6,2}, 15},
        {{5,2,1,9,0}, {3,9,5,6}, 6},
        {{0,0,0,0,0,0}, {0,0,0,0}, 7}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            auto res = sol.maxNumber(tc.a, tc.b, tc.k);
            DoNotOptimize(res); 
            // int s = 0;
            // for (int v : res) s += v;
            // checksum += s;
        }
        //sink = checksum;
    }
    return 0;
}