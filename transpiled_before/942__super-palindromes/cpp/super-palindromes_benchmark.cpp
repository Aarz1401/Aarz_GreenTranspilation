#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <chrono>

using namespace std;

class Solution {
public:
    int superpalindromesInRange(string L, string R) {
        auto is_palindrome = [](unsigned long long k) -> bool {
            string s = to_string(k);
            string t = s;
            reverse(t.begin(), t.end());
            return s == t;
        };

        int lenR = static_cast<int>(R.size());
        unsigned long long l = stoull(L);
        unsigned long long r = stoull(R);

        long long K = static_cast<long long>(pow(10.0, ((lenR + 1) * 0.25))) + 1;

        int result = 0;
        __int128 ll = static_cast<__int128>(l);
        __int128 rr = static_cast<__int128>(r);

        // count odd length
        for (long long k = 0; k < K; ++k) {
            string s = to_string(k);
            string revprefix = s.substr(0, s.size() - 1);
            reverse(revprefix.begin(), revprefix.end());
            string t = s + revprefix;
            unsigned long long p = stoull(t);
            __int128 vv = static_cast<__int128>(p) * static_cast<__int128>(p);
            if (vv > rr) break;
            if (vv >= ll && is_palindrome(static_cast<unsigned long long>(vv))) {
                ++result;
            }
        }

        // count even length
        for (long long k = 0; k < K; ++k) {
            string s = to_string(k);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string t = s + rev;
            unsigned long long p = stoull(t);
            __int128 vv = static_cast<__int128>(p) * static_cast<__int128>(p);
            if (vv > rr) break;
            if (vv >= ll && is_palindrome(static_cast<unsigned long long>(vv))) {
                ++result;
            }
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<string, string>> tests = {
        {"0", "0"},
        {"1", "1"},
        {"1", "2"},
        {"4", "4"},
        {"1", "1000"},
        {"100", "1000"},
        {"5", "6"},
        {"400000000000000", "900000000000000"},
        {"1", "99999999999999"},
        {"4000000000000000", "5000000000000000"}
    };

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& pr : tests) {
            checksum += sol.superpalindromesInRange(pr.first, pr.second);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}