int main() {
    vector<vector<vector<int>>> tests = {
        { {1, 1} },
        { {1, 2}, {3, 2} },
        { {1, 2}, {2, 2} },
        { {100, 5}, {100, 3}, {100, 4} },
        { {6, 1}, {2, 4}, {7, 2}, {3, 3} },
        { {1, 2}, {5, 3}, {2, 2}, {6, 1}, {4, 2} },
        { {100000000, 1}, {99999999, 2}, {100000001, 1} },
        { {10, 10}, {10, 10}, {10, 10} },
        { {1, 3}, {4, 1}, {2, 2}, {5, 2}, {3, 1} },
        { {2, 1}, {5, 2}, {1, 2}, {4, 3}, {6, 1}, {3, 2}, {7, 2} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            vector<int> res = sol.fallingSquares(t);
            for (int v : res) checksum += v;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}