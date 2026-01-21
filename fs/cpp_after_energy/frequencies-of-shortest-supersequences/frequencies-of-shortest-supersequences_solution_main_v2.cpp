int main() {
    vector<vector<string>> tests = {
        {"ab","bc","cd"},
        {"ab","cd"},
        {"ab","ac","bd","cd"},
        {"ab","ac","bd"},
        {"az"},
        {"ab","ac","ad","ae","af"},
        {"ab","bc","bd","de","cf"},
        {"ab","bc","de","ef","gh"},
        {"ab","bc","ce","ad","df"},
        {"ab","bc","cd","de","ef","fg","gh"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            auto res = sol.supersequences(tests[i]);
            checksum += static_cast<int>(res.size());
            for (const auto& v : res) {
                for (int x : v) checksum += x;
            }
        }
        sink = checksum;
    }

    return 0;
}