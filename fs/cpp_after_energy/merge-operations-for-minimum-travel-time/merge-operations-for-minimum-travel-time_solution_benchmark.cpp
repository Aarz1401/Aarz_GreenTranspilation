#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <chrono>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
    vector<Test> tests;
    tests.push_back(Test{10, 2, 0, {0, 5}, {3, 4}});
    tests.push_back(Test{20, 3, 1, {0, 2, 7}, {1, 2, 3}});
    tests.push_back(Test{50, 4, 1, {0, 10, 20, 35}, {5, 2, 4, 1}});
    tests.push_back(Test{100, 5, 2, {0, 5, 15, 30, 50}, {1, 3, 2, 6, 4}});
    tests.push_back(Test{200, 6, 3, {0, 2, 6, 14, 15, 30}, {2, 2, 3, 1, 5, 4}});
    tests.push_back(Test{150, 7, 4, {0, 3, 8, 9, 15, 21, 28}, {3, 1, 4, 2, 6, 5, 2}});
    tests.push_back(Test{300, 8, 5, {0, 1, 2, 6, 10, 15, 21, 28}, {2, 2, 1, 3, 4, 5, 6, 7}});
    tests.push_back(Test{500, 9, 6, {0, 4, 5, 11, 18, 26, 35, 45, 56}, {1, 3, 2, 4, 6, 5, 3, 2, 1}});
    tests.push_back(Test{800, 10, 7, {0, 2, 5, 9, 14, 20, 27, 35, 44, 54}, {5, 4, 3, 2, 1, 2, 3, 4, 5, 6}});
    tests.push_back(Test{1000, 12, 8, {0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66}, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}});

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            int result = sol.minTravelTime(t.l, t.n, t.k, t.position, t.time);
            checksum += result;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed << "\n";
    return 0;
}