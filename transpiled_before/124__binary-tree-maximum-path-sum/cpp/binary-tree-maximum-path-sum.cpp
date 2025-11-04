#include <algorithm>
#include <climits>
#include <cstdint>
#include <limits>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Time:  O(n)
// Space: O(h), h is height of binary tree
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return static_cast<int>(iter_dfs(root));
    }

private:
    struct Frame {
        int step;
        TreeNode* node;
        shared_ptr<long long> ret;
        shared_ptr<long long> ret1;
        shared_ptr<long long> ret2;
    };

    long long iter_dfs(TreeNode* node) {
        long long result = numeric_limits<long long>::lowest();
        auto max_sum = make_shared<long long>(0);
        vector<Frame> stk;
        stk.push_back(Frame{1, node, max_sum, nullptr, nullptr});
        while (!stk.empty()) {
            Frame f = stk.back();
            stk.pop_back();
            if (f.step == 1) {
                TreeNode* cur = f.node;
                if (!cur) {
                    continue;
                }
                auto ret1 = make_shared<long long>(0);
                auto ret2 = make_shared<long long>(0);
                stk.push_back(Frame{2, cur, f.ret, ret1, ret2});
                stk.push_back(Frame{1, cur->right, ret2, nullptr, nullptr});
                stk.push_back(Frame{1, cur->left, ret1, nullptr, nullptr});
            } else { // step == 2
                TreeNode* cur = f.node;
                long long left_gain = max(*f.ret1, 0LL);
                long long right_gain = max(*f.ret2, 0LL);
                result = max(result, static_cast<long long>(cur->val) + left_gain + right_gain);
                *f.ret = static_cast<long long>(cur->val) + max({*f.ret1, *f.ret2, 0LL});
            }
        }
        return result;
    }
};


// Time:  O(n)
// Space: O(h), h is height of binary tree
class Solution2 {
public:
    int maxPathSum(TreeNode* root) {
        return static_cast<int>(dfs(root).first);
    }

private:
    pair<long long, long long> dfs(TreeNode* node) {
        if (!node) {
            return {numeric_limits<long long>::lowest(), 0LL};
        }
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        long long through = static_cast<long long>(node->val) + max(left.second, 0LL) + max(right.second, 0LL);
        long long up = static_cast<long long>(node->val) + max({left.second, right.second, 0LL});
        long long best = max({left.first, right.first, through});
        return {best, up};
    }
};