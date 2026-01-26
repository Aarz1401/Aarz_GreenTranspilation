#include <iostream>
#include <vector>
#include <numeric>

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

int main() {
    Solution sol;
    std::vector<std::vector<int>> tests = {
        {1},
        {1,2,3,4,5},
        {5,4,3,2,1},
        {1,0,2},
        {1,2,2},
        {2,2,2,2,2},
        {1,3,4,5,2},
        {1,3,2,2,1},
        {1,6,10,8,7,3,2},
        {1,2,87,87,87,2,1}
    };

    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.candy(tests[i]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}