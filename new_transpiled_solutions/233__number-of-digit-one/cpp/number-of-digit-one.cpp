#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cstdint>

class Solution {
public:
    int countDigitOne(int n) {
        const long long DIGIT = 1;
        int is_zero = (DIGIT == 0) ? 1 : 0;
        long long result = is_zero;
        long long base = 1;
        while (static_cast<long long>(n) >= base) {
            long long tenbase = base * 10;
            result += (static_cast<long long>(n) / tenbase - is_zero) * base +
                      std::min(base, std::max(static_cast<long long>(n) % tenbase - DIGIT * base + 1, 0LL));
            base *= 10;
        }
        return static_cast<int>(result);
    }
};