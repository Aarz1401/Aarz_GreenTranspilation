#include <vector>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
        return result;
    }
};

struct Test {
    vector<long long> nums;
    vector<vector<long long>> queries;
};

int main() {
    vector<Test> tests;
    tests.reserve(10);

    {
        Test t;
        t.nums = {1};
        t.queries = {
            {1, 0, 0, 0},
            {2, 0, 2},
            {1, 0, 0, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {2, 3, 4};
        t.queries = {
            {1, 0, 2, 1},
            {1, 1, 2, 2},
            {2, 2, 7},
            {1, 0, 2, 3}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1, 2, 15, 16, 31};
        t.queries = {
            {1, 0, 4, 0},
            {1, 0, 4, 1},
            {1, 0, 4, 2},
            {1, 0, 4, 3},
            {1, 0, 4, 4},
            {2, 0, 1024},
            {1, 0, 4, 0}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {6, 10, 12, 24};
        t.queries = {
            {1, 0, 3, 2},
            {2, 1, 10},
            {1, 1, 2, 2},
            {2, 3, 5},
            {1, 0, 3, 2}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {999999999999999LL, 500000000000000LL, 1LL, 2LL, 3LL, 4LL};
        t.queries = {
            {1, 0, 5, 5},
            {1, 2, 5, 0},
            {2, 2, 8},
            {1, 0, 5, 0},
            {1, 0, 5, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {5, 7, 9, 11, 13, 17, 21, 33};
        t.queries = {
            {1, 0, 7, 3},
            {2, 4, 1},
            {1, 0, 7, 0},
            {1, 3, 5, 2}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
        t.queries = {
            {1, 0, 9, 4},
            {2, 9, 1},
            {1, 0, 9, 0},
            {1, 0, 9, 3}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1LL << 49, 1LL << 48, 1LL << 47, 1LL << 46, 1LL << 45};
        t.queries = {
            {1, 0, 4, 1},
            {2, 2, 3},
            {1, 0, 4, 2},
            {1, 1, 3, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {123456789012345LL, 98765432109876LL, 555555555555555LL, 222222222222222LL, 99999999999999LL, 314159265358979LL, 271828182845904LL};
        t.queries = {
            {1, 0, 6, 3},
            {2, 5, 1},
            {1, 0, 6, 0},
            {2, 0, 2},
            {1, 0, 3, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1, 2, 3, 4, 5, 6};
        t.queries = {
            {1, 0, 5, 0},
            {1, 0, 5, 1},
            {2, 0, 7},
            {1, 0, 2, 3},
            {2, 4, 1},
            {1, 0, 5, 0}
        };
        tests.push_back(t);
    }

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (int t = 0; t < (int)tests.size(); ++t) {
            Test cur = tests[t];
            Solution sol;
            vector<int> out = sol.popcountDepth(cur.nums, cur.queries);
            DoNotOptimize(out); 
            // for (int v : out) checksum += v;
            // checksum += (int)out.size();
        }
        //sink = checksum;
    }

    return 0;
}