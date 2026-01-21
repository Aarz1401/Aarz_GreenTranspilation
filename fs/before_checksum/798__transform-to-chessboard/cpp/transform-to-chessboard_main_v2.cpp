int main() {
    auto makeChess = [](int N, int start) {
        vector<vector<int>> b(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                b[i][j] = (i + j + start) % 2;
        return b;
    };
    auto permuteCols = [](const vector<vector<int>>& b, const vector<int>& p) {
        int N = static_cast<int>(b.size());
        vector<vector<int>> r(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                r[i][j] = b[i][p[j]];
        return r;
    };
    auto permuteRows = [](const vector<vector<int>>& b, const vector<int>& p) {
        int N = static_cast<int>(b.size());
        vector<vector<int>> r(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            r[i] = b[p[i]];
        return r;
    };

    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1) 2x2 valid chessboard
    tests.push_back({{0,1},{1,0}});

    // 2) 2x2 invalid due to column counts mismatch
    tests.push_back({{1,1},{0,0}});

    // 3) 3x3 valid chessboard
    tests.push_back(makeChess(3, 0));

    // 4) 3x3 invalid row not matching s1/s2
    tests.push_back({{1,0,1},{0,1,0},{1,1,0}});

    // 5) 4x4 solvable needing swaps
    tests.push_back({{0,0,1,1},{1,1,0,0},{0,0,1,1},{1,1,0,0}});

    // 6) 5x5 valid chessboard starting with 1
    tests.push_back(makeChess(5, 1));

    // 7) 5x5 invalid due to row count imbalance
    tests.push_back({{1,0,1,0,1},{1,0,1,0,1},{1,0,1,0,1},{1,0,1,0,1},{1,0,1,0,1}});

    // 8) 6x6 solvable after permutations
    {
        auto b = makeChess(6, 0);
        vector<int> pc = {2,0,3,5,1,4};
        vector<int> pr = {3,0,5,2,1,4};
        tests.push_back(permuteRows(permuteCols(b, pc), pr));
    }

    // 9) 7x7 solvable after permutations
    {
        auto b = makeChess(7, 0);
        vector<int> pc = {1,0,3,2,5,4,6};
        vector<int> pr = {6,0,2,1,3,5,4};
        tests.push_back(permuteRows(permuteCols(b, pc), pr));
    }

    // 10) 8x8 solvable after permutations
    {
        auto b = makeChess(8, 1);
        vector<int> pc = {7,0,5,2,3,1,6,4};
        vector<int> pr = {4,2,7,0,6,1,5,3};
        tests.push_back(permuteRows(permuteCols(b, pc), pr));
    }

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            checksum += sol.movesToChessboard(tests[i]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}