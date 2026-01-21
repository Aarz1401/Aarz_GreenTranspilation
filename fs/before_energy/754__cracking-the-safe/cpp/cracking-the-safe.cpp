#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>

using namespace std;

// Time:  O(k^n)
// Space: O(k^n)
class Solution {
public:
    string crackSafe(int n, int k) {
        int M = 1;
        for (int i = 0; i < n - 1; ++i) {
            M *= k;
        }
        int total = 1;
        for (int i = 0; i < n; ++i) {
            total *= k;
        }

        // rotate: i*k^(n-1) + q => q*k + i
        vector<int> P;
        P.reserve(total);
        for (int i = 0; i < k; ++i) {
            for (int q = 0; q < M; ++q) {
                P.emplace_back(q * k + i);
            }
        }

        string result;
        result.reserve(total + n - 1);
        for (int i = 0; i < n - 1; ++i) {
            result.push_back(char('0' + (k - 1)));
        }
        for (int i = 0; i < total; ++i) {
            int j = i;
            // concatenation in lexicographic order of Lyndon words
            while (P[j] >= 0) {
                result.push_back(char('0' + (j / M)));
                int pj = P[j];
                P[j] = -1;
                j = pj;
            }
        }
        return result;
    }
};