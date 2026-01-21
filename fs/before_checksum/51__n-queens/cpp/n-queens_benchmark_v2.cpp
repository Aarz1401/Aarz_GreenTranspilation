#include <iostream>
#include <vector>
#include <string>
#include <functional>

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

int main() {
    std::vector<int> tests = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2};

    Solution sol;

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;

        for (int n : tests) {
            auto res = sol.solveNQueens(n);
            checksum += static_cast<int>(res.size());
        }

        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}