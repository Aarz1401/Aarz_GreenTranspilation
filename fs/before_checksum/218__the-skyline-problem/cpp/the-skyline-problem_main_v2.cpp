int main() {
    std::vector<std::vector<std::vector<int>>> tests = {
        {{2, 9, 10}},
        {{1, 2, 1}, {3, 4, 2}},
        {{2, 6, 4}, {4, 8, 6}},
        {{1, 3, 4}, {3, 5, 4}, {5, 8, 4}},
        {{1, 4, 5}, {2, 6, 7}, {5, 8, 6}, {7, 9, 4}, {3, 5, 8}},
        {{1, 2, 1}, {2, 3, 2}, {3, 4, 3}, {4, 5, 4}, {5, 6, 5}},
        {{1, 10, 5}, {1, 7, 9}, {1, 3, 8}, {1, 5, 3}},
        {{50, 120, 5}, {100, 200, 10}, {150, 250, 20}, {240, 300, 15}, {310, 320, 10}},
        {{1, 2, 3}, {2, 4, 3}, {3, 5, 2}, {4, 6, 4}, {5, 7, 3}, {6, 8, 5}},
        {{1, 2, 1}, {10, 12, 2}, {20, 25, 3}, {30, 40, 1}}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& buildings : tests) {
            auto res = sol.getSkyline(buildings);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}