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
