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

int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    // 1) Minimal array, k=1, zero update/query
    tests.push_back(TestCase{
        {0}, 1, {{0, 0, 0, 0}}
    });

    // 2) Small array, negative update, k=2
    tests.push_back(TestCase{
        {1, 2}, 2, {{1, -3, 0, 1}}
    });

    // 3) Negative numbers, k=3
    tests.push_back(TestCase{
        {-1, -2, -3}, 3, {{0, 4, 1, 0}}
    });

    // 4) All same numbers, product index (x == k), k=2
    tests.push_back(TestCase{
        {5, 5, 5}, 2, {{2, 6, 2, 2}}
    });

    // 5) Single element, product index retrieval (x == k), k=5
    tests.push_back(TestCase{
        {7}, 5, {{0, 7, 0, 5}}
    });

    // 6) Large magnitude values, invalid x (>k), k=3
    tests.push_back(TestCase{
        {-1000000000, 1000000000}, 3, {{0, -1000000000, 1, 10}}
    });

    // 7) Patterned array, invalid x (negative), k=2
    tests.push_back(TestCase{
        {1, 0, 1, 0}, 2, {{3, 1, 0, -1}}
    });

    // 8) Extremes INT_MAX/INT_MIN, k=7
    tests.push_back(TestCase{
        {INT_MAX, INT_MIN}, 7, {{1, INT_MAX - 1, 1, 3}}
    });

    // 9) Out-of-range start s > n-1, and product index (x == k), k=4
    tests.push_back(TestCase{
        {2, 2}, 4, {{0, 2, 5, 4}}
    });

    // 10) Medium small array, valid tail query, k=3
    tests.push_back(TestCase{
        {1, 2, 3, 4}, 3, {{2, 5, 3, 1}}
    });

    Solution sol;

    volatile long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            vector<int> out = sol.resultArray(tc.nums, tc.k, tc.queries);
            checksum += (long long)out.size();
            for (int v : out) checksum += v;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed ms: " << elapsed_ms << "\n";

    return 0;
}