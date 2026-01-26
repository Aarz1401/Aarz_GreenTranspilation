#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>

class Solution {
public:
    bool isSelfCrossing(std::vector<int>& x) {
        int n = static_cast<int>(x.size());
        if (n >= 5 && x[3] == x[1] && static_cast<long long>(x[4]) + x[0] >= x[2]) {
            
            return true;
        }

        for (int i = 3; i < n; ++i) {
            if (x[i] >= x[i - 2] && x[i - 3] >= x[i - 1]) {
                
                return true;
            } else if (i >= 5 &&
                       x[i - 4] <= x[i - 2] && static_cast<long long>(x[i]) + x[i - 4] >= x[i - 2] &&
                       x[i - 1] <= x[i - 3] && static_cast<long long>(x[i - 5]) + x[i - 1] >= x[i - 3]) {
                
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<int>> tests = {
        {2, 1, 1, 2},                                  // crossing
        {1, 2, 3, 4},                                  // non-crossing
        {1, 1, 1, 1},                                  // crossing
        {1, 1, 2, 1, 1},                               // crossing (special early check)
        {1, 2, 3, 4, 2, 2},                            // crossing (case 2)
        {2, 2, 3, 3, 2, 2},                            // crossing (case 2)
        {100000000, 200000000, 300000000, 400000000, 500000000, 600000000}, // non-crossing
        {3, 4, 5, 6, 7, 8},                            // non-crossing
        {1, 2, 3, 2},                                  // non-crossing
        {2, 1, 3, 2, 4, 3}                             // non-crossing
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = sol.isSelfCrossing(t);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}