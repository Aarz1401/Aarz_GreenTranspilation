#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
using namespace std;

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& A) {
        int n = static_cast<int>(A.size());
        int total = 0;
        for (int x : A) total += x;
        if (total % 3 != 0) return {-1, -1};
        if (total == 0) return {0, n - 1};

        int count = total / 3;
        vector<int> nums(3, 0);
        int c = 0;
        for (int i = 0; i < n; ++i) {
            if (A[i] == 1) {
                if (c % count == 0) {
                    nums[c / count] = i;
                }
                ++c;
            }
        }

        while (nums[2] < n) {
            if (!(A[nums[0]] == A[nums[1]] && A[nums[1]] == A[nums[2]])) {
                return {-1, -1};
            }
            ++nums[0];
            ++nums[1];
            ++nums[2];
        }
        return {nums[0] - 1, nums[1]};
    }
};

int main() {
    vector<vector<int>> tests = {
        {0,0,0,0,0,0},
        {1,0,1,0,1},
        {1,1,0,1,1},
        {1,0,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,0},
        {0,1,0,1,0,1,0},
        {1,1,1,0,0,0},
        {1,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,1,1,0,1,0,0},
        {1,0,1,1,0,1,0,1,0,1,0,0}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            auto res = sol.threeEqualParts(tests[i]);
            DoNotOptimize(res);
            // checksum += res[0];
            // checksum += res[1];
        }
        //sink = checksum;
    }

    return 0;
}