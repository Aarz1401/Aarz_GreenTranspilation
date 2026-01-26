#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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

static void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

volatile int sink = 0;

int main() {
    vector<string> tests = {
        "1 # # ",
        "2 1 # # 3 # # ",
        "4 3 2 1 # # # # # ",
        "1 # 2 # 3 # 4 # # ",
        "1 2 4 # # 5 # # 3 6 # # 7 # # ",
        "-10 -20 -30 # # -5 # # 15 0 # # 22 # # ",
        "1 1 1 # # # 1 1 # # 1 # # ",
        "8 4 2 1 # # 3 # # 6 5 # # 7 # # 12 10 9 # # 11 # # 14 13 # # 15 # # ",
        "5 2 # 3 # # 9 # 10 8 # # # ",
        "1 # 2 3 # 4 5 # # # # "
    };

    Codec codec;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& s : tests) {
            TreeNode* root = codec.deserialize(s);
            string s2 = codec.serialize(root);
            //checksum += static_cast<int>(s2.size());
            DoNotOptimize(s2);
            freeTree(root);
        }
        //sink = checksum;
    }

    return 0;
}