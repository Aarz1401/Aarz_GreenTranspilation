int main() {
    vector<pair<vector<vector<int>>, int>> tests = {
        { { {0} }, 0 },
        { { {1, 2}, {3, 4} }, 0 },
        { { {1, 100, 1}, {1, 100, 1}, {1, 1, 1} }, 1 },
        { { {5, 1, 3, 2}, {4, 2, 1, 9}, {8, 1, 1, 1} }, 2 },
        { { {7, 7, 7}, {7, 5, 7}, {7, 7, 7}, {1, 1, 1} }, 3 },
        { { {1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, {4, 5, 6, 7, 1}, {5, 6, 7, 1, 2} }, 5 },
        { { {9, 8, 7, 6, 5}, {1, 2, 3, 4, 5} }, 10 },
        { { {0, 2, 1, 0, 3, 1}, {4, 0, 2, 1, 0, 2}, {1, 3, 0, 2, 2, 0}, {2, 1, 2, 0, 1, 3}, {0, 2, 1, 3, 0, 1}, {1, 0, 2, 1, 2, 0} }, 0 },
        { { {3, 1, 4, 1, 5} }, 2 },
        { { {2}, {7}, {1}, {8}, {2} }, 2 }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            checksum += sol.minCost(tc.first, tc.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}