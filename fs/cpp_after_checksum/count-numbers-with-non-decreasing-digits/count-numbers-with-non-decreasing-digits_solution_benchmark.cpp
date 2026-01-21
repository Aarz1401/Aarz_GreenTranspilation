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
#include <functional>
#include <utility>
#include <chrono>
#include <tuple>

using namespace std;

class Solution {
public:
    int countNumbers(string l, string r, int b) {
        using ll = long long;
        const ll MOD = 1000000007LL;

        vector<ll> fact(2, 1), inv(2, 1), invFact(2, 1);

        auto nCr = [&](int n, int k) -> ll {
            if (k < 0 || k > n) return 0;
            while ((int)inv.size() <= n) {
                int i = (int)inv.size();
                fact.push_back(fact.back() * i % MOD);
                ll inv_i = inv[MOD % i] * (MOD - MOD / i) % MOD;
                inv.push_back(inv_i);
                invFact.push_back(invFact.back() * inv_i % MOD);
            }
            return ((fact[n] * invFact[n - k]) % MOD) * invFact[k] % MOD;
        };

        auto nHr = [&](int n, int k) -> ll {
            // combinations with repetitions: C(n + k - 1, k)
            return nCr(n + k - 1, k);
        };

        auto strToDigits = [&](const string& s) -> vector<int> {
            vector<int> d;
            d.reserve(s.size());
            for (char c : s) d.push_back(c - '0');
            return d;
        };

        auto isZeroString = [&](const string& s) -> bool {
            for (char c : s) if (c != '0') return false;
            return true;
        };

        auto decrease = [&](vector<int>& digits) {
            for (int i = (int)digits.size() - 1; i >= 0; --i) {
                if (digits[i] > 0) {
                    digits[i] -= 1;
                    break;
                }
                digits[i] = 9;
            }
        };

        auto divideDigits = [&](const vector<int>& digits, int base) -> pair<vector<int>, int> {
            vector<int> result;
            long long rem = 0;
            for (int d : digits) {
                long long cur = rem * 10 + d;
                int q = (int)(cur / base);
                rem = (int)(cur % base);
                if (!result.empty() || q != 0) result.push_back(q);
            }
            return {result, (int)rem};
        };

        function<vector<int>(vector<int>, int)> to_base = [&](vector<int> digits, int base) -> vector<int> {
            vector<int> result;
            while (!digits.empty()) {
                auto pr = divideDigits(digits, base);
                digits = move(pr.first);
                result.push_back(pr.second);
            }
            reverse(result.begin(), result.end());
            if (result.empty()) result.push_back(0);
            return result;
        };

        function<ll(const vector<int>&)> countDecDigits = [&](const vector<int>& decDigits) -> ll {
            vector<int> digits_base = to_base(decDigits, b);
            ll res = 0;
            int n = (int)digits_base.size();
            bool ok = true;
            for (int i = 0; i < n; ++i) {
                if (i - 1 >= 0 && digits_base[i - 1] > digits_base[i]) {
                    ok = false;
                    break;
                }
                int start = (i - 1 >= 0) ? digits_base[i - 1] : 0;
                for (int j = start; j < digits_base[i]; ++j) {
                    res += nHr(b - j, n - (i + 1));
                    if (res >= MOD) res -= MOD;
                }
            }
            if (ok) {
                res += 1;
                if (res >= MOD) res -= MOD;
            }
            return res;
        };

        ll lowCount = 0;
        if (!isZeroString(l)) {
            vector<int> digitsL = strToDigits(l);
            decrease(digitsL);
            lowCount = countDecDigits(digitsL);
        }
        vector<int> digitsR = strToDigits(r);
        ll highCount = countDecDigits(digitsR);

        ll ans = (highCount - lowCount) % MOD;
        if (ans < 0) ans += MOD;
        return (int)ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs: pairs of decimal strings (l, r) and base b
    const vector<tuple<string, string, int>> tests = {
        {"0", "0", 2},                                                    // exact zero in base 2
        {"0000", "0000", 3},                                              // leading zeros, zero range
        {"0", "9", 10},                                                   // small range in base 10
        {"10", "99", 10},                                                 // two-digit range in base 10
        {"1", "100000", 2},                                               // larger range in base 2
        {"12345678901234567890", "12345678901234567999", 10},             // big numbers in base 10
        {"999999999999999999", "1000000000000000000", 16},                // boundary around 1e18 in base 16
        {"123456789", "987654321", 7},                                    // mid-size range in base 7
        {"42", "42", 36},                                                 // single value in base 36
        {"10000000000000000000000000000000000000000000000000",
         "10000000000000000000000000000000000000000000012345", 11}        // very large numbers in base 11
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            const string& l = get<0>(t);
            const string& r = get<1>(t);
            int b = get<2>(t);
            int res = sol.countNumbers(l, r, b);
            // Mix into checksum to prevent optimization
            checksum ^= (static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2));
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}