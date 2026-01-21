int main() {
    // Prepare 10 diverse test inputs
    vector<vector<vector<char>>> testCases;
    testCases.reserve(10);

    // 1) Empty matrix
    testCases.push_back(vector<vector<char>>{});

    // 2) Matrix with zero columns
    testCases.push_back(makeMatrix({"", "", ""}));

    // 3) Single cell '0'
    testCases.push_back(makeMatrix({"0"}));

    // 4) Single cell '1'
    testCases.push_back(makeMatrix({"1"}));

    // 5) Single row mixed
    testCases.push_back(makeMatrix({"1011010011001110"}));

    // 6) Single column mixed
    testCases.push_back(makeMatrix({"1","0","1","1","1","1","0","1"}));

    // 7) All zeros 5x5
    testCases.push_back(makeMatrix({"00000","00000","00000","00000","00000"}));

    // 8) All ones 5x7
    testCases.push_back(makeMatrix({"1111111","1111111","1111111","1111111","1111111"}));

    // 9) Checkerboard 6x6 starting with '1'
    {
        vector<string> lines(6, string(6, '0'));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                lines[i][j] = ((i + j) % 2 == 0) ? '1' : '0';
            }
        }
        testCases.push_back(makeMatrix(lines));
    }

    // 10) Mixed example
    testCases.push_back(makeMatrix({"10100","10111","11111","10010"}));

    Solution sol;
    long long checksum = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < testCases.size(); ++i) {
            checksum += sol.maximalRectangle(testCases[i]);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}