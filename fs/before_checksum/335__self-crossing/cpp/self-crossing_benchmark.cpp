#include <iostream>
#include <chrono>
#include <vector>

#include <vector>

class Solution {
public:
    bool isSelfCrossing(std::vector<int>& x) {
        int n = static_cast<int>(x.size());
        if (n >= 5 && x[3] == x[1] && static_cast<long long>(x[4]) + x[0] >= x[2]) {
            // Crossing in a loop:
            //     2
            // 3 ┌────┐
            //   └─══>┘1
            //   4  0  (overlapped)
            return true;
        }

        for (int i = 3; i < n; ++i) {
            if (x[i] >= x[i - 2] && x[i - 3] >= x[i - 1]) {
                // Case 1:
                //    i-2
                // i-1┌─┐
                //    └─┼─>i
                //     i-3
                return true;
            } else if (i >= 5 &&
                       x[i - 4] <= x[i - 2] && static_cast<long long>(x[i]) + x[i - 4] >= x[i - 2] &&
                       x[i - 1] <= x[i - 3] && static_cast<long long>(x[i - 5]) + x[i - 1] >= x[i - 3]) {
                // Case 2:
                //    i-4
                //    ┌──┐
                //    │i<┼─┐
                // i-3│ i-5│i-1
                //    └────┘
                //      i-2
                return true;
            }
        }
        return false;
    }
};

int main() {
    // Define 10 diverse test cases
    std::vector<std::vector<int>> tests = {
        {2, 1, 1, 2},                                  // crossing (case 1)
        {1, 2, 3, 4, 5, 6},                            // non-crossing
        {1, 1, 2, 1, 1},                               // crossing (overlapped pre-check)
        {1, 1, 2, 2, 1, 1},                            // crossing (case 2)
        {1, 1, 1, 1},                                  // crossing
        {1, 1, 2, 3, 4, 5},                            // non-crossing
        {},                                            // empty (non-crossing)
        {5},                                           // single element (non-crossing)
        {0, 0, 0, 0},                                  // zeros (crossing)
        {1500000000, 1500000000, 1, 1500000000, 1500000000} // large numbers (overlapped pre-check)
    };

    Solution solver;

    long long checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            bool res = solver.isSelfCrossing(tests[i]);
            checksum += res ? static_cast<long long>(i + 1) : 0;
        }
    }

    auto end = Clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}