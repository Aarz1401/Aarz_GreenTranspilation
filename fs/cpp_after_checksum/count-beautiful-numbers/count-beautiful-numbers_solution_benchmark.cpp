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
#include <utility>
#include <cstdint>
#include <chrono>

using namespace std;

class Solution {
public:
    long long beautifulNumbers(long long l, long long r) {
        auto count = [&](long long x) -> long long {
            if (x < 0) return 0;
            string s = to_string(x);

            struct Key {
                long long mul;
                int total;
            };
            struct KeyHash {
                size_t operator()(const Key& k) const noexcept {
                    size_t h1 = std::hash<long long>{}(k.mul);
                    size_t h2 = std::hash<int>{}(k.total);
                    // hash combine
                    return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
                }
            };
            struct KeyEq {
                bool operator()(const Key& a, const Key& b) const noexcept {
                    return a.mul == b.mul && a.total == b.total;
                }
            };

            vector<unordered_map<Key, long long, KeyHash, KeyEq>> dp(2);
            dp[1][Key{1LL, 0}] = 1LL;

            for (char ch : s) {
                int c = ch - '0';
                vector<unordered_map<Key, long long, KeyHash, KeyEq>> new_dp(2);
                for (int b = 0; b < 2; ++b) {
                    for (const auto& kv : dp[b]) {
                        const Key& st = kv.first;
                        long long cnt = kv.second;
                        int limit = b ? c : 9;
                        for (int xd = 0; xd <= limit; ++xd) {
                            bool nb = b && (xd == c);
                            long long nmul = st.mul * ((st.total == 0 && xd == 0) ? 1LL : (long long)xd);
                            int ntotal = st.total + xd;
                            new_dp[nb][Key{nmul, ntotal}] += cnt;
                        }
                    }
                }
                dp.swap(new_dp);
            }

            long long result = 0;
            for (int b = 0; b < 2; ++b) {
                for (const auto& kv : dp[b]) {
                    const Key& st = kv.first;
                    long long cnt = kv.second;
                    if (st.total != 0 && st.mul % st.total == 0) {
                        result += cnt;
                    }
                }
            }
            return result;
        };

        return count(r) - count(l - 1);
    }
};

int main() {
    // Define 10 diverse test ranges
    vector<pair<long long, long long>> tests = {
        {0LL, 0LL},
        {1LL, 9LL},
        {10LL, 99LL},
        {100LL, 1000LL},
        {1LL, 1000000LL},
        {123456789LL, 987654321LL},
        {999999000000LL, 1000000000000LL},
        {555555555555555LL, 555555555555999LL},
        {1000000000000000LL, 1000000000010000LL},
        {314159265358979LL, 314159265359000LL}
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            long long res = sol.beautifulNumbers(t.first, t.second);
            checksum += static_cast<unsigned long long>(res) ^ static_cast<unsigned long long>(iter + 1);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}