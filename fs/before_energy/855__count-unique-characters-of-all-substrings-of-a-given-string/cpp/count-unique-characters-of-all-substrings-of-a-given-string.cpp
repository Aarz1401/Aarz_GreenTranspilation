#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <array>
#include <string>
#include <cstdint>
using namespace std;

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    int uniqueLetterString(string S) {
        const int64_t M = 1000000007LL;
        vector<array<int, 2>> index(26);
        for (int i = 0; i < 26; ++i) {
            index[i] = {-1, -1};
        }
        int64_t result = 0;
        for (int i = 0; i < static_cast<int>(S.size()); ++i) {
            int c = S[i] - 'A';
            int k = index[c][0];
            int j = index[c][1];
            result = (result + (int64_t)(i - j) * (j - k)) % M;
            index[c] = {j, i};
        }
        for (int i = 0; i < 26; ++i) {
            int k = index[i][0];
            int j = index[i][1];
            result = (result + (int64_t)(static_cast<int>(S.size()) - j) * (j - k)) % M;
        }
        return static_cast<int>(result % M);
    }
};