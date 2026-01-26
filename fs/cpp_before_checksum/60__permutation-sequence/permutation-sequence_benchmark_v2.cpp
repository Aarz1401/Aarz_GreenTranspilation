#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Solution {
public:
    std::string getPermutation(int n, int k) {
        std::vector<int> perm;
        perm.reserve(n);
        for (int i = 1; i <= n; ++i) {
            perm.push_back(i);
        }
        
        long long kk = static_cast<long long>(k) - 1;
        long long fact = 1;
        for (int i = 2; i <= n - 1; ++i) {
            fact *= i;
        }
        
        std::string seq;
        seq.reserve(n);
        for (int i = n - 1; i >= 0; --i) {
            int idx = static_cast<int>(kk / fact);
            seq += std::to_string(perm[idx]);
            perm.erase(perm.begin() + idx);
            if (i > 0) {
                kk %= fact;
                fact /= i;
            }
        }
        return seq;
    }
};

volatile int sink = 0;

int main() {
    std::vector<std::pair<int,int>> tests = {
        {1, 1},
        {2, 1},
        {2, 2},
        {3, 5},
        {4, 9},
        {5, 42},
        {6, 400},
        {7, 2500},
        {8, 40320},
        {9, 362880}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            std::string res = sol.getPermutation(t.first, t.second);
            checksum += static_cast<int>(res[0]);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}