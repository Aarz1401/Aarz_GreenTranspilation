#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */

class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        const int L = 6;
        const int N = static_cast<int>(wordlist.size());
        vector<vector<int>> H(N, vector<int>(N, 0));
        for (int i = 0; i < N; ++i) {
            H[i][i] = L;
            for (int j = i + 1; j < N; ++j) {
                int m = match(wordlist[i], wordlist[j], L);
                H[i][j] = m;
                H[j][i] = m;
            }
        }

        vector<int> possible(N);
        for (int i = 0; i < N; ++i) possible[i] = i;

        for (int attempt = 0; attempt < 10 && !possible.empty(); ++attempt) {
            int guess = solve(H, possible);
            int n = master.guess(wordlist[guess]);
            if (n == L) return;
            vector<int> next;
            next.reserve(possible.size());
            for (int j : possible) {
                if (H[guess][j] == n) {
                    next.push_back(j);
                }
            }
            possible.swap(next);
        }
    }

private:
    static int match(const string& a, const string& b, int L) {
        int cnt = 0;
        for (int i = 0; i < L; ++i) {
            if (a[i] == b[i]) ++cnt;
        }
        return cnt;
    }

    static int solve(const vector<vector<int>>& H, const vector<int>& possible) {
        int best_guess = -1;
        int min_max_group_size = numeric_limits<int>::max();
        for (int guess : possible) {
            array<int, 7> sizes{};
            sizes.fill(0);
            for (int j : possible) {
                if (j == guess) continue;
                int m = H[guess][j];
                if (m >= 0 && m <= 6) {
                    ++sizes[m];
                }
            }
            int max_group_size = 0;
            for (int s : sizes) max_group_size = max(max_group_size, s);
            if (max_group_size < min_max_group_size) {
                min_max_group_size = max_group_size;
                best_guess = guess;
            }
        }
        return best_guess;
    }
};