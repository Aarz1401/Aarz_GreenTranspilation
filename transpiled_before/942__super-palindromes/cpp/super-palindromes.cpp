#include <string>
#include <algorithm>
#include <cmath>
#include <cstdint>

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