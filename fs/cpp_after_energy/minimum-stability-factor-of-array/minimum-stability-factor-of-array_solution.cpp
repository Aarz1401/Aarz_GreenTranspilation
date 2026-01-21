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
#include <numeric>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}
using namespace std::chrono;

class Solution {
public:
    struct SparseTableGCD {
        vector<vector<int>> st;
        vector<int> log2of;
        SparseTableGCD() {}
        explicit SparseTableGCD(const vector<int>& arr) {
            int n = arr.size();
            log2of.assign(n + 1, 0);
            for (int i = 2; i <= n; ++i) {
                log2of[i] = log2of[i / 2] + 1;
            }
            int k = (n > 0) ? log2of[n] : 0;
            st.assign(k + 1, vector<int>(n, 0));
            if (n > 0) {
                st[0] = arr;
                for (int i = 1; i <= k; ++i) {
                    int len = 1 << i;
                    int half = len >> 1;
                    for (int j = 0; j + len <= n; ++j) {
                        st[i][j] = std::gcd(st[i - 1][j], st[i - 1][j + half]);
                    }
                }
            }
        }
        int query(int L, int R) const {
            if (L > R) return 0;
            int i = log2of[R - L + 1];
            return std::gcd(st[i][L], st[i][R - (1 << i) + 1]);
        }
    };

    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        SparseTableGCD rmq(nums);
        auto check = [&](int l) -> bool {
            long long cnt = 0;
            int i = 0;
            while (i + l - 1 < n) {
                if (rmq.query(i, i + l - 1) >= 2) {
                    ++cnt;
                    i += l;
                } else {
                    ++i;
                }
            }
            return cnt > maxC;
        };

        int l = 1, r = n;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (!check(mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return r;
    }
};

struct TestCase {
    vector<int> nums;
    int maxC;
};
