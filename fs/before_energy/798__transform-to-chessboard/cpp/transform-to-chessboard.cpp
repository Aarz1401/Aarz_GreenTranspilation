#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>

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