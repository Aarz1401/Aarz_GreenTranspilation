#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

static vector<int> global_cnt = {0, 0};

class Solution {
public:
    int countKReducibleNumbers(string s, int k) {
        const int MOD = 1000000007;
        int n = static_cast<int>(s.size());

        // Ensure cnt is computed up to index n-1
        while ((int)global_cnt.size() <= n - 1) {
            int idx = (int)global_cnt.size();
            int pc = __builtin_popcount((unsigned int)idx);
            global_cnt.push_back(global_cnt[pc] + 1);
        }

        vector<long long> dp(n, 0);
        int curr = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                dp[j + 1] = (dp[j + 1] + dp[j]) % MOD;
            }
            if (s[i] != '1') {
                continue;
            }
            dp[curr] = (dp[curr] + 1) % MOD;
            curr += 1;
        }

        long long result = 0;
        for (int i = 1; i < n; ++i) {
            if (global_cnt[i] < k) {
                result = (result + dp[i]) % MOD;
            }
        }
        return (int)(result % MOD);
    }
};

static string makeAlternating(int len, char a = '1', char b = '0') {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s.push_back((i % 2 == 0) ? a : b);
    return s;
}

static string makeAll(int len, char c) {
    return string(max(0, len), c);
}

static string makePattern100(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s.push_back((i % 3 == 0) ? '1' : '0');
    return s;
}

static string makePrimeOnes(int len) {
    if (len <= 0) return "";
    vector<bool> is_prime(len, true);
    if (len > 0) is_prime[0] = false;
    if (len > 1) is_prime[1] = false;
    for (int i = 2; i * i < len; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < len; j += i) is_prime[j] = false;
        }
    }
    string s(len, '0');
    for (int i = 2; i < len; ++i) if (is_prime[i]) s[i] = '1';
    return s;
}

static string makeDeterministicPseudo(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        int v = (i * i + 31 * i + 7);
        s.push_back(((v & 7) < 3) ? '1' : '0'); // ~3/8 ones
    }
    return s;
}

int main() {
    // Generate 10 diverse test inputs (string s, int k)
    vector<pair<string, int>> tests;
    tests.emplace_back(string(""), 0);                               // 1) empty string
    tests.emplace_back(string("0"), 1);                              // 2) single zero
    tests.emplace_back(string("1"), 1);                              // 3) single one
    tests.emplace_back(makeAlternating(10), 2);                      // 4) alternating length 10
    tests.emplace_back(makeAll(32, '1'), 3);                         // 5) all ones length 32
    tests.emplace_back(makeAll(64, '0'), 4);                         // 6) all zeros length 64
    tests.emplace_back(makePattern100(75), 2);                       // 7) "1" every 3rd position length 75
    tests.emplace_back(makeAlternating(128), 5);                     // 8) alternating length 128
    tests.emplace_back(makePrimeOnes(200), 4);                       // 9) ones at prime indices length 200
    tests.emplace_back(makeDeterministicPseudo(256), 6);             // 10) deterministic pseudo-random length 256

    Solution sol;

    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += sol.countKReducibleNumbers(tc.first, tc.second);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = elapsed_ns / 1e6;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}