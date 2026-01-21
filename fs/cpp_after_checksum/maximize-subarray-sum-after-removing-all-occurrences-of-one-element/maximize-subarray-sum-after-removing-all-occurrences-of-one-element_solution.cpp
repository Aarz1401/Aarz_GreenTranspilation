#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>

using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        long long result = LLONG_MIN;
        long long curr = 0;
        long long mn = 0;
        long long mn0 = 0;
        unordered_map<long long, long long> mn1;  // default 0

        for (int x : nums) {
            long long xl = static_cast<long long>(x);
            curr += xl;
            result = max(result, curr - mn);
            long long& ref = mn1[xl];
            ref = min(ref, mn0) + xl;
            mn0 = min(mn0, curr);
            mn = min(mn, ref);
            mn = min(mn, mn0);
        }
        return result;
    }
};
