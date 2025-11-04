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