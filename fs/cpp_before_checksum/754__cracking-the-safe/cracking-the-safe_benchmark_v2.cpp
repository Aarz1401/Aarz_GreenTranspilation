#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Time:  O(k^n)
// Space: O(k^n)
class Solution {
public:
    string crackSafe(int n, int k) {
        int M = 1;
        for (int i = 0; i < n - 1; ++i) {
            M *= k;
        }
        int total = 1;
        for (int i = 0; i < n; ++i) {
            total *= k;
        }

        // rotate: i*k^(n-1) + q => q*k + i
        vector<int> P;
        P.reserve(total);
        for (int i = 0; i < k; ++i) {
            for (int q = 0; q < M; ++q) {
                P.emplace_back(q * k + i);
            }
        }

        string result;
        result.reserve(total + n - 1);
        for (int i = 0; i < n - 1; ++i) {
            result.push_back(char('0' + (k - 1)));
        }
        for (int i = 0; i < total; ++i) {
            int j = i;
            // concatenation in lexicographic order of Lyndon words
            while (P[j] >= 0) {
                result.push_back(char('0' + (j / M)));
                int pj = P[j];
                P[j] = -1;
                j = pj;
            }
        }
        return result;
    }
};

int main() {
    vector<pair<int,int>> tests = {
        {1, 2},
        {1, 10},
        {2, 2},
        {2, 3},
        {2, 7},
        {3, 2},
        {3, 3},
        {3, 10},
        {4, 2},
        {4, 5}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            string res = s.crackSafe(tc.first, tc.second);
            checksum += static_cast<int>(res.size());
            checksum += static_cast<unsigned char>(res.front());
            checksum += static_cast<unsigned char>(res.back());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}