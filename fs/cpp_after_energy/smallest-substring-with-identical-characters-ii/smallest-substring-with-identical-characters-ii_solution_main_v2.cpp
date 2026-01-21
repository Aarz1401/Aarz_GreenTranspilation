int main() {
    vector<pair<string, int>> tests = {
        {"0", 0},
        {"1", 0},
        {"00000", 0},
        {"010101", 0},
        {"11110000", 2},
        {"00110011", 1},
        {"101010001110", 3},
        {"000111000111000", 5},
        {"0100111001011", 4},
        {"0010010110110001110100011101100010110010100110", 7}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.minLength(t.first, t.second);
        }
        sink = checksum;
    }

    return 0;
}