#include <bits/stdc++.h>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}
using namespace std::chrono;

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

struct TestInput {
    vector<long long> nums;
    vector<vector<long long>> queries;
};

int main() {
    // Generate 10 diverse test inputs
    vector<TestInput> tests;
    tests.reserve(10);

    int K = PRE.MAX_K; // allowable depth range [0..K]
    const long long MAX_SAFE = 1000000000000000LL; // 1e15
    const long long ALL50ONES = (1ULL << 50) - 1;  // popcount = 50 (<= MAX_BIT_LEN)

    // Test 1: Single element array, query all possible k
    {
        TestInput t;
        t.nums = {1};
        for (int k = 0; k <= K; ++k) {
            t.queries.push_back({1, 0, 0, (long long)k});
        }
        // Update to 0 and query again
        t.queries.push_back({2, 0, 0});
        t.queries.push_back({1, 0, 0, 1});
        tests.push_back(std::move(t));
    }

    // Test 2: Small array with mixed values, updates and queries
    {
        TestInput t;
        t.nums = {0, 1, 2, 3, 4, 5, 6, 7};
        t.queries = {
            {1, 0, 7, 1},
            {2, 3, 10},
            {1, 2, 5, 2},
            {2, 0, (long long)ALL50ONES},
            {1, 0, 7, (long long)min(K, 3)},
            {2, 7, 1},
            {1, 7, 7, 0}
        };
        tests.push_back(std::move(t));
    }

    // Test 3: Medium array with large values near 1e15
    {
        TestInput t;
        int n = 12;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) {
            t.nums[i] = (123456789123LL * (i + 1)) % MAX_SAFE;
        }
        t.queries = {
            {1, 0, n - 1, (long long)min(K, 2)},
            {2, 5, MAX_SAFE - 1},
            {1, 3, 8, (long long)min(K, 4)},
            {2, 0, 1},
            {1, 0, 0, 0},
            {2, 11, (long long)ALL50ONES},
            {1, 9, 11, (long long)min(K, 3)}
        };
        tests.push_back(std::move(t));
    }

    // Test 4: Powers of two
    {
        TestInput t;
        int n = 20;
        t.nums.resize(n);
        t.nums[0] = 1;
        for (int i = 1; i < n; ++i) {
            t.nums[i] = (1LL << (i % 50)); // keep within 50 bits
        }
        t.queries = {
            {1, 0, n - 1, 0},
            {1, 1, 10, (long long)min(K, 2)},
            {2, 10, (long long)ALL50ONES},
            {1, 10, 10, (long long)min(K, 3)},
            {2, 0, 2},
            {1, 0, 0, (long long)min(K, 2)}
        };
        tests.push_back(std::move(t));
    }

    // Test 5: All zeros
    {
        TestInput t;
        int n = 30;
        t.nums.assign(n, 0);
        t.queries = {
            {1, 0, n - 1, (long long)min(K, 1)},
            {2, 15, 1},
            {1, 10, 20, 0},
            {2, 29, (long long)ALL50ONES},
            {1, 25, 29, (long long)min(K, 3)}
        };
        tests.push_back(std::move(t));
    }

    // Test 6: Alternating small and large values
    {
        TestInput t;
        int n = 25;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) t.nums[i] = i + 2;
            else t.nums[i] = MAX_SAFE - (i * 99991 % 100000) - 1;
        }
        t.queries = {
            {1, 0, n - 1, (long long)min(K, 4)},
            {2, 12, 1},
            {2, 13, 0},
            {1, 10, 15, (long long)min(K, 2)},
            {1, 5, 5, 0}
        };
        tests.push_back(std::move(t));
    }

    // Test 7: Alternating 1 and (2^50 - 1)
    {
        TestInput t;
        int n = 18;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i % 2 == 0) ? 1 : (long long)ALL50ONES;
        t.queries = {
            {1, 0, n - 1, 0},
            {1, 0, n - 1, (long long)min(K, 4)},
            {2, 1, 1},
            {2, 2, (long long)ALL50ONES},
            {1, 1, 2, (long long)min(K, 3)}
        };
        tests.push_back(std::move(t));
    }

    // Test 8: Sequential updates across range then queries
    {
        TestInput t;
        int n = 16;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = i + 1;
        for (int i = 0; i < n; i += 3) {
            t.queries.push_back({2, (long long)i, (long long)((i % 2 == 0) ? ALL50ONES : 0)});
        }
        t.queries.push_back({1, 0, n - 1, (long long)min(K, 3)});
        t.queries.push_back({1, 5, 10, (long long)min(K, 2)});
        tests.push_back(std::move(t));
    }

    // Test 9: Many single-index range queries
    {
        TestInput t;
        int n = 22;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i * 9876543211LL + 12345) % MAX_SAFE;
        for (int i = 0; i < n; ++i) {
            t.queries.push_back({1, (long long)i, (long long)i, (long long)(i % (K + 1))});
        }
        t.queries.push_back({2, 0, 1});
        t.queries.push_back({1, 0, 0, 0});
        tests.push_back(std::move(t));
    }

    // Test 10: Mixed random-like updates and queries with bounded values
    {
        TestInput t;
        int n = 28;
        t.nums.resize(n);
        long long seed = 88172645463393265ULL;
        for (int i = 0; i < n; ++i) {
            seed ^= seed << 7;
            seed ^= seed >> 9;
            t.nums[i] = (seed % MAX_SAFE);
        }
        for (int i = 0; i < 20; ++i) {
            int idx = (i * 7) % n;
            long long val = ((seed + i * 1234567) % MAX_SAFE);
            t.queries.push_back({2, (long long)idx, val});
            int l = (i * 3) % n;
            int r = min(n - 1, l + (i % 5));
            t.queries.push_back({1, (long long)l, (long long)r, (long long)(i % (K + 1))});
        }
        tests.push_back(std::move(t));
    }

    // Benchmark loop
    Solution sol;
    long long checksum = 0;

    const int iterations = 1000;
    auto start = high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            // Make copies because the solution mutates nums via updates
            auto nums = t.nums;
            auto queries = t.queries;
            auto res = sol.popcountDepth(nums, queries);
            for (int v : res) checksum += v;
        }
    }
    auto end = high_resolution_clock::now();
    auto elapsed_ms = duration_cast<milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}