#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
public:
    int minLength(string s, int numOps) {
        auto check = [&](int x) -> bool {
            if (x == 1) {
                int cnt = 0;
                for (int i = 0; i < static_cast<int>(s.size()); ++i) {
                    int bit = s[i] - '0';
                    if (bit != (i % 2)) {
                        cnt++;
                    }
                }
                return min(cnt, static_cast<int>(s.size()) - cnt) <= numOps;
            }
            long long ops = 0;
            int cnt = 0;
            for (int i = 0; i < static_cast<int>(s.size()); ++i) {
                cnt += 1;
                if (i + 1 == static_cast<int>(s.size()) || s[i + 1] != s[i]) {
                    ops += cnt / (x + 1);
                    cnt = 0;
                }
            }
            return ops <= numOps;
        };

        int left = 1, right = static_cast<int>(s.size());
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    vector<pair<string, int>> tests = {
        {"0", 0},
        {"1", 0},
        {"00000", 0},
        {"010101", 0},
        {"11110000", 2},
        {"00110011", 1},
        {"101010001110", 3},
        {"000111000111000", 5},
        {"0100111001011", 4},
        {"0010010110110001110100011101100010110010100110", 7}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.minLength(t.first, t.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}