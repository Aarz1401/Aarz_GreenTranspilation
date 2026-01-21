#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>

class Solution {
public:
    int minPatches(std::vector<int>& nums, int n) {
        long long miss = 1;
        int i = 0;
        int patches = 0;
        while (miss <= static_cast<long long>(n)) {
            if (i < static_cast<int>(nums.size()) && nums[i] <= miss) {
                miss += nums[i];
                ++i;
            } else {
                miss += miss;
                ++patches;
            }
        }
        return patches;
    }
};

struct Test {
    std::vector<int> nums;
    int n;
};

int main() {
    std::vector<Test> tests = {
        {{1, 3}, 6},
        {{1, 5, 10}, 20},
        {{1, 2, 2}, 5},
        {{2}, 1},
        {{2, 3, 4, 7}, 15},
        {{1, 1, 1, 1}, 8},
        {{5, 10, 25}, 50},
        {{1, 4, 7, 13, 28}, 100},
        {{1, 2, 31, 33}, 2147483647},
        {{1, 2, 4, 8, 16, 32}, 63}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int r = 0;
        r = sol.minPatches(tests[0].nums, tests[0].n);
        r = sol.minPatches(tests[1].nums, tests[1].n);
        r = sol.minPatches(tests[2].nums, tests[2].n);
        r = sol.minPatches(tests[3].nums, tests[3].n);
        r = sol.minPatches(tests[4].nums, tests[4].n);
        r = sol.minPatches(tests[5].nums, tests[5].n);
        r = sol.minPatches(tests[6].nums, tests[6].n);
        r = sol.minPatches(tests[7].nums, tests[7].n);
        r = sol.minPatches(tests[8].nums, tests[8].n);
        r = sol.minPatches(tests[9].nums, tests[9].n);
        DoNotOptimize(r); 
        //sink = checksum;
    }

    return 0;
}