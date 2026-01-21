#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    // Time:  O(n)
    // Space: O(n)
    int candy(std::vector<int>& ratings) {
        int n = static_cast<int>(ratings.size());
        if (n == 0) return 0;
        
        std::vector<int> candies(n, 1);
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {
                candies[i] = candies[i + 1] + 1;
            }
        }
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};