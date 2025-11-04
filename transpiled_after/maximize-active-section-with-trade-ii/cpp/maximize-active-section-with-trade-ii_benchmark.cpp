#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>
#include <utility>
using namespace std;

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<TestCase> tests;

    // 1) Empty string, no queries
    tests.push_back(TestCase{
        "",
        {}
    });

    // 2) Single zero
    tests.push_back(TestCase{
        "0",
        {{0,0}}
    });

    // 3) Single one
    tests.push_back(TestCase{
        "1",
        {{0,0}}
    });

    // 4) All zeros
    tests.push_back(TestCase{
        "0000000",
        {{0,6}, {1,5}, {3,3}, {2,4}}
    });

    // 5) All ones
    tests.push_back(TestCase{
        "1111111",
        {{0,6}, {1,5}, {3,3}, {2,4}}
    });

    // 6) Alternating pattern
    tests.push_back(TestCase{
        "010101010101",
        {{0,11}, {1,10}, {2,9}, {5,5}, {0,0}, {11,11}}
    });

    // 7) Mixed runs with adjacent zero runs queries
    tests.push_back(TestCase{
        "001110000111",
        {{0,11}, {1,3}, {4,7}, {8,11}, {2,8}}
    });

    // 8) Repeating blocks of zeros and ones
    tests.push_back(TestCase{
        "0000111100001111",
        {{0,15}, {4,7}, {8,11}, {12,15}, {3,12}, {6,9}}
    });

    // 9) Random-looking pattern
    tests.push_back(TestCase{
        "1011001110001111",
        {{0,15}, {0,3}, {4,7}, {8,11}, {12,15}, {5,10}}
    });

    // 10) Long zero prefix then ones
    tests.push_back(TestCase{
        "00000000011111",
        {{0,13}, {0,8}, {5,13}, {7,10}, {2,2}}
    });

    Solution sol;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long long total = 0;
    const int iterations = 1000;

    for (int iter = 0; iter < iterations; ++iter) {
        for (auto &tc : tests) {
            vector<int> res = sol.maxActiveSectionsAfterTrade(tc.s, tc.queries);
            for (int v : res) total += v;
            total += static_cast<long long>(res.size());
        }
    }

    auto end = high_resolution_clock::now();
    auto ms = duration_cast<milliseconds>(end - start).count();

    cout << "Total: " << total << "\n";
    cout << "Elapsed ms: " << ms << "\n";

    return 0;
}