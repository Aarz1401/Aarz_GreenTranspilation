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

    const int iterations = 1;
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