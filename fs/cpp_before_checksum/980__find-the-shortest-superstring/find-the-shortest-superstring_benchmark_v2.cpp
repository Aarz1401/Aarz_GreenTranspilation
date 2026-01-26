#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        int n = static_cast<int>(A.size());
        vector<vector<int>> overlaps(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            const string& x = A[i];
            for (int j = 0; j < n; ++j) {
                const string& y = A[j];
                int minLen = static_cast<int>(min(x.size(), y.size()));
                for (int l = minLen - 1; l >= 0; --l) {
                    if (y.compare(0, l, x, static_cast<int>(x.size()) - l, l) == 0) {
                        overlaps[i][j] = l;
                        break;
                    }
                }
            }
        }

        int totalMasks = 1 << n;
        vector<vector<int>> dp(totalMasks, vector<int>(n, 0));
        vector<vector<int>> prev(totalMasks, vector<int>(n, -1));

        for (int mask = 1; mask < totalMasks; ++mask) {
            for (int bit = 0; bit < n; ++bit) {
                if (((mask >> bit) & 1) == 0) continue;
                int prev_mask = mask ^ (1 << bit);
                for (int i = 0; i < n; ++i) {
                    if (((prev_mask >> i) & 1) == 0) continue;
                    int value = dp[prev_mask][i] + overlaps[i][bit];
                    if (value > dp[mask][bit]) {
                        dp[mask][bit] = value;
                        prev[mask][bit] = i;
                    }
                }
            }
        }

        int fullMask = totalMasks - 1;
        int bestBit = 0;
        for (int b = 1; b < n; ++b) {
            if (dp[fullMask][b] > dp[fullMask][bestBit]) {
                bestBit = b;
            }
        }

        vector<int> words;
        int mask = fullMask;
        int bit = bestBit;
        while (bit != -1) {
            words.push_back(bit);
            int nextMask = mask ^ (1 << bit);
            int nextBit = prev[mask][bit];
            mask = nextMask;
            bit = nextBit;
        }
        reverse(words.begin(), words.end());

        vector<char> inSet(n, 0);
        for (int w : words) inSet[w] = 1;
        for (int i = 0; i < n; ++i) {
            if (!inSet[i]) words.push_back(i);
        }

        string result = A[words[0]];
        for (int i = 1; i < static_cast<int>(words.size()); ++i) {
            int overlap = overlaps[words[i - 1]][words[i]];
            result += A[words[i]].substr(overlap);
        }
        return result;
    }
};

volatile int sink = 0;

int main() {
    vector<vector<string>> testCases = {
        {"alex","loves","leetcode"},
        {"catg","ctaagt","gcta","ttca","atgcatc"},
        {"abcd","cdef","fgh","de"},
        {"aa","bb","cc","dd"},
        {"a","b","c","a"},
        {"ababa","baba","aba"},
        {"the","there","answer","any","by","their"},
        {"abc","bcd","cde","defg"},
        {"xyz","yzab","zabc","abcd","bc"},
        {"lemon","melon","onion"}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : testCases) {
            vector<string> A = tc;
            string res = sol.shortestSuperstring(A);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}