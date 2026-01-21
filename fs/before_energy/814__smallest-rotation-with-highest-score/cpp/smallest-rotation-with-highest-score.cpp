#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

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