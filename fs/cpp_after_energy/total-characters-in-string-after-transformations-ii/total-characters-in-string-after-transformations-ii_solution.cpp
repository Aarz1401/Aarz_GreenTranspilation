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
