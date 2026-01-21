#include <vector>
#include <string>
#include <utility>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}


static vector<int> global_cnt = {0, 0};

class Solution {
public:
    int countKReducibleNumbers(string s, int k) {
        const int MOD = 1000000007;
        int n = static_cast<int>(s.size());

        // Ensure cnt is computed up to index n-1
        while ((int)global_cnt.size() <= n - 1) {
            int idx = (int)global_cnt.size();
            int pc = __builtin_popcount((unsigned int)idx);
            global_cnt.push_back(global_cnt[pc] + 1);
        }

        vector<long long> dp(n, 0);
        int curr = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                dp[j + 1] = (dp[j + 1] + dp[j]) % MOD;
            }
            if (s[i] != '1') {
                continue;
            }
            dp[curr] = (dp[curr] + 1) % MOD;
            curr += 1;
        }

        long long result = 0;
        for (int i = 1; i < n; ++i) {
            if (global_cnt[i] < k) {
                result = (result + dp[i]) % MOD;
            }
        }
        return (int)(result % MOD);
    }
};

int main() {

    vector<pair<string,int>> tests = {
        {"1", 1},
        {"0", 1},
        {"10", 1},
        {"10101", 2},
        {"11111", 3},
        {"00000", 1},
        {"110010100111", 2},
        {"10101010101010101010101010101010", 1},
        {"1001001001001001001", 2},
        {"111000111000111000111000111000111000111000111000111000111000", 4}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.countKReducibleNumbers(tc.first, tc.second);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}