#include <bits/stdc++.h>
using namespace std;

// Time:  O(logn * log(logn))
// Space: O(1)

class Solution {
public:
    string smallestGoodBase(string n) {
        unsigned long long num = stoull(n);
        int max_len = static_cast<int>(floor(logl((long double)num) / logl(2.0L)));
        for (int l = max_len; l >= 2; --l) {
            long double root = powl((long double)num, 1.0L / l);
            unsigned long long b = static_cast<unsigned long long>(floor(root));
            if (b >= 2 && isGood(num, b, l)) {
                return to_string(b);
            }
            // Guard against floating error by checking b+1 as well
            if (b + 1 >= 2 && isGood(num, b + 1, l)) {
                return to_string(b + 1);
            }
        }
        return to_string(num - 1);
    }

private:
    // Check if 1 + b + b^2 + ... + b^l == num without overflow
    static bool isGood(unsigned long long num, unsigned long long b, int l) {
        __int128 target = static_cast<__int128>(num);
        __int128 sum = 1;
        __int128 curr = 1;
        for (int i = 1; i <= l; ++i) {
            if (curr > target / b) return false; // next multiplication would exceed num
            curr *= b;
            sum += curr;
            if (sum > target) return false;
        }
        return sum == target;
    }
};

int main() {
    // Define 10 diverse test inputs as strings (as required by the solution)
    vector<string> tests = {
        "3",                        // small, 2^2 - 1
        "13",                       // 1 + 3 + 9
        "31",                       // 2^5 - 1
        "4681",                     // 1 + 8 + 8^2 + 8^3 + 8^4
        "121",                      // 1 + 10 + 100
        "21",                       // 1 + 4 + 16
        "1000000000000000000",      // large 1e18
        "999999999999999999",       // large, 18-digit 9s
        "2251799813685247",         // 2^51 - 1
        "1099511627775"             // 2^40 - 1
    };

    Solution sol;
    uint64_t checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            string res = sol.smallestGoodBase(tests[i]);
            // Accumulate into checksum to prevent optimization
            uint64_t b = stoull(res);
            checksum += b;
            checksum ^= (static_cast<uint64_t>(res.size()) + static_cast<uint64_t>(i) + static_cast<uint64_t>(iter));
            checksum = (checksum << 7) | (checksum >> (64 - 7)); // simple bit mix
        }
    }

    auto end = Clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << '\n';
    cout << "Elapsed time (ns): " << elapsed_ns << '\n';
    return 0;
}