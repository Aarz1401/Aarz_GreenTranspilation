#include <iostream>
#include <algorithm>
#include <limits>
#include <memory>
#include <vector>
#include <initializer_list>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

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

int main() {
    // Build 10 diverse, valid test trees
    TreeNode* t1 = new TreeNode(42);

    TreeNode* t2 = new TreeNode(1);
    t2->left = new TreeNode(2);

    TreeNode* t3 = new TreeNode(-10);
    t3->left = new TreeNode(9);
    t3->right = new TreeNode(20);
    t3->right->left = new TreeNode(15);
    t3->right->right = new TreeNode(7);

    TreeNode* t4 = new TreeNode(-3);
    t4->left = new TreeNode(-2);
    t4->right = new TreeNode(-4);

    TreeNode* t5 = new TreeNode(1);
    t5->left = new TreeNode(2);
    t5->left->left = new TreeNode(3);
    t5->left->left->left = new TreeNode(4);
    t5->left->left->left->left = new TreeNode(5);

    TreeNode* t6 = new TreeNode(-1);
    t6->right = new TreeNode(2);
    t6->right->right = new TreeNode(3);
    t6->right->right->right = new TreeNode(-4);
    t6->right->right->right->right = new TreeNode(5);

    TreeNode* t7 = new TreeNode(5);
    t7->left = new TreeNode(4);
    t7->right = new TreeNode(8);
    t7->left->left = new TreeNode(11);
    t7->left->left->left = new TreeNode(7);
    t7->left->left->right = new TreeNode(2);
    t7->right->left = new TreeNode(13);
    t7->right->right = new TreeNode(4);
    t7->right->right->right = new TreeNode(1);

    TreeNode* t8 = new TreeNode(0);
    t8->left = new TreeNode(-3);
    t8->right = new TreeNode(0);
    t8->right->left = new TreeNode(0);
    t8->right->right = new TreeNode(-2);

    TreeNode* t9 = new TreeNode(1);
    t9->left = new TreeNode(2);
    t9->right = new TreeNode(3);
    t9->left->left = new TreeNode(4);
    t9->left->right = new TreeNode(5);
    t9->right->left = new TreeNode(6);
    t9->right->right = new TreeNode(7);

    TreeNode* t10 = new TreeNode(10);
    t10->left = new TreeNode(-2);
    t10->right = new TreeNode(7);
    t10->left->left = new TreeNode(8);
    t10->left->right = new TreeNode(-4);
    t10->right->left = new TreeNode(-1);
    t10->right->right = new TreeNode(3);

    vector<TreeNode*> tests = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10};

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (TreeNode* root : tests) {
            checksum += sol.maxPathSum(root);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}