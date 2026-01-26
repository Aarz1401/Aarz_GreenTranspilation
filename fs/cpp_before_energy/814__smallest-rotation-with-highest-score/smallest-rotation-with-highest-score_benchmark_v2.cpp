#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
using namespace std;

class Solution {
public:
    int bestRotation(vector<int>& A) {
        int N = static_cast<int>(A.size());
        if (N == 0) return 0;
        vector<int> change(N, 1);
        for (int i = 0; i < N; ++i) {
            int idx = (i - A[i] + 1) % N;
            if (idx < 0) idx += N;
            change[idx] -= 1;
        }
        for (int i = 1; i < N; ++i) {
            change[i] += change[i - 1];
        }
        int best = 0;
        int bestVal = change[0];
        for (int i = 1; i < N; ++i) {
            if (change[i] > bestVal) {
                bestVal = change[i];
                best = i;
            }
        }
        return best;
    }
};

int main() {
    vector<vector<int>> tests = {
        {0},
        {1, 0},
        {2, 2, 1},
        {0, 0, 0, 0},
        {4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5},
        {6, 5, 4, 3, 2, 1, 0},
        {1, 3, 5, 7, 0, 2, 4, 6},
        {2, 0, 6, 3, 1, 4, 9, 7, 5, 8},
        {14, 0, 14, 7, 3, 5, 10, 2, 12, 6, 8, 1, 9, 4, 11}
    };

    Solution s;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = s.bestRotation(t);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}