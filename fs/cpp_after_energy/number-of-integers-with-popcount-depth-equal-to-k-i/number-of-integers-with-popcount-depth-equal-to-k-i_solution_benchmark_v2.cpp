#include <vector>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

static inline int bit_length(unsigned long long x) {
    if (x == 0) return 0;
    return 64 - __builtin_clzll(x);
}

struct Precompute {
    int MAX_BIT_LEN;
    vector<vector<long long>> nCr;
    vector<int> D;
    Precompute() {
        const unsigned long long MAX_N = 1000000000000000ULL; // 1e15
        MAX_BIT_LEN = bit_length(MAX_N);
        nCr.assign(MAX_BIT_LEN + 1, vector<long long>(MAX_BIT_LEN + 1, 0));
        for (int i = 0; i <= MAX_BIT_LEN; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (0 < j && j < i) {
                    nCr[i][j] = nCr[i - 1][j] + nCr[i - 1][j - 1];
                } else {
                    nCr[i][j] = 1;
                }
            }
        }
        D.assign(MAX_BIT_LEN + 1, 0);
        for (int i = 2; i <= MAX_BIT_LEN; ++i) {
            D[i] = D[__builtin_popcount(i)] + 1;
        }
    }
};

static Precompute PC;

class Solution {
public:
    long long popcountDepth(long long n, int k) {
        auto count_c = [&](int c) -> long long {
            long long result = 0;
            int cnt = 0;
            unsigned long long un = static_cast<unsigned long long>(n);
            int bl = bit_length(un);
            for (int i = bl - 1; i >= 0; --i) {
                if ((un & (1ULL << i)) == 0) continue;
                int need = c - cnt;
                if (need >= 0 && need <= i) {
                    result += PC.nCr[i][need];
                }
                cnt += 1;
            }
            if (cnt == c) {
                result += 1;
            }
            return result;
        };

        if (k == 0) {
            return 1;
        }
        if (k == 1) {
            return bit_length(static_cast<unsigned long long>(n)) - 1;
        }
        long long ans = 0;
        int bl = bit_length(static_cast<unsigned long long>(n));
        for (int c = 2; c <= bl; ++c) {
            if (PC.D[c] == k - 1) {
                ans += count_c(c);
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;

    vector<pair<long long, int>> tests = {
        {1LL, 0},
        {1LL, 1},
        {3LL, 2},
        {5LL, 2},
        {100LL, 1},
        {1048576LL, 3},
        {562949953421311LL, 1},
        {999999999999999LL, 0},
        {1000000000000000LL, 1},
        {12345LL, 4}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            int r = static_cast<int>(sol.popcountDepth(t.first, t.second));
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}