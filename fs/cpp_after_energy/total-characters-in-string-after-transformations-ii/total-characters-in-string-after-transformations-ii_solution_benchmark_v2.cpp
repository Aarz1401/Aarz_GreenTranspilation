#include <vector>
#include <string>

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
    Solution sol;
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1
    vector<int> nums1(26, 0);
    tests.push_back({"a", 0, nums1});

    // Test 2
    vector<int> nums2(26, 1);
    tests.push_back({"abc", 1, nums2});

    // Test 3
    vector<int> nums3(26, 0);
    nums3[25] = 2; // 'z'
    tests.push_back({"zzz", 2, nums3});

    // Test 4
    vector<int> nums4(26);
    for (int i = 0; i < 26; ++i) nums4[i] = i % 3;
    tests.push_back({"leetcode", 3, nums4});

    // Test 5
    vector<int> nums5(26);
    for (int i = 0; i < 26; ++i) nums5[i] = i % 5;
    tests.push_back({"abcdefghijklmnopqrstuvwxyz", 5, nums5});

    // Test 6
    vector<int> nums6(26, 0);
    nums6[0] = 3; // 'a'
    tests.push_back({"aaaaaaaaaaaaaaaaaaaa", 10, nums6});

    // Test 7
    vector<int> nums7(26, 2);
    tests.push_back({"mixandmatch", 26, nums7});

    // Test 8
    vector<int> nums8(26);
    for (int i = 0; i < 26; ++i) nums8[i] = (i % 2 == 0) ? 2 : 1;
    tests.push_back({"bcdxyzab", 12, nums8});

    // Test 9
    vector<int> nums9(26, 0);
    nums9[16] = 4; // 'q'
    nums9[22] = 3; // 'w'
    nums9[19] = 2; // 't'
    tests.push_back({"qwerty", 32, nums9});

    // Test 10
    vector<int> nums10 = {3,0,1,2,0,1,3,0,2,1,0,3,1,0,2,1,0,2,3,0,1,2,0,1,2,3};
    tests.push_back({"thequickbrownfox", 20, nums10});

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.lengthAfterTransformations(tc.s, tc.t, tc.nums);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}