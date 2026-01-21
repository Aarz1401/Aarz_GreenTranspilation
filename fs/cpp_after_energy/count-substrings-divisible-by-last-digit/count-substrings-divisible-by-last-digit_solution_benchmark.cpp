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
#include <array>
#include <deque>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    long long countSubstrings(string s) {
        int n = static_cast<int>(s.size());
        long long result = 0;

        // digit 1, 2, 5
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1' || s[i] == '2' || s[i] == '5') {
                result += static_cast<long long>(i) + 1;
            }
        }

        // digit 3, 6
        {
            int remain = 0;
            vector<long long> cnt(3, 0);
            cnt[0] = 1;
            for (int i = 0; i < n; ++i) {
                remain = (remain + (s[i] - '0')) % 3;
                if (s[i] == '3' || s[i] == '6') {
                    result += cnt[remain];
                }
                cnt[remain] += 1;
            }
        }

        // digit 9
        {
            int remain = 0;
            vector<long long> cnt(9, 0);
            cnt[0] = 1;
            for (int i = 0; i < n; ++i) {
                remain = (remain + (s[i] - '0')) % 9;
                if (s[i] == '9') {
                    result += cnt[remain];
                }
                cnt[remain] += 1;
            }
        }

        // digit 4
        for (int i = 0; i < n; ++i) {
            if (s[i] == '4') {
                result += 1;
                if (i - 1 >= 0) {
                    int val2 = (s[i - 1] - '0') * 10 + (s[i] - '0');
                    if (val2 % 4 == 0) {
                        result += i;
                    }
                }
            }
        }

        // digit 8
        for (int i = 0; i < n; ++i) {
            if (s[i] == '8') {
                result += 1;
                if (i - 1 >= 0) {
                    int val2 = (s[i - 1] - '0') * 10 + (s[i] - '0');
                    if (val2 % 8 == 0) {
                        result += 1;
                    }
                }
                if (i - 2 >= 0) {
                    int val3 = (s[i - 2] - '0') * 100 + (s[i - 1] - '0') * 10 + (s[i] - '0');
                    if (val3 % 8 == 0) {
                        result += i - 1;
                    }
                }
            }
        }

        // digit 7
        {
            int base = 1;
            int remain = 0;
            vector<long long> cnt(7, 0);
            for (int i = 0; i < n; ++i) {
                int pos = n - 1 - i;
                int d = s[pos] - '0';
                remain = (remain + (base * d) % 7) % 7;
                result += cnt[remain];
                if (s[pos] == '7') {
                    result += 1;
                    cnt[remain] += 1;
                }
                base = (base * 10) % 7;
            }
        }

        return result;
    }
};

static string repeatPattern(const string& pat, int times) {
    string s;
    s.reserve(pat.size() * times);
    for (int i = 0; i < times; ++i) s += pat;
    return s;
}

static string genLCGDigits(size_t n, unsigned int seed) {
    string s;
    s.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        seed = seed * 1664525u + 1013904223u;
        s.push_back(char('0' + (seed % 10)));
    }
    return s;
}

int main() {
    // Prepare 10 diverse test inputs (strings of digits)
    vector<string> tests;
    tests.reserve(10);
    tests.push_back("");                                   // 1) empty
    tests.push_back("0");                                  // 2) single zero
    tests.push_back("9");                                  // 3) single nine
    tests.push_back("27");                                 // 4) small mixed digits
    tests.push_back("1234567890");                         // 5) all digits once
    tests.push_back(string(100, '7'));                     // 6) many 7s
    tests.push_back(repeatPattern("31415926", 32));        // 7) length 256
    tests.push_back(repeatPattern("0123456789", 100));     // 8) length 1000
    tests.push_back(genLCGDigits(2000, 123456789u));       // 9) length 2000 pseudo-random digits
    tests.push_back(string(4096, '8'));                    // 10) many 8s

    Solution sol;

    volatile long long checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            long long ans = sol.countSubstrings(s);
            checksum += ans;
        }
    }

    auto end = Clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}