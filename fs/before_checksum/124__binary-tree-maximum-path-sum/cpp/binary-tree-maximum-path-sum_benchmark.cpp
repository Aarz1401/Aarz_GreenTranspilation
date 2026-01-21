#include <algorithm>
#include <climits>
#include <cstdint>
#include <limits>
#include <memory>
#include <utility>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left_, TreeNode *right_) : val(x), left(left_), right(right_) {}
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

static void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    // Build 10 diverse test trees
    vector<TreeNode*> tests;
    tests.reserve(10);

    // 1) Single node
    {
        TreeNode* r = new TreeNode(5);
        tests.push_back(r);
    }

    // 2) Small balanced positive
    {
        TreeNode* r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->right = new TreeNode(3);
        tests.push_back(r);
    }

    // 3) Classic mixed with negatives
    {
        TreeNode* r = new TreeNode(-10);
        r->left = new TreeNode(9);
        r->right = new TreeNode(20);
        r->right->left = new TreeNode(15);
        r->right->right = new TreeNode(7);
        tests.push_back(r);
    }

    // 4) All negatives
    {
        TreeNode* r = new TreeNode(-3);
        r->left = new TreeNode(-2);
        r->right = new TreeNode(-1);
        r->left->left = new TreeNode(-4);
        r->left->right = new TreeNode(-5);
        tests.push_back(r);
    }

    // 5) Left-skewed increasing
    {
        TreeNode* r = new TreeNode(5);
        r->left = new TreeNode(4);
        r->left->left = new TreeNode(3);
        r->left->left->left = new TreeNode(2);
        r->left->left->left->left = new TreeNode(1);
        tests.push_back(r);
    }

    // 6) Right-skewed negatives
    {
        TreeNode* r = new TreeNode(-1);
        r->right = new TreeNode(-2);
        r->right->right = new TreeNode(-3);
        r->right->right->right = new TreeNode(-4);
        r->right->right->right->right = new TreeNode(-5);
        tests.push_back(r);
    }

    // 7) Mixed with zeros
    {
        TreeNode* r = new TreeNode(0);
        r->left = new TreeNode(1);
        r->right = new TreeNode(-1);
        r->left->left = new TreeNode(2);
        r->left->right = new TreeNode(-2);
        r->right->left = new TreeNode(3);
        r->right->right = new TreeNode(-3);
        tests.push_back(r);
    }

    // 8) Larger positives forming a long cross-root path
    {
        TreeNode* r = new TreeNode(10);
        r->left = new TreeNode(2);
        r->right = new TreeNode(10);
        r->right->left = new TreeNode(20);
        r->right->right = new TreeNode(1);
        tests.push_back(r);
    }

    // 9) Full tree depth ~3 with multiple branches
    {
        TreeNode* r = new TreeNode(5);
        r->left = new TreeNode(4);
        r->right = new TreeNode(8);
        r->left->left = new TreeNode(11);
        r->left->left->left = new TreeNode(7);
        r->left->left->right = new TreeNode(2);
        r->right->left = new TreeNode(13);
        r->right->right = new TreeNode(4);
        r->right->right->left = new TreeNode(5);
        r->right->right->right = new TreeNode(1);
        tests.push_back(r);
    }

    // 10) Mixed positives and negatives with both subtrees
    {
        TreeNode* r = new TreeNode(2);
        r->left = new TreeNode(-1);
        r->right = new TreeNode(-2);
        r->left->left = new TreeNode(3);
        r->left->right = new TreeNode(4);
        r->right->left = new TreeNode(-5);
        r->right->right = new TreeNode(1);
        tests.push_back(r);
    }

    Solution solver;

    volatile long long checksum = 0; // volatile to prevent optimization
    const int iterations = 1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (TreeNode* root : tests) {
            checksum += solver.maxPathSum(root);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    for (TreeNode* r : tests) {
        freeTree(r);
    }
    return 0;
}