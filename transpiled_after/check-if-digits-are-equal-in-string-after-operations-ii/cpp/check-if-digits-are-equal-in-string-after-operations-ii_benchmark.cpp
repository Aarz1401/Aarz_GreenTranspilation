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

using namespace std;

class Solution {
public:
    bool hasSameDigits(string s) {
        auto modpow = [](long long a, long long e, int mod) -> long long {
            long long r = 1 % mod;
            a %= mod;
            while (e > 0) {
                if (e & 1) r = (r * a) % mod;
                a = (a * a) % mod;
                e >>= 1;
            }
            return r;
        };

        auto check = [&](int mod) -> bool {
            auto decompose = [&](int x, int m) -> pair<int,int> { // x = a * m^cnt
                int cnt = 0;
                while (x > 1 && x % m == 0) {
                    x /= m;
                    cnt += 1;
                }
                return {x, cnt};
            };

            int result = 0;
            int cnt = 0;
            int curr = 1 % mod;
            int n = static_cast<int>(s.size());
            for (int i = 0; i < n - 1; ++i) {
                if (cnt == 0) {
                    int diff = int(s[i]) - int(s[i + 1]);
                    int term = (int)((1LL * curr * ((diff % mod + mod) % mod)) % mod);
                    result += term;
                    result %= mod;
                }
                auto p1 = decompose((n - 2) - i, mod);
                int x1 = p1.first, c1 = p1.second;
                curr = (int)((1LL * curr * (x1 % mod)) % mod);
                cnt += c1;

                auto p2 = decompose(i + 1, mod);
                int x2 = p2.first, c2 = p2.second;
                curr = (int)((1LL * curr * modpow(x2 % mod, mod - 2, mod)) % mod);
                cnt -= c2;
            }
            return (result % mod + mod) % mod == 0;
        };

        return check(2) && check(5);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<string> tests = {
        "",                 // empty string
        "7",                // single digit
        "00",               // same digits
        "01",               // increasing adjacent
        "10",               // decreasing adjacent
        "0123456789",       // ascending sequence
        "9876543210",       // descending sequence
        "1212121212",       // repeating pattern
        "9999999999",       // all same digit
        "31415926"          // mixed digits
    };

    Solution sol;
    long long total = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            total += sol.hasSameDigits(s);
        }
    }

    auto end_time = high_resolution_clock::now();
    auto ms = duration_cast<duration<double, std::milli>>(end_time - start).count();

    cout << "Aggregate result: " << total << "\n";
    cout << "Execution time (ms): " << ms << "\n";

    return 0;
}