int main() {
    vector<vector<vector<int>>> tests;

    // 1) 1x1 valid (0 moves)
    tests.push_back({{0}});

    // 2) 2x2 valid chessboard (0 moves)
    tests.push_back(makeBoardFromRC({0,1}, {0,1}));

    // 3) 2x2 valid chessboard starting with 1 (0 moves)
    tests.push_back(makeBoardFromRC({1,0}, {1,0}));

    // 4) 2x2 invalid board (should be -1)
    tests.push_back({{1,1},{0,0}});

    // 5) 3x3 valid with 1 move
    tests.push_back(makeBoardFromRC({0,1,1}, {1,0,1}));

    // 6) 3x3 invalid (row not matching pattern)
    tests.push_back({{0,1,0},{1,1,1},{0,1,0}});

    // 7) 4x4 valid with 2 moves
    tests.push_back(makeBoardFromRC({0,0,1,1}, {0,0,1,1}));

    // 8) 4x4 invalid due to row counts mismatch
    tests.push_back(makeBoardFromRC({0,0,0,1}, {0,1,0,1}));

    // 9) 5x5 valid with 2 moves
    tests.push_back(makeBoardFromRC({0,0,1,1,1}, {1,1,0,0,1}));

    // 10) 6x6 valid with 2 moves
    tests.push_back(makeBoardFromRC({1,1,0,0,1,0}, {0,1,1,0,0,1}));

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& board : tests) {
            int res = sol.movesToChessboard(board);
            checksum += res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}