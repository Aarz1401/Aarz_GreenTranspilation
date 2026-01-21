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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        const int MOD = 1000000007;
        const int n = 26;

        auto matMul = [&](const vector<vector<int>>& A, const vector<vector<int>>& B) {
            vector<vector<int>> C(n, vector<int>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int k = 0; k < n; ++k) {
                    if (A[i][k] == 0) continue;
                    long long aik = A[i][k];
                    for (int j = 0; j < n; ++j) {
                        if (B[k][j] == 0) continue;
                        C[i][j] = (C[i][j] + (aik * B[k][j]) % MOD) % MOD;
                    }
                }
            }
            return C;
        };

        auto matPow = [&](vector<vector<int>> base, long long exp) {
            vector<vector<int>> result(n, vector<int>(n, 0));
            for (int i = 0; i < n; ++i) result[i][i] = 1;
            while (exp > 0) {
                if (exp & 1LL) {
                    result = matMul(result, base);
                }
                base = matMul(base, base);
                exp >>= 1LL;
            }
            return result;
        };

        vector<int> cnt(n, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        vector<vector<int>> matrix(n, vector<int>(n, 0));
        for (int i = 0; i < static_cast<int>(nums.size()) && i < n; ++i) {
            for (int j = 1; j <= nums[i]; ++j) {
                matrix[i][(i + j) % n] = 1;
            }
        }

        vector<vector<int>> matrix_pow_t = matPow(matrix, static_cast<long long>(t));

        // Multiply row vector cnt by matrix_pow_t
        vector<int> row(n, 0);
        for (int j = 0; j < n; ++j) {
            long long sum = 0;
            for (int i = 0; i < n; ++i) {
                if (cnt[i] == 0 || matrix_pow_t[i][j] == 0) continue;
                sum = (sum + 1LL * cnt[i] * matrix_pow_t[i][j]) % MOD;
            }
            row[j] = static_cast<int>(sum);
        }

        long long ans = 0;
        for (int v : row) {
            ans += v;
            if (ans >= MOD) ans -= MOD;
        }
        return static_cast<int>(ans % MOD);
    }
};

struct TestCase {
    string s;
    int t;
    vector<int> nums;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: Empty string, t=0, empty nums
    tests.push_back({"", 0, {}});

    // Test 2: Single character, minimal nums
    tests.push_back({"a", 1, {1}});

    // Test 3: Small string, simple transitions
    tests.push_back({"abc", 2, {1, 1, 1}});

    // Test 4: Repeated 'z', sparse matrix across full alphabet
    {
        vector<int> nums4(26);
        for (int i = 0; i < 26; ++i) nums4[i] = i % 3; // 0,1,2 repeating
        tests.push_back({string(10, 'z'), 3, nums4});
    }

    // Test 5: Large counts for 'a', limited transitions
    {
        vector<int> nums5(26, 0);
        nums5[0] = 2; // 'a' -> 'b','c'
        nums5[1] = 1; // 'b' -> 'c'
        tests.push_back({string(1000, 'a'), 8, nums5});
    }

    // Test 6: Partial nums vector smaller than 26
    tests.push_back({"leetcode", 5, {2, 0, 1, 2, 1}});

    // Test 7: Full alphabet string, sparse transitions across all rows
    {
        vector<int> nums7(26);
        for (int i = 0; i < 26; ++i) nums7[i] = (i % 3); // 0,1,2 repeating
        tests.push_back({"abcdefghijklmnopqrstuvwxyz", 7, nums7});
    }

    // Test 8: Very sparse transitions, larger t
    {
        vector<int> nums8(26, 0);
        nums8[0] = 1;  // 'a' -> 'b'
        nums8[1] = 2;  // 'b' -> 'c','d'
        nums8[12] = 1; // 'm' -> 'n'
        nums8[23] = 2; // 'x' -> 'y','z'
        tests.push_back({"abbaabbaab", 16, nums8});
    }

    // Test 9: Long string, nums longer than 26 (extra ignored)
    {
        string base9 = "thequickbrownfoxjumpsoverthelazydog";
        string s9;
        for (int i = 0; i < 6; ++i) s9 += base9; // length ~ 210
        vector<int> nums9(30);
        for (int i = 0; i < 30; ++i) nums9[i] = (i * 7) % 3; // 0,1,2 pattern
        tests.push_back({s9, 12, nums9});
    }

    // Test 10: No transitions (empty nums), t=1
    tests.push_back({"mismatchcases", 1, {}});

    Solution sol;
    volatile uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            int res = sol.lengthAfterTransformations(tc.s, tc.t, tc.nums);
            checksum = (checksum * 1315423911ull) ^ static_cast<uint64_t>(res + 0x9e3779b97f4a7c15ull);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << static_cast<uint64_t>(checksum) << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}