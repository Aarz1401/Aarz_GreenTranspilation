#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>
using namespace std;

// Original solution (used without modification)
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

// Time:  O(logn)
// Space: O(logn)

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string str_N = to_string(N);
        unordered_set<char> set_D;
        set_D.reserve(D.size() * 2);
        for (const string& s : D) {
            if (!s.empty()) {
                set_D.insert(s[0]);
            }
        }

        int m = static_cast<int>(D.size());
        int L = static_cast<int>(str_N.size());

        auto ipow = [](int base, int exp) -> int {
            long long res = 1;
            long long b = base;
            while (exp > 0) {
                if (exp & 1) res *= b;
                b *= b;
                exp >>= 1;
            }
            return static_cast<int>(res);
        };

        long long result = 0;
        for (int i = 1; i < L; ++i) {
            result += ipow(m, i);
        }

        int i = 0;
        while (i < L) {
            int countLess = 0;
            for (const string& s : D) {
                if (!s.empty() && s[0] < str_N[i]) {
                    ++countLess;
                }
            }
            result += static_cast<long long>(countLess) * ipow(m, L - i - 1);
            if (!set_D.count(str_N[i])) {
                break;
            }
            ++i;
        }
        return static_cast<int>(result + (i == L ? 1 : 0));
    }
};

struct TestCase {
    vector<string> D;
    int N;
};

int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;
    tests.push_back({{"1","3","5","7"}, 100});              // typical example
    tests.push_back({{"1","4","9"}, 1000000000});           // large N, small digit set
    tests.push_back({{"7"}, 8});                            // single digit set
    tests.push_back({{"2","3","5","7"}, 29});               // primes as digits
    tests.push_back({{"1","2","3","4","5","6","7","8","9"}, 999999999}); // many digits, large N
    tests.push_back({{"0","1","2"}, 100});                  // includes zero
    tests.push_back({{"8","9"}, 1000});                     // two high digits
    tests.push_back({{"1"}, 111111});                       // repetitive N with single digit
    tests.push_back({{"3","4","8"}, 3456});                 // mixed mid-range
    tests.push_back({{}, 12345});                           // empty digit set (edge case)

    Solution sol;

    volatile long long checksum_sink = 0; // to avoid optimization
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.atMostNGivenDigitSet(tc.D, tc.N);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    checksum_sink = checksum;

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum_sink << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}