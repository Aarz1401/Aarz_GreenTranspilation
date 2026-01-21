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
    const int iterations = 1000;
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