#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

// Time:  O(n)
// Space: O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        long long hold1 = numeric_limits<long long>::lowest() / 4;
        long long hold2 = numeric_limits<long long>::lowest() / 4;
        long long release1 = 0;
        long long release2 = 0;
        for (int price : prices) {
            hold1 = max(hold1, -static_cast<long long>(price));
            release1 = max(release1, hold1 + price);
            hold2 = max(hold2, release1 - price);
            release2 = max(release2, hold2 + price);
        }
        return static_cast<int>(release2);
    }
};

int main() {
    Solution s;
    vector<vector<int>> tests = {
        {5},
        {9,7,4,3,1},
        {1,2,3,4,5},
        {3,3,5,0,0,3,1,4},
        {1,2,4,2,5,7,2,4,9,0},
        {5,2,4,0,1,3,2,5},
        {1000000,1,1000000,1,1000000},
        {2,2,2,2,2},
        {1,3,2,8,4,9},
        {7,6,4,3,1,2,10,1,2,3,0,8}
    };

    const int iterations = 1;
    volatile int sink = 0;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += s.maxProfit(tests[i]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}