#include <vector>

class Solution {
public:
    // Time:  O(n!)
    // Space: O(n)
    int totalNQueens(int n) {
        if (n <= 0) return 0;
        std::vector<int> cols(n, 0);
        std::vector<int> main_diag(2 * n - 1, 0);
        std::vector<int> anti_diag(2 * n - 1, 0);
        return dfs(0, n, cols, main_diag, anti_diag);
    }

private:
    int dfs(int row, int n, std::vector<int>& cols,
            std::vector<int>& main_diag, std::vector<int>& anti_diag) {
        if (row == n) {
            return 1;
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            int md = row + i;
            int ad = row - i + (n - 1);
            if (cols[i] || main_diag[md] || anti_diag[ad]) {
                continue;
            }
            cols[i] = main_diag[md] = anti_diag[ad] = 1;
            result += dfs(row + 1, n, cols, main_diag, anti_diag);
            cols[i] = main_diag[md] = anti_diag[ad] = 0;
        }
        return result;
    }
};