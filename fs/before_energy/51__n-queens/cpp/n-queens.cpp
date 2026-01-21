#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <functional>

// Time:  O(n^2 * n!)
// Space: O(n)

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result;
        std::vector<int> curr;
        std::vector<bool> cols(n, false), main_diag(2 * n - 1, false), anti_diag(2 * n - 1, false);

        std::function<void(int)> dfs = [&](int row) {
            if (row == n) {
                std::vector<std::string> board;
                board.reserve(n);
                for (int r = 0; r < n; ++r) {
                    std::string s(n, '.');
                    s[curr[r]] = 'Q';
                    board.push_back(std::move(s));
                }
                result.push_back(std::move(board));
                return;
            }
            for (int i = 0; i < n; ++i) {
                if (cols[i] || main_diag[row + i] || anti_diag[row - i + (n - 1)]) {
                    continue;
                }
                cols[i] = main_diag[row + i] = anti_diag[row - i + (n - 1)] = true;
                curr.push_back(i);
                dfs(row + 1);
                curr.pop_back();
                cols[i] = main_diag[row + i] = anti_diag[row - i + (n - 1)] = false;
            }
        };

        dfs(0);
        return result;
    }
};


// For any point (x,y), if we want the new point (p,q) don't share the same row, column, or diagonal.
// then there must have p+q != x+y and p-q != x-y
// the former focuses on eliminating 'left bottom right top' diagonal
// the latter focuses on eliminating 'left top right bottom' diagonal
//
// - col_per_row: the list of column index per row
// - cur_row: current row we are searching for a valid column
// - xy_diff: the list of x-y
// - xy_sum: the list of x+y
class Solution2 {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<int>> ress;

        std::vector<int> col_per_row;
        std::vector<int> xy_diff;
        std::vector<int> xy_sum;

        std::function<void()> dfs = [&]() {
            int cur_row = static_cast<int>(col_per_row.size());
            if (cur_row == n) {
                ress.push_back(col_per_row);
                return;
            }
            for (int col = 0; col < n; ++col) {
                bool ok = true;
                for (int v : col_per_row) {
                    if (v == col) { ok = false; break; }
                }
                if (!ok) continue;
                for (int v : xy_diff) {
                    if (v == cur_row - col) { ok = false; break; }
                }
                if (!ok) continue;
                for (int v : xy_sum) {
                    if (v == cur_row + col) { ok = false; break; }
                }
                if (!ok) continue;

                col_per_row.push_back(col);
                xy_diff.push_back(cur_row - col);
                xy_sum.push_back(cur_row + col);
                dfs();
                col_per_row.pop_back();
                xy_diff.pop_back();
                xy_sum.pop_back();
            }
        };

        dfs();

        std::vector<std::vector<std::string>> ans;
        ans.reserve(ress.size());
        for (const auto& res : ress) {
            std::vector<std::string> board;
            board.reserve(n);
            for (int i = 0; i < n; ++i) {
                std::string s(n, '.');
                s[res[i]] = 'Q';
                board.push_back(std::move(s));
            }
            ans.push_back(std::move(board));
        }
        return ans;
    }
};