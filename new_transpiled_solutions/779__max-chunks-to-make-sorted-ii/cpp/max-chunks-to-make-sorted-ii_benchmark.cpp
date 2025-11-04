#include <chrono>
#include <iostream>
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

int main() {
    // Define 10 diverse test inputs (vector<int> as required by the solution)
    vector<vector<int>> tests;
    tests.push_back({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});                 // Already sorted
    tests.push_back({9, 8, 7, 6, 5, 4, 3, 2, 1, 0});                 // Reverse sorted
    tests.push_back({2, 1, 3, 4, 4, 0, 0, 2});                       // Duplicates mixed
    tests.push_back({7, 7, 7, 7, 7});                                // All equal
    tests.push_back({2, 0, 1, 4, 3, 6, 5, 8, 7});                    // Alternating high-low
    tests.push_back({1000000, 2000000, 3000000, 4000000});           // Large increasing
    tests.push_back({-1, -3, -2, 0, -4, 5});                         // Includes negatives
    tests.push_back({1, 2, 2, 3, 3, 0, 4, 4});                       // Plateau then drop
    tests.push_back({42});                                           // Single element
    tests.push_back({});                                             // Empty array

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            // The function signature takes a non-const ref, but it doesn't modify the input
            int result = sol.maxChunksToSorted(tests[i]);
            checksum += (result * static_cast<int>(i + 1)); // weighted to avoid trivial cancellation
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}