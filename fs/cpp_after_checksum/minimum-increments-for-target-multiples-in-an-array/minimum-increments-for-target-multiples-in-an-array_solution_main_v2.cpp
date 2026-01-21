int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        { {2}, {2} },
        { {1,3}, {2,3} },
        { {4,9}, {2,3,4} },
        { {5,6}, {4,9} },
        { {10,14,20}, {7} },
        { {1,2}, {2,2,3} },
        { {8,9,10}, {2,5,3} },
        { {6,10,15,30}, {2,3,5} },
        { {2147483647, 2147483629}, {2147483647, 2147483629} },
        { {1,2,3,4,5}, {2,3,4,5,6,7,8,9} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;

        for (auto& t : tests) {
            checksum += sol.minimumIncrements(t.first, t.second);
        }

        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}