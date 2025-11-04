#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int rowsMoves = analyzeRows(board);
        if (rowsMoves < 0) return -1;
        int colsMoves = analyzeCols(board);
        if (colsMoves < 0) return -1;
        return rowsMoves + colsMoves;
    }

private:
    int computeMovesForPattern(const vector<int>& seq) {
        int N = static_cast<int>(seq.size());
        int ones = 0;
        for (int v : seq) ones += v;

        if (N % 2 == 1) {
            int begin = (ones * 2 > N) ? 1 : 0;
            int mismatch = 0;
            for (int i = 0; i < N; ++i) {
                int expected = (i + begin) % 2;
                if (seq[i] != expected) mismatch++;
            }
            return mismatch / 2;
        } else {
            int mismatch0 = 0, mismatch1 = 0;
            for (int i = 0; i < N; ++i) {
                if (seq[i] != (i % 2)) mismatch0++;
                if (seq[i] != ((i + 1) % 2)) mismatch1++;
            }
            return min(mismatch0, mismatch1) / 2;
        }
    }

    int analyzeRows(const vector<vector<int>>& board) {
        int N = static_cast<int>(board.size());
        const vector<int>& s1 = board[0];
        vector<int> s2(N);
        for (int j = 0; j < N; ++j) s2[j] = 1 - s1[j];

        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < N; ++i) {
            if (board[i] == s1) {
                cnt1++;
            } else if (board[i] == s2) {
                cnt2++;
            } else {
                return -1;
            }
        }

        int a = min(cnt1, cnt2);
        int b = max(cnt1, cnt2);
        if (!(a == N / 2 && b == (N + 1) / 2)) return -1;

        return computeMovesForPattern(s1);
    }

    int analyzeCols(const vector<vector<int>>& board) {
        int N = static_cast<int>(board.size());
        vector<int> s1(N);
        for (int i = 0; i < N; ++i) s1[i] = board[i][0];

        int cnt1 = 0, cnt2 = 0;
        for (int j = 0; j < N; ++j) {
            bool eq1 = true, eq2 = true;
            for (int i = 0; i < N; ++i) {
                if (board[i][j] != s1[i]) eq1 = false;
                if (board[i][j] != 1 - s1[i]) eq2 = false;
                if (!eq1 && !eq2) break;
            }
            if (eq1) {
                cnt1++;
            } else if (eq2) {
                cnt2++;
            } else {
                return -1;
            }
        }

        int a = min(cnt1, cnt2);
        int b = max(cnt1, cnt2);
        if (!(a == N / 2 && b == (N + 1) / 2)) return -1;

        return computeMovesForPattern(s1);
    }
};

static vector<vector<int>> makeBoardFromRC(const vector<int>& r, const vector<int>& c) {
    int N = static_cast<int>(r.size());
    vector<vector<int>> b(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            b[i][j] = r[i] ^ c[j];
        }
    }
    return b;
}

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