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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Empty array
    tests.push_back(TestCase{vector<int>{}, 0});

    // 2) Single prime element
    tests.push_back(TestCase{vector<int>{7}, 0});

    // 3) Single element equals 1
    tests.push_back(TestCase{vector<int>{1}, 0});

    // 4) All evens
    vector<int> t4(10, 4);
    tests.push_back(TestCase{t4, 2});

    // 5) All primes (odd), gcd of any segment > 1 unlikely
    tests.push_back(TestCase{vector<int>{5, 7, 11, 13, 17, 19, 23, 29, 31, 37}, 0});

    // 6) Mixed evens and odds
    tests.push_back(TestCase{vector<int>{2, 4, 6, 9, 3, 15, 10, 5, 25, 50, 75}, 1});

    // 7) Large array of ones
    vector<int> t7(500, 1);
    tests.push_back(TestCase{t7, 0});

    // 8) Patterned array with many multiples
    vector<int> t8;
    t8.reserve(300);
    int pattern8[] = {6, 10, 15, 21, 14, 22};
    for (int rep = 0; rep < 50; ++rep) {
        for (int v : pattern8) t8.push_back(v);
    }
    tests.push_back(TestCase{t8, 50});

    // 9) Array with zeros interspersed
    tests.push_back(TestCase{vector<int>{0, 0, 4, 0, 8, 0, 16, 0, 3, 0, 9, 0}, 3});

    // 10) Negatives and large numbers
    tests.push_back(TestCase{vector<int>{-4, -8, 12, -16, 24, -36, 48, -60, 2147483646, -2147483646, 1000000000, -1000000000}, 5});

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            int res = sol.minStable(tc.nums, tc.maxC);
            checksum += res;
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}