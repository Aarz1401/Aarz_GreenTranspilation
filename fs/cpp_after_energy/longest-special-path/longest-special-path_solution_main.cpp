int main() {
    // Define 10 diverse test inputs (trees with weighted edges)
    vector<vector<vector<int>>> edgesList;
    vector<vector<int>> numsList;

    // 1) Single node
    edgesList.push_back({});
    numsList.push_back({1});

    // 2) Chain of 5 with increasing nums
    edgesList.push_back({{0,1,1},{1,2,2},{2,3,3},{3,4,4}});
    numsList.push_back({1,2,3,4,5});

    // 3) Star with center 0
    edgesList.push_back({{0,1,5},{0,2,6},{0,3,7},{0,4,8},{0,5,9},{0,6,10}});
    numsList.push_back({10,9,8,7,8,9,10});

    // 4) Balanced binary tree of 7
    edgesList.push_back({{0,1,3},{0,2,5},{1,3,2},{1,4,7},{2,5,1},{2,6,4}});
    numsList.push_back({5,4,6,3,5,7,8});

    // 5) Random tree of 10
    edgesList.push_back({{0,1,2},{0,2,3},{1,3,4},{1,4,5},{2,5,6},{2,6,7},{3,7,2},{4,8,1},{6,9,9}});
    numsList.push_back({100,99,101,98,99,102,103,97,100,104});

    // 6) Chain with all equal nums
    edgesList.push_back({{0,1,1},{1,2,1},{2,3,1},{3,4,1},{4,5,1}});
    numsList.push_back({5,5,5,5,5,5});

    // 7) Strictly decreasing nums on a chain
    edgesList.push_back({{0,1,5},{1,2,4},{2,3,3},{3,4,2},{4,5,1}});
    numsList.push_back({6,5,4,3,2,1});

    // 8) Star with large weights
    edgesList.push_back({{0,1,1000000000},{0,2,900000000},{0,3,800000000},{0,4,700000000}});
    numsList.push_back({1,2,1,2,3});

    // 9) Two nodes with far-apart nums
    edgesList.push_back({{0,1,42}});
    numsList.push_back({1000000,-1000000000});

    // 10) Mixed negative nums
    edgesList.push_back({{0,1,7},{0,2,1},{2,3,2}});
    numsList.push_back({-5,-6,-5,-4});

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < edgesList.size(); ++i) {
            vector<vector<int>> edges = edgesList[i];
            vector<int> nums = numsList[i];
            vector<int> res = sol.longestSpecialPath(edges, nums);
            checksum += (static_cast<long long>(res[0]) * 1000003LL + res[1]) ^ static_cast<long long>(iter + i);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time: " << elapsed_us << " microseconds\n";

    return 0;
}