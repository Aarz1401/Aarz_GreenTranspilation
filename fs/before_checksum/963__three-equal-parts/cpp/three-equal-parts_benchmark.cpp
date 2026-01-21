#include <chrono>
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

// Original Solution (unchanged)
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

int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> tests;

    // 1) Empty array
    tests.push_back({});

    // 2) Single zero
    tests.push_back({0});

    // 3) Single one (not divisible by 3)
    tests.push_back({1});

    // 4) All zeros
    tests.push_back({0, 0, 0, 0, 0});

    // 5) Not divisible by 3
    tests.push_back({1, 1, 0});

    // 6) Valid classic example
    tests.push_back({1, 0, 1, 0, 1});

    // 7) Valid "100" repeated
    tests.push_back({1, 0, 0, 1, 0, 0, 1});

    // 8) Valid "110" pattern repeated
    tests.push_back({1, 1, 0, 1, 1, 0, 1, 1, 0});

    // 9) Likely invalid due to trailing zeros mismatch
    tests.push_back({1, 0, 1, 0, 1, 0, 0});

    // 10) Large valid with long trailing zeros alignment
    {
        vector<int> big;
        big.insert(big.end(), 500, 0);
        big.push_back(1);
        big.insert(big.end(), 500, 0);
        big.push_back(1);
        big.insert(big.end(), 500, 0);
        big.push_back(1);
        big.insert(big.end(), 500, 0);
        tests.push_back(move(big));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<int> res = sol.threeEqualParts(tests[i]);
            // Combine results into checksum to avoid optimization
            checksum += ((static_cast<long long>(res[0]) << 32) ^ (static_cast<unsigned long long>(res[1]) & 0xffffffffULL)) + static_cast<long long>(i) + iter;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}