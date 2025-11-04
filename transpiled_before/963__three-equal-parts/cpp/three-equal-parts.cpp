#include <vector>
using namespace std;

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& A) {
        int n = static_cast<int>(A.size());
        int total = 0;
        for (int x : A) total += x;
        if (total % 3 != 0) return {-1, -1};
        if (total == 0) return {0, n - 1};

        int count = total / 3;
        vector<int> nums(3, 0);
        int c = 0;
        for (int i = 0; i < n; ++i) {
            if (A[i] == 1) {
                if (c % count == 0) {
                    nums[c / count] = i;
                }
                ++c;
            }
        }

        while (nums[2] < n) {
            if (!(A[nums[0]] == A[nums[1]] && A[nums[1]] == A[nums[2]])) {
                return {-1, -1};
            }
            ++nums[0];
            ++nums[1];
            ++nums[2];
        }
        return {nums[0] - 1, nums[1]};
    }
};