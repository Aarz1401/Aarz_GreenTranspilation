
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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
    // Prepare 10 diverse test inputs
    vector<string> tests;
    tests.reserve(10);

    // 1) Empty string
    tests.push_back("");

    // 2) Single digit
    tests.push_back("7");

    // 3) Two identical digits
    tests.push_back("00");

    // 4) Ascending digits
    tests.push_back("0123456789");

    // 5) Descending digits
    tests.push_back("9876543210");

    // 6) Repeated same digit (longer)
    tests.push_back(string(256, '7'));

    // 7) Alternating digits
    {
        string s;
        s.reserve(512);
        for (int i = 0; i < 512; ++i) s.push_back((i % 2) ? '2' : '1');
        tests.push_back(s);
    }

    // 8) Digits of pi (prefix)
    tests.push_back("314159265358979323846264338327950288419716939937510");

    // 9) Pseudorandom-like pattern based on linear congruential sequence (length 1000)
    {
        string s;
        s.reserve(1000);
        int x = 12345;
        for (int i = 0; i < 1000; ++i) {
            x = (1103515245 * x + 12345) & 0x7fffffff;
            s.push_back(char('0' + (x % 10)));
        }
        tests.push_back(s);
    }

    // 10) Repeated pattern of "31415926" (length ~800)
    {
        string s;
        s.reserve(800);
        const string pat = "31415926";
        while (s.size() < 800) s += pat;
        s.resize(800);
        tests.push_back(s);
    }

    Solution sol;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;

    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int i = 0; i < 10; ++i) {
            bool r = sol.hasSameDigits(tests[i]);
            // Accumulate in a way that depends on both result and input index/size
            checksum += r ? (i + 1) : 0;
            checksum ^= static_cast<long long>(tests[i].size() + (r ? 123 : 321));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}