#include <iostream>
#include <chrono>
#include <cstdint>
#include <array>
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

int main() {
    Solution sol;

    // 10 diverse integer inputs covering edge and typical cases
    const std::array<int, 10> tests = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};

    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : tests) {
            checksum += static_cast<uint64_t>(sol.totalNQueens(n));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}