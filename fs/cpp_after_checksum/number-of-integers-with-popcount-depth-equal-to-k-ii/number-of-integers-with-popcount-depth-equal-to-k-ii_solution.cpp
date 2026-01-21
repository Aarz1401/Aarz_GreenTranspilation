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
#include <chrono>

using namespace std;

static inline int bit_length_u64(unsigned long long v) {
    if (v == 0ULL) return 0;
    return 64 - __builtin_clzll(v);
}

static inline int ceil_log2_ull(unsigned long long x) {
    // x > 0
    return bit_length_u64(x - 1ULL);
}

struct BIT {
    // 0-indexed Fenwick Tree
    int n;
    vector<int> bit;
    BIT() : n(0) {}
    BIT(int n_) : n(n_), bit(n_ + 1, 0) {}
    void add(int i, int val) {
        ++i; // dummy node
        while (i < (int)bit.size()) {
            bit[i] += val;
            i += (i & -i);
        }
    }
    int query(int i) const {
        ++i; // dummy node
        int ret = 0;
        while (i > 0) {
            ret += bit[i];
            i -= (i & -i);
        }
        return ret;
    }
};

struct Precompute {
    int MAX_BIT_LEN;
    vector<int> D;
    int MAX_K;
    Precompute() {
        unsigned long long MAX_N = 1000000000000000ULL; // 1e15
        MAX_BIT_LEN = bit_length_u64(MAX_N);
        D.assign(MAX_BIT_LEN + 1, 0);
        for (int i = 2; i <= MAX_BIT_LEN; ++i) {
            D[i] = D[__builtin_popcount((unsigned int)i)] + 1;
        }
        MAX_K = 0;
        unsigned long long t = MAX_N;
        while (t != 1ULL) {
            t = (unsigned long long)ceil_log2_ull(t);
            ++MAX_K;
        }
    }
};

static Precompute PRE;

class Solution {
public:
    vector<int> popcountDepth(vector<long long>& nums, vector<vector<long long>>& queries) {
        auto countDepth = [](long long x) -> int {
            if (x == 1LL) return 0;
            int pc = __builtin_popcountll((unsigned long long)x);
            return PRE.D[pc] + 1;
        };

        int n = (int)nums.size();
        vector<BIT> bits;
        bits.reserve(PRE.MAX_K + 1);
        for (int i = 0; i <= PRE.MAX_K; ++i) {
            bits.emplace_back(BIT(n));
        }
        for (int i = 0; i < n; ++i) {
            int d = countDepth(nums[i]);
            bits[d].add(i, +1);
        }

        vector<int> result;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                long long l = q[1], r = q[2], k = q[3];
                int ki = (int)k;
                int rr = (int)r;
                int ll = (int)l;
                int ans = bits[ki].query(rr) - bits[ki].query(ll - 1);
                result.emplace_back(ans);
            } else {
                long long i = q[1], x = q[2];
                int idx = (int)i;
                int old_d = countDepth(nums[idx]);
                int new_d = countDepth(x);
                if (new_d != old_d) {
                    bits[old_d].add(idx, -1);
                    bits[new_d].add(idx, +1);
                }
                nums[idx] = x;
            }
        }
