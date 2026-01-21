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
#include <chrono>
#include <utility>
#include <random>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int minLength(string s, int numOps) {
        int n = static_cast<int>(s.size());
        auto check = [&](int x) -> bool {
            if (x == 1) {
                int cnt = 0;
                for (int i = 0; i < n; ++i) {
                    int val = s[i] - '0';
                    if (val != (i % 2)) {
                        ++cnt;
                    }
                }
                return min(cnt, n - cnt) <= numOps;
            }
            long long ops = 0;
            int cnt = 1;
            for (int i = 1; i < n; ++i) {
                if (s[i] == s[i - 1]) {
                    ++cnt;
                } else {
                    ops += cnt / (x + 1);
                    cnt = 1;
                }
            }
            ops += cnt / (x + 1);
            return ops <= numOps;
        };

        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

static string makeAlternating(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(((i % 2 == 0) ? first : (first == '0' ? '1' : '0')));
    }
    return s;
}

static string makeRandom01(int n, unsigned seed) {
    string s;
    s.reserve(n);
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, 1);
    for (int i = 0; i < n; ++i) s.push_back(char('0' + dist(rng)));
    return s;
}

static string makeRuns(const vector<pair<char, int>>& runs) {
    string s;
    int total = 0;
    for (auto& r : runs) total += r.second;
    s.reserve(total);
    for (auto& r : runs) s.append(r.second, r.first);
    return s;
}

int main() {
    // Generate 10 diverse test inputs (string s, int numOps)
    vector<pair<string, int>> tests;
    tests.reserve(10);

    // 1) Single zero, zero ops
    tests.emplace_back(string("0"), 0);

    // 2) Single one, one op
    tests.emplace_back(string("1"), 1);

    // 3) Alternating even length, zero ops
    tests.emplace_back(makeAlternating(10, '0'), 0);

    // 4) Small mixed blocks, small ops
    tests.emplace_back(string("00110011"), 1);

    // 5) All zeros, moderate ops
    tests.emplace_back(string(100, '0'), 10);

    // 6) All ones, zero ops, odd length
    tests.emplace_back(string(257, '1'), 0);

    // 7) Random length 1000, arbitrary ops
    tests.emplace_back(makeRandom01(1000, 42u), 123);

    // 8) Long runs with varied sizes
    tests.emplace_back(
        makeRuns({
            {'0', 10}, {'1', 10}, {'0', 8}, {'1', 6}, {'0', 1}, {'1', 20}, {'0', 5}
        }),
        5
    );

    // 9) Mixed pattern with increasing/decreasing run lengths
    tests.emplace_back(
        makeRuns({
            {'0', 3}, {'1', 3}, {'0', 2}, {'1', 4}, {'0', 4}, {'1', 5}, {'0', 6}, {'1', 2}
        }),
        8
    );

    // 10) Larger random length 5000, higher ops
    tests.emplace_back(makeRandom01(5000, 2025u), 777);

    Solution sol;

    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.minLength(tests[i].first, tests[i].second);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}