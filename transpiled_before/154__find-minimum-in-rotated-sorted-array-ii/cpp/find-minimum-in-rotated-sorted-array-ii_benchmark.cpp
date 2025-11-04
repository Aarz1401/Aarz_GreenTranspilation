#include <iostream>
#include <vector>
#include <chrono>

class Solution {
public:
    int findMin(std::vector<int>& nums) {
        int left = 0, right = static_cast<int>(nums.size()) - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == nums[right]) {
                --right;
            } else if (nums[mid] < nums[right]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return nums[left];
    }
};

class Solution2 {
public:
    int findMin(std::vector<int>& nums) {
        int left = 0, right = static_cast<int>(nums.size()) - 1;
        while (left < right && nums[left] >= nums[right]) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == nums[left]) {
                ++left;
            } else if (nums[mid] < nums[left]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return nums[left];
    }
};

int main() {
    // Prepare 10 diverse test inputs
    std::vector<std::vector<int>> tests;

    // 1. Single element
    tests.push_back({1});

    // 2. Two elements, sorted
    tests.push_back({1, 2});

    // 3. Two elements, rotated
    tests.push_back({2, 1});

    // 4. Multiple elements, rotated, no duplicates
    tests.push_back({3, 4, 5, 1, 2});

    // 5. Duplicates around pivot
    tests.push_back({2, 2, 2, 0, 1, 2});

    // 6. All identical
    tests.push_back({10, 10, 10, 10, 10});

    // 7. Many duplicates with a unique minimum
    tests.push_back({1, 1, 1, 0, 1});

    // 8. Larger array rotated at pivot 73: [73..99, 0..72]
    {
        std::vector<int> v8;
        v8.reserve(100);
        for (int i = 73; i < 100; ++i) v8.push_back(i);
        for (int i = 0; i < 73; ++i) v8.push_back(i);
        tests.push_back(std::move(v8));
    }

    // 9. Includes negatives, rotated with duplicates
    tests.push_back({-1, 0, 1, -3, -2, -1});

    // 10. Already sorted with duplicates
    tests.push_back({0, 0, 1, 1, 2, 2, 3, 3, 4, 4});

    Solution solver;

    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            checksum += solver.findMin(t);
        }
    }

    auto end = clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}