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
#include <random>

using namespace std;

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        struct SegmentTree {
            int n;
            int base;
            int k;
            vector<vector<int>> tree; // each node stores vector<int> of size k+1; last index k stores product mod k

            SegmentTree(const vector<int>& nums, int k_) : n((int)nums.size()), k(k_) {
                base = 1;
                while (base < n) base <<= 1;
                tree.assign(base << 1, vector<int>());
                for (int i = 0; i < n; ++i) {
                    tree[base + i] = make_leaf(nums[i]);
                }
                for (int i = base - 1; i >= 1; --i) {
                    tree[i] = merge(tree[i << 1], tree[(i << 1) + 1]);
                }
            }

            inline int mod_norm(long long x) const {
                long long r = x % k;
                if (r < 0) r += k;
                return (int)r;
            }

            vector<int> make_leaf(long long v) const {
                vector<int> cnt(k + 1, 0);
                int r = mod_norm(v);
                cnt[r] = 1;
                cnt[k] = r;
                return cnt;
            }

            vector<int> merge(const vector<int>& x, const vector<int>& y) const {
                if (x.empty()) return y;
                if (y.empty()) return x;
                vector<int> cnt = x;
                int xl = x[k];
                for (int i = 0; i < k; ++i) {
                    int idx = (int)((1LL * xl * i) % k);
                    cnt[idx] += y[i];
                }
                cnt[k] = (int)((1LL * x[k] * y[k]) % k);
                return cnt;
            }

            void update(int idx, long long val) {
                int x = base + idx;
                tree[x] = make_leaf(val);
                while (x > 1) {
                    x >>= 1;
                    tree[x] = merge(tree[x << 1], tree[(x << 1) + 1]);
                }
            }

            vector<int> query(int L, int R) const {
                L += base;
                R += base;
                vector<int> left, right;
                while (L <= R) {
                    if (L & 1) {
                        left = merge(left, tree[L]);
                        ++L;
                    }
                    if ((R & 1) == 0) {
                        right = merge(tree[R], right);
                        --R;
                    }
                    L >>= 1;
                    R >>= 1;
                }
                return merge(left, right);
            }
        };

        SegmentTree st(nums, k);
        int q = (int)queries.size();
        vector<int> result(q, 0);
        int n = (int)nums.size();
        for (int idx = 0; idx < q; ++idx) {
            int i = queries[idx][0];
            int v = queries[idx][1];
            int s = queries[idx][2];
            int x = queries[idx][3];
            st.update(i, v);
            vector<int> res = st.query(s, n - 1);
            result[idx] = (x >= 0 && x < (int)res.size()) ? res[x] : 0;
        }
        return result;
    }
};

struct TestCase {
    vector<int> nums;
    int k;
    vector<vector<int>> queries;
};

static vector<TestCase> buildTests() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: small array, k=1 edge case
    {
        TestCase t;
        t.nums = {1, 2, 3, 4, 5};
        t.k = 1;
        t.queries = {
            {0, 10, 0, 0},
            {4, -7, 2, 1},
            {2, 3, 1, 5},   // x out of range
            {1, -1, 4, 0},
            {3, 100, 3, 1}
        };
        tests.push_back(move(t));
    }

    // Test 2: negatives and zeros, k=5
    {
        TestCase t;
        t.nums = {-5, -10, 15, -20, 25, 0};
        t.k = 5;
        t.queries = {
            {1, -15, 0, 0},
            {3, -2, 2, 5},  // x out of range
            {5, 7, 1, 4},
            {0, -100, 3, 2},
            {2, 9, 5, 5},   // x out of range
            {4, 11, 4, 1}
        };
        tests.push_back(move(t));
    }

    // Test 3: zeros and ones, s possibly > n-1 to test empty query
    {
        TestCase t;
        t.nums = {0, 0, 1, 1, 0, 1, 0, 1};
        t.k = 7;
        t.queries = {
            {0, 0, 8, 3},   // s == n, empty range
            {7, -3, 0, 6},
            {4, 5, 6, 7},   // x == k
            {2, -2, 5, 0},
            {5, 14, 3, 1}
        };
        tests.push_back(move(t));
    }

    // Test 4: k large relative to values
    {
        TestCase t;
        t.k = 1000;
        int n = 20;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i % 2 == 0 ? 123456 - i * 111 : -654321 + i * 77);
        t.queries = {
            {0, 999999, 0, 0},
            {5, -250000, 3, 10},
            {10, 314159, 7, 1000}, // x == k
            {15, -271828, 2, 2},
            {19, 42, 19, 7},
            {1, -1, 1, 1234},      // x out of range
            {7, 777, 4, 9},
            {12, -888, 6, 0},
            {8, 0, 5, 500},
            {3, 123, 9, 1}
        };
        tests.push_back(move(t));
    }

    // Test 5: prime k, moderate size
    {
        TestCase t;
        t.k = 97;
        t.nums = {
            5, -12, 33, 47, -58, 69, -70, 81,
            92, -103, 114, -125, 136, -147, 158, -169
        };
        t.queries = {
            {0, -5, 0, 0},
            {15, 169, 8, 96},   // x == k-1
            {7, 1000, 4, 50},
            {3, -3000, 6, 97},  // x == k (out of range since size is k+1; this is in range actually, size = 98; x=97 in range)
            {10, 777, 10, 10},
            {5, -555, 2, 20},
            {12, 2468, 5, 97},  // x == k
            {1, -13579, 7, 0},
            {9, 86420, 9, 1},
            {6, 0, 3, 2},
            {11, -1, 12, 97},   // x == k
            {14, 31415, 1, 3}
        };
        tests.push_back(move(t));
    }

    // Test 6: single element array
    {
        TestCase t;
        t.nums = {7};
        t.k = 3;
        t.queries = {
            {0, 5, 0, 0},
            {0, -2, 0, 1},
            {0, 9, 0, 2},   // x == k
            {0, 0, 0, 3},   // x out of range
            {0, -7, 0, 1}
        };
        tests.push_back(move(t));
    }

    // Test 7: larger n, composite k
    {
        TestCase t;
        t.k = 16;
        int n = 128;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i % 3 == 0 ? i : -i);
        for (int q = 0; q < 64; ++q) {
            int i = (q * 7) % n;
            int v = (q % 2 == 0 ? q * 123 - 500 : -q * 77 + 250);
            int s = min(n - 1, (q * 3) % n);
            int x = (q * 5) % (t.k + 4); // sometimes out of range
            t.queries.push_back({i, v, s, x});
        }
        tests.push_back(move(t));
    }

    // Test 8: duplicates, k=9
    {
        TestCase t;
        t.k = 9;
        int n = 50;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i % 5 == 0 ? 45 : (i % 2 ? -18 : 27));
        for (int q = 0; q < 25; ++q) {
            int i = (q * 11) % n;
            int v = (q % 4 == 0 ? 0 : (q * 91 - 100));
            int s = (q % n);
            int x = (q * 2) % (t.k + 3);
            t.queries.push_back({i, v, s, x});
        }
        tests.push_back(move(t));
    }

    // Test 9: s == n-1 queries, k=8
    {
        TestCase t;
        t.k = 8;
        int n = 32;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i - 16) * (i % 4 == 0 ? -1 : 1);
        for (int q = 0; q < 20; ++q) {
            int i = (q * 9) % n;
            int v = (q * 33 - 500);
            int s = n - 1; // always querying the last element segment
            int x = q % (t.k + 2);
            t.queries.push_back({i, v, s, x});
        }
        tests.push_back(move(t));
    }

    // Test 10: mixed random-like, k=12
    {
        TestCase t;
        t.k = 12;
        int n = 75;
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i * 12345 + 6789) % 100000 - 50000;
        for (int q = 0; q < 40; ++q) {
            int i = (q * 17 + 3) % n;
            int v = (q % 2 == 0 ? q * 1000 - 123 : -q * 100 + 321);
            int s = (q * 7) % n;
            int x = (q * 11) % (t.k + 5);
            t.queries.push_back({i, v, s, x});
        }
        tests.push_back(move(t));
    }

    return tests;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests = buildTests();
    Solution solver;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long long checksum = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<int> res = solver.resultArray(const_cast<vector<int>&>(tc.nums), const_cast<int&>(tc.k), const_cast<vector<vector<int>>&>(tc.queries));
            for (int v : res) checksum += v;
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (microseconds): " << elapsed_us << "\n";

    return 0;
}