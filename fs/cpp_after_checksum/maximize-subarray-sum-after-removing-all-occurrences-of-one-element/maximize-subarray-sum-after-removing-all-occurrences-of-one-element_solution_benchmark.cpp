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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<int>> tests;
    tests.reserve(10);

    // 1. All positive
    tests.push_back({1, 2, 3, 4, 5});

    // 2. All negative
    tests.push_back({-1, -2, -3, -4});

    // 3. Mixed positives and negatives
    tests.push_back({3, -2, 5, -1, 6, -3});

    // 4. Large values and extremes
    tests.push_back({INT_MAX, -1, INT_MAX, -2, -1000000000, 999999999});

    // 5. Many zeros
    {
        vector<int> v5(100, 0);
        tests.push_back(move(v5));
    }

    // 6. Alternating duplicates to stress mn1
    tests.push_back({5, -5, 5, -5, 5, -5, 5, -5});

    // 7. Programmatically generated patterned sequence (length 200)
    {
        vector<int> v7;
        v7.reserve(200);
        for (int i = 0; i < 200; ++i) {
            int val = static_cast<int>((i * 37) % 201) - 100; // range [-100, 100]
            // Add some alternating negation to diversify
            if (i % 3 == 0) val = -val;
            v7.push_back(val);
        }
        tests.push_back(move(v7));
    }

    // 8. Monotonic negative to positive crossing
    {
        vector<int> v8;
        for (int x = -50; x <= 50; ++x) v8.push_back(x);
        tests.push_back(move(v8));
    }

    // 9. Single element
    tests.push_back({42});

    // 10. Empty vector
    tests.push_back({});

    Solution sol;
    unsigned long long checksum = 0;

    const int iterations = 1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            long long res = sol.maxSubarraySum(tests[i]);
            // Mix into checksum to avoid optimization
            checksum ^= static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + (static_cast<unsigned long long>(iter) << 1) + i;
            checksum = (checksum << 7) | (checksum >> (64 - 7));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}