#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>

class Solution {
public:
    int findIntegers(int num) {
        std::vector<int> dp(32, 0);
        dp[0] = 1;
        dp[1] = 2;
        for (int i = 2; i < 32; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        int result = 0;
        int prev_bit = 0;
        for (int i = 30; i >= 0; --i) {
            if (num & (1 << i)) {
                result += dp[i];
                if (prev_bit == 1) {
                    result -= 1;
                    break;
                }
                prev_bit = 1;
            } else {
                prev_bit = 0;
            }
        }
        return result + 1;
    }
};