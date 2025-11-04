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
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    struct SparseTableGCD {
        vector<vector<int>> st;
        vector<int> log2of;
        SparseTableGCD() {}
        explicit SparseTableGCD(const vector<int>& arr) {
            int n = arr.size();
            log2of.assign(n + 1, 0);
            for (int i = 2; i <= n; ++i) {
                log2of[i] = log2of[i / 2] + 1;
            }
            int k = (n > 0) ? log2of[n] : 0;
            st.assign(k + 1, vector<int>(n, 0));
            if (n > 0) {
                st[0] = arr;
                for (int i = 1; i <= k; ++i) {
                    int len = 1 << i;
                    int half = len >> 1;
                    for (int j = 0; j + len <= n; ++j) {
                        st[i][j] = std::gcd(st[i - 1][j], st[i - 1][j + half]);
                    }
                }
            }
        }
        int query(int L, int R) const {
            if (L > R) return 0;
            int i = log2of[R - L + 1];
            return std::gcd(st[i][L], st[i][R - (1 << i) + 1]);
        }
    };

    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        SparseTableGCD rmq(nums);
        auto check = [&](int l) -> bool {
            long long cnt = 0;
            int i = 0;
            while (i + l - 1 < n) {
                if (rmq.query(i, i + l - 1) >= 2) {
                    ++cnt;
                    i += l;
                } else {
                    ++i;
                }
            }
            return cnt > maxC;
        };

        int l = 1, r = n;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (!check(mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return r;
    }
};

struct TestCase {
    vector<int> nums;
    int maxC;
};

int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    // 0) Empty array
    tests.push_back({{}, 0});

    // 1) Single element
    tests.push_back({{2}, 0});

    // 2) All evens (high gcd)
    tests.push_back({{2, 4, 6, 8, 10, 12, 14, 16}, 2});

    // 3) All odd primes (mostly gcd 1)
    tests.push_back({{3, 5, 7, 11, 13, 17, 19}, 0});

    // 4) Mix with zeros
    tests.push_back({{0, 0, 2, 4, 0, 6, 0, 8, 10, 0}, 3});

    // 5) Includes negatives
    tests.push_back({{-2, -4, 6, -8, 10, -12}, 1});

    // 6) Mixed values with likely gcd 1
    tests.push_back({{14, 25, 9, 35, 22, 49, 18, 55, 26}, 1});

    // 7) All ones (gcd always 1)
    tests.push_back({{1, 1, 1, 1, 1, 1, 1}, 5});

    // 8) Composite numbers with many common factors
    tests.push_back({{12, 18, 24, 30, 36, 42, 48, 54}, 5});

    // 9) Larger mixed array programmatically generated
    vector<int> arr9;
    for (int i = 1; i <= 50; ++i) {
        if (i % 5 == 0) arr9.push_back(0);               // introduce zeros
        else if (i % 2 == 0) arr9.push_back(i * 2);      // even numbers
        else if (i % 3 == 0) arr9.push_back(i * 3);      // multiples of 3
        else arr9.push_back(i * 7 + 1);                  // numbers often coprime
    }
    tests.push_back({arr9, 7});

    const int iterations = 1000;

    Solution solver;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t k = 0; k < tests.size(); ++k) {
            // Slightly vary maxC per iteration to avoid being trivially optimized
            int maxC = tests[k].maxC + (iter & 1);
            checksum += solver.minStable(tests[k].nums, maxC);
        }
    }

    auto end = high_resolution_clock::now();
    auto dur_ns = duration_cast<nanoseconds>(end - start).count();
    double dur_ms = dur_ns / 1e6;

    // Print result to prevent optimization and report timing
    cout << "Checksum: " << checksum << '\n';
    cout << "Time: " << dur_ns << " ns (" << dur_ms << " ms)" << '\n';

    return 0;
}