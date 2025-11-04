#include <iostream>
#include <vector>
#include <unordered_set>
#include <numeric>
#include <algorithm>

using namespace std;

// Time:  O(n^4)
// Space: O(n^3)

class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        auto possible = [](int total, int n) -> bool {
            for (int i = 1; i <= n / 2; ++i) {
                if ((total * i) % n == 0) {
                    return true;
                }
            }
            return false;
        };

        int n = static_cast<int>(A.size());
        int s = accumulate(A.begin(), A.end(), 0);
        if (!possible(s, n)) {
            return false;
        }

        int half = n / 2;
        vector<unordered_set<int>> sums(half + 1);
        sums[0].insert(0);
        for (int num : A) {  // O(n) times
            for (int i = half; i >= 1; --i) {  // O(n) times
                if (!sums[i - 1].empty()) {
                    for (const int& prev : sums[i - 1]) {  // O(1) + O(2) + ... O(n/2) = O(n^2) times
                        sums[i].insert(prev + num);
                    }
                }
            }
        }

        for (int i = 1; i <= half; ++i) {
            if ((s * i) % n == 0) {
                int target = (s * i) / n;
                if (sums[i].count(target)) {
                    return true;
                }
            }
        }
        return false;
    }
};