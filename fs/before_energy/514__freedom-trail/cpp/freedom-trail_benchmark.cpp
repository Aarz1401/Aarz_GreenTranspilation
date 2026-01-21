#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <chrono>
using namespace std;

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int R = ring.size();
        unordered_map<char, vector<int>> lookup;
        lookup.reserve(64);
        for (int i = 0; i < R; ++i) {
            lookup[ring[i]].push_back(i);
        }

        vector<vector<int>> dp(2, vector<int>(R, 0));
        vector<int> prev(1, 0);

        for (int i = 1; i <= (int)key.size(); ++i) {
            int cur = i & 1;
            int pre = (i - 1) & 1;
            for (int j = 0; j < R; ++j) dp[cur][j] = INT_MAX / 4;

            const auto& positions = lookup[key[i - 1]];
            for (int j : positions) {
                for (int k : prev) {
                    int cw = (j - k + R) % R;
                    int ccw = (k - j + R) % R;
                    int dist = min(cw, ccw);
                    dp[cur][j] = min(dp[cur][j], dp[pre][k] + dist);
                }
            }
            prev = positions;
        }

        int minSteps = INT_MAX;
        int idx = key.size() & 1;
        for (int v : dp[idx]) minSteps = min(minSteps, v);
        return minSteps + (int)key.size();
    }
};

int main() {
    vector<pair<string, string>> tests = {
        {"godding", "gd"},
        {"abcde", "ade"},
        {"aaaaa", "aaaaa"},
        {"abcdefghijklmnopqrstuvwxyz", "leetcode"},
        {"ababcababc", "cabba"},
        {"xyz", ""},
        {"zxyxzx", "xzxyzxz"},
        {"a", "aaaaaaa"},
        {"qwertyuiopasdfghjklzxcvbnmqwertyuiop", "pazbycqdxre"},
        {"aaaabaaaacaaaadaaaae", "edcba"}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.findRotateSteps(tests[i].first, tests[i].second);
            checksum += res + static_cast<int>(i) + iter;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = elapsed_ns / 1e6;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}