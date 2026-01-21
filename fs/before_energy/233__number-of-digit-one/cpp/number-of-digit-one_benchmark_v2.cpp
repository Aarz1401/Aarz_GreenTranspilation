#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>

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

int main() {
    std::vector<int> tests = {
        0, 1, 9, 10, 11, 19, 99, 101, 1000, 1000000000
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (int n : tests) {
            int r = sol.countDigitOne(n);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}