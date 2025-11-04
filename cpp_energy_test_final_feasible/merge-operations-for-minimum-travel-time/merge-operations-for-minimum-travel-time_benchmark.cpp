#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <chrono>
using namespace std;

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + time[i];
        }

        vector<unordered_map<long long, long long>> dp(n), new_dp(n);
        dp[0][time[0]] = 0;

        for (int cnt = 2; cnt <= n - k; ++cnt) {
            for (int i = 0; i < n; ++i) new_dp[i].clear();
            for (int i = cnt - 1; i <= (cnt - 1) + k && i < n; ++i) {
                for (int j = cnt - 2; j <= i - 1; ++j) {
                    if (j < 0 || dp[j].empty()) continue;
                    long long tnew = prefix[i + 1] - prefix[j + 1];
                    long long dist = static_cast<long long>(position[i]) - static_cast<long long>(position[j]);
                    for (const auto& kv : dp[j]) {
                        long long t = kv.first;
                        long long c = kv.second;
                        long long val = dist * t + c;
                        auto it = new_dp[i].find(tnew);
                        if (it == new_dp[i].end() || val < it->second) {
                            new_dp[i][tnew] = val;
                        }
                    }
                }
            }
            dp.swap(new_dp);
        }

        long long ans = LLONG_MAX;
        for (const auto& kv : dp[n - 1]) {
            ans = min(ans, kv.second);
        }
        return static_cast<int>(ans);
    }
};

struct Test {
    int l;
    int n;
    int k;
    vector<int> position;
    vector<int> time;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Test> tests;
    tests.push_back(Test{10, 1, 0, {0}, {5}});
    tests.push_back(Test{100, 2, 0, {0, 10}, {2, 3}});
    tests.push_back(Test{20, 3, 1, {0, 5, 14}, {3, 1, 4}});
    tests.push_back(Test{9, 4, 2, {0, 2, 4, 8}, {1, 0, 2, 1}});
    tests.push_back(Test{16, 5, 2, {1, 3, 6, 10, 15}, {0, 2, 2, 0, 3}});
    tests.push_back(Test{15, 6, 3, {0, 1, 3, 6, 10, 15}, {5, 4, 3, 2, 1, 0}});
    tests.push_back(Test{40, 7, 2, {2, 5, 9, 14, 20, 27, 35}, {1, 1, 2, 3, 5, 8, 13}});
    tests.push_back(Test{45, 8, 3, {0, 3, 7, 12, 18, 25, 33, 42}, {2, 2, 2, 2, 2, 2, 2, 2}});
    tests.push_back(Test{35, 9, 4, {0, 4, 5, 9, 10, 15, 21, 22, 30}, {1, 0, 1, 0, 1, 0, 1, 0, 1}});
    tests.push_back(Test{100, 10, 5, {0, 10, 20, 21, 35, 36, 52, 70, 71, 90}, {9, 7, 5, 3, 1, 2, 4, 6, 8, 10}});

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int t = 0; t < 10; ++t) {
            const Test& tc = tests[t];
            checksum += sol.minTravelTime(tc.l, tc.n, tc.k, const_cast<vector<int>&>(tc.position), const_cast<vector<int>&>(tc.time));
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (ns): " << elapsed_ns << "\n";
    return 0;
}