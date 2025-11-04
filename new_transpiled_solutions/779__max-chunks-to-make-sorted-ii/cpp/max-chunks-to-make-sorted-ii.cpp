#include <vector>
#include <algorithm>
using namespace std;

// Time:  O(n)
// Space: O(n)

// mono stack solution
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<int> increasing_stk;
        for (const int& num : arr) {
            int max_num = increasing_stk.empty() ? num : max(increasing_stk.back(), num);
            while (!increasing_stk.empty() && increasing_stk.back() > num) {
                increasing_stk.pop_back();
            }
            increasing_stk.push_back(max_num);
        }
        return static_cast<int>(increasing_stk.size());
    }
};