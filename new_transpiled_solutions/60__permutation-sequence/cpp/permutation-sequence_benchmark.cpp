#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <utility>

// Original Solution (used without modification)
#include <string>
#include <vector>

class Solution {
public:
    std::string getPermutation(int n, int k) {
        std::vector<int> perm;
        perm.reserve(n);
        for (int i = 1; i <= n; ++i) {
            perm.push_back(i);
        }
        
        long long kk = static_cast<long long>(k) - 1;
        long long fact = 1;
        for (int i = 2; i <= n - 1; ++i) {
            fact *= i;
        }
        
        std::string seq;
        seq.reserve(n);
        for (int i = n - 1; i >= 0; --i) {
            int idx = static_cast<int>(kk / fact);
            seq += std::to_string(perm[idx]);
            perm.erase(perm.begin() + idx);
            if (i > 0) {
                kk %= fact;
                fact /= i;
            }
        }
        return seq;
    }
};

int main() {
    // Define 10 diverse test inputs (n, k)
    std::vector<std::pair<int, int>> tests = {
        {1, 1},
        {2, 1},
        {2, 2},
        {3, 1},
        {3, 6},       // max for n=3
        {4, 9},       // mid for n=4
        {5, 120},     // max for n=5
        {6, 400},     // within range for n=6 (<=720)
        {7, 5040},    // max for n=7
        {9, 362880}   // max for n=9
    };

    Solution sol;
    unsigned long long checksum = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            int n = tests[t].first;
            int k = tests[t].second;
            std::string res = sol.getPermutation(n, k);
            for (unsigned char c : res) {
                checksum = (checksum * 1315423911ull) ^ c;
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}