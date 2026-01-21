#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <array>
#include <string>
#include <cstdint>
#include <chrono>
using namespace std;

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    int uniqueLetterString(string S) {
        const int64_t M = 1000000007LL;
        vector<array<int, 2>> index(26);
        for (int i = 0; i < 26; ++i) {
            index[i] = {-1, -1};
        }
        int64_t result = 0;
        for (int i = 0; i < static_cast<int>(S.size()); ++i) {
            int c = S[i] - 'A';
            int k = index[c][0];
            int j = index[c][1];
            result = (result + (int64_t)(i - j) * (j - k)) % M;
            index[c] = {j, i};
        }
        for (int i = 0; i < 26; ++i) {
            int k = index[i][0];
            int j = index[i][1];
            result = (result + (int64_t)(static_cast<int>(S.size()) - j) * (j - k)) % M;
        }
        return static_cast<int>(result % M);
    }
};

int main() {
    // Prepare 10 diverse uppercase test inputs
    vector<string> tests;
    tests.reserve(10);

    tests.push_back("");                           // 1. Empty string
    tests.push_back("A");                          // 2. Single character
    tests.push_back("AAAAAAA");                    // 3. All same character
    tests.push_back("ABC");                        // 4. All unique, short
    tests.push_back("ABCA");                       // 5. Repeat with gap
    tests.push_back("ABABABAB");                   // 6. Alternating pattern
    tests.push_back("LEETCODE");                   // 7. Typical mixed repeats
    tests.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // 8. All 26 unique

    // 9. Long patterned string cycling A..Z
    string t9;
    t9.reserve(4096);
    for (int i = 0; i < 4096; ++i) {
        t9.push_back(static_cast<char>('A' + (i % 26)));
    }
    tests.push_back(t9);

    // 10. Long blocks of repeated characters
    string t10;
    t10.append(1000, 'A');
    t10.append(1000, 'B');
    t10.append(1000, 'C');
    t10.append(1000, 'D');
    tests.push_back(t10);

    Solution sol;
    uint64_t checksum = 0;

    using Clock = chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += static_cast<uint64_t>(sol.uniqueLetterString(s));
        }
    }

    auto end = Clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}