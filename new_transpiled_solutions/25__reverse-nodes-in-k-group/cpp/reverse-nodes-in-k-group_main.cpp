int main() {
    // Prepare 10 diverse test inputs (vectors) and corresponding k values
    std::vector<std::vector<int>> tests(10);
    tests[0] = {};                                        // empty list
    tests[1] = {1};                                       // single element, k=1
    tests[2] = {5};                                       // single element, k>len
    tests[3] = {1, 2};                                    // exact group
    tests[4] = {1, 2, 3};                                 // partial group
    tests[5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};           // ascending
    tests[6] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};           // descending
    tests[7] = {1, 1, 1, 1, 1, 1};                        // duplicates
    tests[8] = {0, -1, 2, -3, 4, -5, 6};                  // mixed negatives/positives
    tests[9].resize(100);                                 // larger test
    for (int i = 0; i < 100; ++i) {
        // mixed pattern including negatives and positives
        tests[9][i] = (i * 7 + ((i % 3 == 0) ? -i : i)) - 50;
    }

    int ks[10] = {3, 1, 2, 2, 2, 3, 4, 2, 3, 5};

    Solution sol;

    uint64_t total_checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int i = 0; i < 10; ++i) {
            ListNode* head = buildList(tests[i]);
            ListNode* res = sol.reverseKGroup(head, ks[i]);
            uint64_t h = checksumList(res);
            // Mix into total checksum to avoid easy cancellation
            total_checksum ^= h + 0x9e3779b97f4a7c15ULL + (total_checksum << 6) + (total_checksum >> 2);
            freeList(res);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << total_checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}