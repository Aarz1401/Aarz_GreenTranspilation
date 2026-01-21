int main() {
    vector<pair<int,int>> tests = {
        {1, 2},
        {1, 10},
        {2, 2},
        {2, 3},
        {2, 7},
        {3, 2},
        {3, 3},
        {3, 10},
        {4, 2},
        {4, 5}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            string res = s.crackSafe(tc.first, tc.second);
            checksum += static_cast<int>(res.size());
            checksum += static_cast<unsigned char>(res.front());
            checksum += static_cast<unsigned char>(res.back());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}