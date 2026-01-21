#include <bits/stdc++.h>
using namespace std;
#include <chrono>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <string>
#include <sstream>

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
// Space: O(h)
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserializeHelper(in);
    }

private:
    void serializeHelper(TreeNode* node, ostringstream& out) {
        if (!node) {
            out << "# ";
            return;
        }
        out << node->val << ' ';
        serializeHelper(node->left, out);
        serializeHelper(node->right, out);
    }

    TreeNode* deserializeHelper(istringstream& in) {
        string val;
        if (!(in >> val)) return nullptr;
        if (val == "#") return nullptr;
        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserializeHelper(in);
        node->right = deserializeHelper(in);
        return node;
    }
};

// Time: O(n)
// Space: O(n)
class Codec2 {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        genPreorder(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return build(in);
    }

private:
    void genPreorder(TreeNode* node, ostringstream& out) {
        if (!node) {
            out << "# ";
            return;
        }
        out << node->val << ' ';
        genPreorder(node->left, out);
        genPreorder(node->right, out);
    }

    TreeNode* build(istringstream& in) {
        string val;
        if (!(in >> val)) return nullptr;
        if (val == "#") return nullptr;
        TreeNode* node = new TreeNode(stoi(val));
        node->left = build(in);
        node->right = build(in);
        return node;
    }
};

// Helper to delete a tree and free memory
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Test tree builders
TreeNode* makeSkewLeft(int n, int startVal = 1) {
    TreeNode* root = nullptr;
    for (int i = 0; i < n; ++i) {
        root = new TreeNode(startVal + i, root, nullptr);
    }
    return root;
}

TreeNode* makeSkewRight(int n, int startVal = 1) {
    TreeNode* root = nullptr;
    TreeNode* cur = nullptr;
    for (int i = 0; i < n; ++i) {
        if (!root) {
            root = new TreeNode(startVal + i);
            cur = root;
        } else {
            cur->right = new TreeNode(startVal + i);
            cur = cur->right;
        }
    }
    return root;
}

TreeNode* makeFullBalanced7() {
    // Values 1..7 in a balanced configuration
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n7 = new TreeNode(7);
    n2->left = n1; n2->right = n3;
    n6->left = n5; n6->right = n7;
    n4->left = n2; n4->right = n6;
    return n4;
}

vector<TreeNode*> buildTestTrees() {
    vector<TreeNode*> tests;
    tests.reserve(10);

    // 1) Empty tree
    tests.push_back(nullptr);

    // 2) Single node
    tests.push_back(new TreeNode(42));

    // 3) Skewed left, 5 nodes
    tests.push_back(makeSkewLeft(5, 10));

    // 4) Skewed right, 5 nodes
    tests.push_back(makeSkewRight(5, 100));

    // 5) Full balanced 7 nodes
    tests.push_back(makeFullBalanced7());

    // 6) Sparse irregular
    {
        TreeNode* root = new TreeNode(10);
        root->left = new TreeNode(20);
        root->left->right = new TreeNode(30);
        root->right = new TreeNode(40);
        root->right->right = new TreeNode(50);
        root->right->right->left = new TreeNode(60);
        tests.push_back(root);
    }

    // 7) Negative values
    {
        TreeNode* root = new TreeNode(-1);
        root->left = new TreeNode(-2);
        root->right = new TreeNode(-3);
        root->left->left = new TreeNode(-4);
        root->right->right = new TreeNode(-5);
        tests.push_back(root);
    }

    // 8) Large values
    {
        TreeNode* root = new TreeNode(2000000000);
        root->left = new TreeNode(1500000000);
        root->right = new TreeNode(1999999999);
        root->left->left = new TreeNode(123456789);
        root->left->right = new TreeNode(987654321);
        tests.push_back(root);
    }

    // 9) Duplicates
    {
        TreeNode* root = new TreeNode(7);
        root->left = new TreeNode(7);
        root->right = new TreeNode(7);
        root->left->left = new TreeNode(7);
        root->left->right = new TreeNode(7);
        root->right->left = new TreeNode(7);
        root->right->right = new TreeNode(7);
        tests.push_back(root);
    }

    // 10) Mixed complex shape
    {
        TreeNode* root = new TreeNode(0);
        root->left = new TreeNode(-10);
        root->right = new TreeNode(10);
        root->left->left = new TreeNode(-20);
        root->left->right = new TreeNode(-5);
        root->right->left = new TreeNode(5);
        root->right->right = new TreeNode(20);
        root->left->right->left = new TreeNode(-6);
        root->right->left->right = new TreeNode(6);
        tests.push_back(root);
    }

    return tests;
}

int main() {
    // Build test inputs
    vector<TreeNode*> tests = buildTestTrees();

    // Instances of the provided classes (unmodified)
    Codec codec;
    Codec2 codec2;

    // Accumulator to prevent optimization
    unsigned long long checksum = 0;

    // Timing
    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run serialize/deserialize for each test input
        for (TreeNode* t : tests) {
            // Codec
            string s1 = codec.serialize(t);
            TreeNode* d1 = codec.deserialize(s1);
            checksum += s1.size();
            checksum += (d1 ? static_cast<unsigned long long>(d1->val) : 0ULL);

            // Codec2
            string s2 = codec2.serialize(t);
            TreeNode* d2 = codec2.deserialize(s2);
            checksum += s2.size();
            checksum += (d2 ? static_cast<unsigned long long>(d2->val) : 0ULL);

            // Clean up deserialized trees
            deleteTree(d1);
            deleteTree(d2);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // Clean up original test trees
    for (TreeNode* t : tests) deleteTree(t);

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}