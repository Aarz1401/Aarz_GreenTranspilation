#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

// Time:  O(logn)
// Space: O(logn)

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string str_N = to_string(N);
        unordered_set<char> set_D;
        set_D.reserve(D.size() * 2);
        for (const string& s : D) {
            if (!s.empty()) {
                set_D.insert(s[0]);
            }
        }

        int m = static_cast<int>(D.size());
        int L = static_cast<int>(str_N.size());

        auto ipow = [](int base, int exp) -> int {
            long long res = 1;
            long long b = base;
            while (exp > 0) {
                if (exp & 1) res *= b;
                b *= b;
                exp >>= 1;
            }
            return static_cast<int>(res);
        };

        long long result = 0;
        for (int i = 1; i < L; ++i) {
            result += ipow(m, i);
        }

        int i = 0;
        while (i < L) {
            int countLess = 0;
            for (const string& s : D) {
                if (!s.empty() && s[0] < str_N[i]) {
                    ++countLess;
                }
            }
            result += static_cast<long long>(countLess) * ipow(m, L - i - 1);
            if (!set_D.count(str_N[i])) {
                break;
            }
            ++i;
        }
        return static_cast<int>(result + (i == L ? 1 : 0));
    }
};