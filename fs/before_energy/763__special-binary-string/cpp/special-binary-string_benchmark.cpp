#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdint>

using namespace std;

// Time:  f(n) = k * f(n/k) + n/k * klogk <= O(logn * nlogk) <= O(n^2)
//        n is the length of S, k is the max number of special strings in each depth
// Space: O(n)

class Solution {
public:
    string makeLargestSpecial(string S) {
        vector<string> result;
        int anchor = 0, count = 0;
        for (int i = 0; i < static_cast<int>(S.size()); ++i) {
            count += (S[i] == '1') ? 1 : -1;
            if (count == 0) {
                string inner = S.substr(anchor + 1, i - anchor - 1);
                string rec = makeLargestSpecial(inner);
                result.push_back(string("1") + rec + "0");
                anchor = i + 1;
            }
        }
        sort(result.begin(), result.end(), greater<string>());
        string ans;
        for (const auto& s : result) {
            ans += s;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse special binary string test inputs
    vector<string> inputs;
    inputs.push_back("10");                    // minimal
    inputs.push_back("1100");                  // nested once
    inputs.push_back("1010");                  // concatenation of basics
    inputs.push_back("110100");                // mixed nested/concat
    inputs.push_back("111000");                // deep nesting
    inputs.push_back("11011000");              // example-like
    inputs.push_back("11110000");              // deeper nesting
    inputs.push_back("1101001100");            // longer mixed
    inputs.push_back("110110110000");          // multiple clusters
    {
        string longRep;
        longRep.reserve(8 * 25);
        for (int i = 0; i < 25; ++i) longRep += "11011000"; // length 200
        inputs.push_back(longRep);            // long repeated special string
    }

    Solution solver;

    uint64_t checksum = 1469598103934665603ull; // FNV-1a offset basis

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : inputs) {
            string out = solver.makeLargestSpecial(s);
            for (unsigned char c : out) {
                checksum ^= c;
                checksum *= 1099511628211ull; // FNV-1a prime
            }
            // Mix in iteration and size to further prevent optimization
            checksum ^= static_cast<uint64_t>(iter + out.size());
            checksum *= 1099511628211ull;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}