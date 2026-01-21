int main() {
    vector<pair<string, int>> tests = {
        {"a", 1},
        {"aaab", 3},
        {"abc", 3},
        {"aabbcc", 5},
        {"ababab", 4},
        {"zzzzzzzzzz", 7},
        {"mississippi", 10},
        {"qwertyuiopasdfghjkl", 20},
        {"aaaabbbbccccddddeeee", 2},
        {"b", 100}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum ^= sol.possibleStringCount(tc.first, tc.second);
        }
        sink = checksum;
    }

    return 0;
}