#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if (nums.empty()) return 0;
        return static_cast<int>(countAndMergeSort(nums, 0, static_cast<int>(nums.size()) - 1));
    }
    
private:
    long long countAndMergeSort(vector<int>& nums, int start, int end) {
        if (end - start <= 0) return 0;
        int mid = start + (end - start) / 2;
        long long count = countAndMergeSort(nums, start, mid) + countAndMergeSort(nums, mid + 1, end);
        
        int r = mid + 1;
        for (int i = start; i <= mid; ++i) {
            while (r <= end && static_cast<long long>(nums[i]) > 2LL * nums[r]) {
                ++r;
            }
            count += r - (mid + 1);
        }
        
        merge(nums, start, mid, end);
        return count;
    }
    
    void merge(vector<int>& nums, int start, int mid, int end) {
        int r = mid + 1;
        vector<int> tmp;
        tmp.reserve(end - start + 1);
        
        for (int i = start; i <= mid; ++i) {
            while (r <= end && nums[i] > nums[r]) {
                tmp.push_back(nums[r]);
                ++r;
            }
            tmp.push_back(nums[i]);
        }
        
        for (size_t k = 0; k < tmp.size(); ++k) {
            nums[start + static_cast<int>(k)] = tmp[k];
        }
        // Remaining right elements stay in place.
    }
};