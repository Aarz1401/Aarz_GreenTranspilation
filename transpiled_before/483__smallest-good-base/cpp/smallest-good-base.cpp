#include <string>
#include <cmath>
#include <cstdint>
#include <limits>

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