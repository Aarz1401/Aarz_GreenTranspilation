#include <string>
#include <vector>

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