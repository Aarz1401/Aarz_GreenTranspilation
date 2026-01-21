#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>

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
    Solution sol;
    vector<pair<long long, long long>> tests = {
        {0, 0},
        {1, 9},
        {10, 99},
        {100, 999},
        {0, 12345},
        {54321, 99999},
        {100000, 200000},
        {0, 999999},
        {123456, 123456},
        {700000, 765432}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += static_cast<int>(sol.beautifulNumbers(t.first, t.second));
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}