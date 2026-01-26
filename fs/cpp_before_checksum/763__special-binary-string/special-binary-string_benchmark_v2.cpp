#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// Time:  f(n) = k * f(n/k) + n/k * klogk <= O(logn * nlogk) <= O(n^2)
//        n is the length of S, k is the max number of special strings in each depth
// Space: O(n)

class Solution {
public:
    string makeLargestSpecial(string S) {
        vector<string> result;
        int anchor = 0, count = 0;
        for (int i = 0; i < static_cast<int>(S.size()); ++i) {
            count += (S[i] == '1') ? 1 : -1;
            if (count == 0) {
                string inner = S.substr(anchor + 1, i - anchor - 1);
                string rec = makeLargestSpecial(inner);
                result.push_back(string("1") + rec + "0");
                anchor = i + 1;
            }
        }
        sort(result.begin(), result.end(), greater<string>());
        string ans;
        for (const auto& s : result) {
            ans += s;
        }
        return ans;
    }
};

int main() {
    vector<string> tests = {
        "10",
        "1100",
        "1010",
        "111000",
        "110100",
        "110010",
        "11100100",
        "11011000",
        "1011001100",
        "1101101000"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            string r = sol.makeLargestSpecial(s);
            checksum += static_cast<int>(r.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}