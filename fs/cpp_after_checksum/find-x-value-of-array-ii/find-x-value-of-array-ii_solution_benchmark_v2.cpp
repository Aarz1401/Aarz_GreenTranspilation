#include <iostream>
#include <vector>
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
    vector<TestCase> tests;

    // Test 1
    tests.push_back({
        {5},
        1,
        {{0, 7, 0, 1}}
    });

    // Test 2
    tests.push_back({
        {1, 2, 3},
        2,
        {
            {1, 5, 0, 0},
            {0, -3, 1, 1},
            {2, 4, 2, 2}
        }
    });

    // Test 3
    tests.push_back({
        {-5, 7, 0, 12, -3},
        3,
        {
            {3, -2, 0, 0},
            {1, 9, 2, 1},
            {4, 6, 1, 2},
            {0, -7, 4, 3}
        }
    });

    // Test 4
    tests.push_back({
        {2, 4, 6, 8},
        4,
        {
            {2, 5, 0, 0},
            {3, -1, 1, 1},
            {0, 7, 2, 2},
            {1, 3, 3, 4}
        }
    });

    // Test 5
    tests.push_back({
        {1, 1, 1, 1, 1, 1},
        5,
        {
            {5, 2, 0, 0},
            {4, 3, 1, 1},
            {3, 4, 2, 2},
            {2, 5, 3, 3},
            {1, 6, 4, 4},
            {0, 7, 5, 5}
        }
    });

    // Test 6
    tests.push_back({
        {-10, 3, -7, 9, 0, 2, 5},
        7,
        {
            {6, -2, 0, 0},
            {5, 14, 1, 3},
            {4, -21, 2, 5},
            {3, 7, 3, 7},
            {2, 8, 4, 2}
        }
    });

    // Test 7
    tests.push_back({
        {1000000, -1000000},
        8,
        {
            {1, 123456, 0, 0},
            {0, -654321, 1, 4},
            {1, 1, 1, 8}
        }
    });

    // Test 8
    tests.push_back({
        {1,2,3,4,5,6,7,8},
        10,
        {
            {7, 9, 0, 0},
            {6, -5, 2, 5},
            {5, 11, 4, 7},
            {4, -13, 6, 9},
            {3, 17, 7, 10},
            {2, 19, 5, 3}
        }
    });

    // Test 9
    tests.push_back({
        {0,1,2,3,4,5,6,7,8,9},
        9,
        {
            {9, -1, 0, 0},
            {8, -2, 1, 1},
            {7, -3, 2, 2},
            {6, -4, 3, 3},
            {5, -5, 4, 4},
            {4, -6, 5, 5},
            {3, -7, 6, 6},
            {2, -8, 7, 7},
            {1, -9, 8, 8},
            {0, -10, 9, 9}
        }
    });

    // Test 10
    tests.push_back({
        {9, -4, 6},
        6,
        {
            {2, 1000000007, 0, 0},
            {1, -1000000007, 1, 3},
            {0, 123456789, 2, 6}
        }
    });

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t t = 0; t < tests.size(); ++t) {
            Solution sol;
            vector<int> nums = tests[t].nums;
            int k = tests[t].k;
            vector<vector<int>> queries = tests[t].queries;
            vector<int> out = sol.resultArray(nums, k, queries);
            for (int v : out) checksum += v;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}