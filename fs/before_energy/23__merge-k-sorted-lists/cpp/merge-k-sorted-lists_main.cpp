int main() {
    // Prepare 10 diverse test inputs (as vectors of sorted integer lists)
    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1. No lists
    tests.emplace_back(vector<vector<int>>{});
    // 2. Single empty list
    tests.emplace_back(vector<vector<int>>{{}});
    // 3. Multiple empty lists
    tests.emplace_back(vector<vector<int>>{{}, {}, {}});
    // 4. Single sorted list
    tests.emplace_back(vector<vector<int>>{{1, 2, 3, 4}});
    // 5. Mixed positive lists (classic sample)
    tests.emplace_back(vector<vector<int>>{{1, 4, 5}, {1, 3, 4}, {2, 6}});
    // 6. Negative and positive numbers
    tests.emplace_back(vector<vector<int>>{{-10, -5, 0}, {-6, -3, 2, 9}, {-7, -3, 0, 1}});
    // 7. Varying lengths and empties
    tests.emplace_back(vector<vector<int>>{{5}, {}, {1,2,3,4,5,6,7,8,9,10}, {2,2,2,2,2}, {1000}});
    // 8. Heavy duplicates
    tests.emplace_back(vector<vector<int>>{{1,1,1,1}, {1,1,1}, {1,1}, {1}});
    // 9. Many small single-node lists
    tests.emplace_back(vector<vector<int>>{{0},{-1},{-2},{-3},{-4},{-5},{-6},{-7},{-8},{-9}});
    // 10. Larger case: 5 lists of 100 elements each
    {
        vector<vector<int>> big(5);
        for (int j = 0; j < 5; ++j) {
            big[j].reserve(100);
            for (int i = 0; i < 100; ++i) {
                big[j].push_back(j * 1000 + i * 3 - j); // strictly increasing within each list
            }
        }
        tests.emplace_back(move(big));
    }

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            vector<ListNode*> lists = buildLists(tests[t]);
            ListNode* merged = sol.mergeKLists(lists);

            long long sum = 0;
            long long count = 0;
            for (ListNode* p = merged; p != nullptr; p = p->next) {
                sum += p->val;
                ++count;
            }
            // Mix in iteration and test index to avoid trivial optimization
            checksum += (sum ^ (count * 1315423911LL)) + static_cast<long long>(t * 17 + iter);

            freeList(merged);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}