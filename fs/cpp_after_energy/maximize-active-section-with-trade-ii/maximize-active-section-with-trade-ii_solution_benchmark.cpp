#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>
#include <utility>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    // Sparse Table for Range Maximum Query (RMQ)
    struct SparseTableMax {
        vector<vector<int>> st;
        vector<int> logs;
        int n = 0;
        int K = 0;

        SparseTableMax() {}

        SparseTableMax(const vector<int>& arr) {
            build(arr);
        }

        void build(const vector<int>& arr) {
            n = static_cast<int>(arr.size());
            if (n == 0) {
                K = 0;
                st.clear();
                logs.assign(1, 0);
                return;
            }
            logs.assign(n + 1, 0);
            for (int i = 2; i <= n; ++i) {
                logs[i] = logs[i / 2] + 1;
            }
            K = logs[n];
            st.assign(K + 1, vector<int>(n));
            st[0] = arr;
            for (int k = 1; k <= K; ++k) {
                int len = 1 << k;
                int half = len >> 1;
                for (int i = 0; i + len <= n; ++i) {
                    st[k][i] = std::max(st[k - 1][i], st[k - 1][i + half]);
                }
            }
        }

        int query(int L, int R) const {
            if (L > R) return INT_MIN;
            int len = R - L + 1;
            int k = logs[len];
            return std::max(st[k][L], st[k][R - (1 << k) + 1]);
        }
    };

    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = static_cast<int>(s.size());
        vector<int> lookup(n, -1);
        vector<pair<int, int>> idxs;  // pairs of (start_index, length) for consecutive '0' runs
        int cnt1 = 0;

        for (int i = 0; i < n; ++i) {
            char x = s[i];
            if (x == '0') {
                if (i - 1 >= 0 && s[i - 1] == '0') {
                    idxs.back().second += 1;
                } else {
                    idxs.emplace_back(i, 1);
                }
            } else {
                cnt1 += 1;
            }
            lookup[i] = static_cast<int>(idxs.size()) - 1;
        }

        if (idxs.empty()) {
            return vector<int>(queries.size(), cnt1);
        }

        int m = static_cast<int>(idxs.size());
        vector<int> arr(max(0, m - 1), 0);
        for (int i = 0; i + 1 < m; ++i) {
            arr[i] = idxs[i].second + idxs[i + 1].second;
        }

        SparseTableMax st(arr);
        vector<int> result(queries.size(), cnt1);

        for (size_t qi = 0; qi < queries.size(); ++qi) {
            int l = queries[qi][0];
            int r = queries[qi][1];

            int left = lookup[l] + 1;
            int right = lookup[r] - (s[r] == '0' ? 1 : 0);

            int left_cnt = (lookup[l] != -1) ? (idxs[lookup[l]].second - (l - idxs[lookup[l]].first)) : -1;
            int right_cnt = (lookup[r] != -1) ? (r - idxs[lookup[r]].first + 1) : -1;

            if (left <= right - 1) {
                result[qi] = max(result[qi], cnt1 + st.query(left, right - 1));
            }
            if (s[l] == '0' && s[r] == '0' && lookup[l] + 1 == lookup[r]) {
                result[qi] = max(result[qi], cnt1 + left_cnt + right_cnt);
            }
            if (s[l] == '0' && lookup[l] + 1 <= right) {
                result[qi] = max(result[qi], cnt1 + left_cnt + idxs[lookup[l] + 1].second);
            }
            if (s[r] == '0' && left <= lookup[r] - 1) {
                result[qi] = max(result[qi], cnt1 + right_cnt + idxs[lookup[r] - 1].second);
            }
        }

        return result;
    }
};

struct TestCase {
    string s;
    vector<vector<int>> queries;
};

int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) All zeros
    {
        TestCase tc;
        tc.s = string(10, '0');
        tc.queries = {
            {0, 9}, {0, 0}, {9, 9}, {2, 7}, {1, 2}
        };
        tests.push_back(std::move(tc));
    }

    // 2) All ones
    {
        TestCase tc;
        tc.s = string(10, '1');
        tc.queries = {
            {0, 9}, {1, 1}, {4, 7}, {0, 0}, {9, 9}
        };
        tests.push_back(std::move(tc));
    }

    // 3) Alternating pattern
    {
        TestCase tc;
        int n = 31;
        tc.s.reserve(n);
        for (int i = 0; i < n; ++i) tc.s.push_back((i % 2 == 0) ? '0' : '1');
        tc.queries = {
            {0, 30}, {1, 29}, {2, 2}, {15, 15}, {8, 23}, {10, 20}
        };
        tests.push_back(std::move(tc));
    }

    // 4) Clustered runs of zeros and ones
    {
        TestCase tc;
        tc.s = "000111000111000111";
        tc.queries = {
            {0, 5}, {3, 8}, {6, 11}, {12, 17}, {9, 15}, {0, 17}
        };
        tests.push_back(std::move(tc));
    }

    // 5) Zeros at ends, ones in middle
    {
        TestCase tc;
        tc.s = "00011111000";
        tc.queries = {
            {0, 10}, {0, 2}, {8, 10}, {3, 7}, {2, 8}
        };
        tests.push_back(std::move(tc));
    }

    // 6) Single zero
    {
        TestCase tc;
        tc.s = "0";
        tc.queries = {
            {0, 0}
        };
        tests.push_back(std::move(tc));
    }

    // 7) Single one
    {
        TestCase tc;
        tc.s = "1";
        tc.queries = {
            {0, 0}
        };
        tests.push_back(std::move(tc));
    }

    // 8) Mixed small with zero blocks at ends
    {
        TestCase tc;
        tc.s = "0011100";
        tc.queries = {
            {0, 6}, {0, 1}, {5, 6}, {2, 4}, {1, 5}
        };
        tests.push_back(std::move(tc));
    }

    // 9) Irregular pattern with varying run lengths
    {
        TestCase tc;
        tc.s = "101010001110000101011110000";
        tc.queries = {
            {0, 26}, {3, 5}, {7, 14}, {10, 16}, {20, 26}, {12, 12}
        };
        tests.push_back(std::move(tc));
    }

    // 10) Large patterned case
    {
        TestCase tc;
        string pattern = "00001111";
        int repeats = 625; // 8 * 625 = 5000
        tc.s.reserve(repeats * (int)pattern.size());
        for (int i = 0; i < repeats; ++i) tc.s += pattern;

        vector<vector<int>> q;
        q.push_back({0, (int)tc.s.size() - 1});
        for (int seg = 0; seg < 10; ++seg) {
            int l = seg * 500;
            int r = min((int)tc.s.size() - 1, l + 300);
            q.push_back({l, r});
        }
        for (int seg = 0; seg < 10; ++seg) {
            int l = seg * 250;
            int r = min((int)tc.s.size() - 1, l + 200);
            q.push_back({l, r});
        }
        q.push_back({123, 4567});
        q.push_back({1000, 2000});
        q.push_back({2500, 3500});
        q.push_back({4000, 4500});
        q.push_back({0, 0});
        q.push_back({(int)tc.s.size() - 1, (int)tc.s.size() - 1});
        tc.queries = std::move(q);
        tests.push_back(std::move(tc));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            auto res = sol.maxActiveSectionsAfterTrade(tests[ti].s, tests[ti].queries);
            for (size_t i = 0; i < res.size(); ++i) {
                checksum += res[i] + (long long)iter + (long long)ti + (long long)i;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}