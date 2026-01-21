#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        (void)precomp; // ensure precomputation is done
        int upto = std::min(n, x);
        long long ans = 0;
        for (int i = 1; i <= upto; ++i) {
            long long term = (long long)NCR[x][i] * DP[n][i] % MOD;
            term = term * POWT[y][i] % MOD;
            ans += term;
            if (ans >= MOD) ans -= MOD;
        }
        return (int)ans;
    }

private:
    static const int MOD = 1000000007;
    static const int MAX_N = 1000;
    static const int MAX_X = 1000;
    static const int MAX_Y = 1000;
    static const int R = (MAX_N < MAX_X ? MAX_N : MAX_X);

    static std::vector<std::vector<int>> NCR;
    static std::vector<std::vector<int>> DP;
    static std::vector<std::vector<int>> POWT;

    struct Precomp {
        Precomp() {
            NCR.assign(MAX_N + 1, std::vector<int>(MAX_N + 1, 0));
            DP.assign(MAX_N + 1, std::vector<int>(MAX_N + 1, 0));
            POWT.assign(MAX_Y + 1, std::vector<int>(R + 1, 1));

            NCR[0][0] = 1;
            DP[0][0] = 1;
            for (int i = 1; i <= MAX_N; ++i) {
                NCR[i][0] = 1;
                for (int j = 1; j <= i; ++j) {
                    int a = NCR[i - 1][j];
                    int b = NCR[i - 1][j - 1];
                    int c = a + b;
                    if (c >= MOD) c -= MOD;
                    NCR[i][j] = c;

                    long long t1 = (long long)DP[i - 1][j] * j % MOD;
                    long long t2 = (long long)DP[i - 1][j - 1] * j % MOD;
                    DP[i][j] = (int)((t1 + t2) % MOD);
                }
            }

            for (int base = 1; base <= MAX_Y; ++base) {
                for (int exp = 1; exp <= R; ++exp) {
                    POWT[base][exp] = (int)((long long)POWT[base][exp - 1] * base % MOD);
                }
            }
        }
    };
    static Precomp precomp;
};

const int Solution::MOD;
const int Solution::MAX_N;
const int Solution::MAX_X;
const int Solution::MAX_Y;
const int Solution::R;

std::vector<std::vector<int>> Solution::NCR;
std::vector<std::vector<int>> Solution::DP;
std::vector<std::vector<int>> Solution::POWT;
Solution::Precomp Solution::precomp;

struct InputCase {
    int n, x, y;
};

int main() {
    std::vector<InputCase> tests = {
        {0, 0, 0},
        {1, 1, 1},
        {2, 3, 5},
        {10, 10, 0},
        {50, 20, 7},
        {200, 500, 1000},
        {1000, 1000, 1000},
        {999, 1000, 2},
        {100, 1, 999},
        {345, 678, 123}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.numberOfWays(tc.n, tc.x, tc.y);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}