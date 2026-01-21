#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <unordered_set>
#include <numeric>

using namespace std;

// Time:  O(n^4)
// Space: O(n^3)

class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        auto possible = [](int total, int n) -> bool {
            for (int i = 1; i <= n / 2; ++i) {
                if ((total * i) % n == 0) {
                    return true;
                }
            }
            return false;
        };

        int n = static_cast<int>(A.size());
        int s = accumulate(A.begin(), A.end(), 0);
        if (!possible(s, n)) {
            return false;
        }

        int half = n / 2;
        vector<unordered_set<int>> sums(half + 1);
        sums[0].insert(0);
        for (int num : A) {  // O(n) times
            for (int i = half; i >= 1; --i) {  // O(n) times
                if (!sums[i - 1].empty()) {
                    for (const int& prev : sums[i - 1]) {  // O(1) + O(2) + ... O(n/2) = O(n^2) times
                        sums[i].insert(prev + num);
                    }
                }
            }
        }

        for (int i = 1; i <= half; ++i) {
            if ((s * i) % n == 0) {
                int target = (s * i) / n;
                if (sums[i].count(target)) {
                    return true;
                }
            }
        }
        return false;
    }
};

volatile int sink = 0;

int main() {
    vector<vector<int>> tests = {
        {1, 2},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {5, 5, 5, 5},
        {0, 0, 0, 0, 0, 0, 0},
        {2, 0, 5, 6, 16, 12, 15, 9},
        {3, 3, 3, 4, 5},
        {1, 2, 3, 4, 6, 8, 10},
        {9, 1, 2, 3, 4, 5, 6, 7, 8},
        {1, 1, 1, 1, 1, 1},
        {10, 20, 30, 40, 50, 60}
    };

    Solution s;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& A : tests) {
            int r = s.splitArraySameAverage(A);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}