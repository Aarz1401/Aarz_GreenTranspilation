#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// Time:  O(nlogn)
// Space: O(n)
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> counts(nums.size(), 0);
        if (nums.empty()) return counts;

        vector<pair<int, int>> num_idxs;
        num_idxs.reserve(nums.size());
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            num_idxs.emplace_back(nums[i], i);
        }

        countAndMergeSort(num_idxs, 0, static_cast<int>(num_idxs.size()) - 1, counts);
        return counts;
    }

private:
    void countAndMergeSort(vector<pair<int, int>>& num_idxs, int start, int end, vector<int>& counts) {
        if (end - start <= 0) {
            return;  // The size of range [start, end] less than 2 is always with count 0.
        }

        int mid = start + (end - start) / 2;
        countAndMergeSort(num_idxs, start, mid, counts);
        countAndMergeSort(num_idxs, mid + 1, end, counts);

        int r = mid + 1;
        vector<pair<int, int>> tmp;
        tmp.reserve((mid - start + 1) + (end - mid));

        for (int i = start; i <= mid; ++i) {
            // Merge the two sorted arrays into tmp.
            while (r <= end && num_idxs[r].first < num_idxs[i].first) {
                tmp.emplace_back(num_idxs[r]);
                ++r;
            }
            tmp.emplace_back(num_idxs[i]);
            counts[num_idxs[i].second] += r - (mid + 1);
        }

        // Copy tmp back to num_idxs
        for (int i = 0; i < static_cast<int>(tmp.size()); ++i) {
            num_idxs[start + i] = tmp[i];
        }
    }
};