#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int minLength(string s, int numOps) {
        int n = static_cast<int>(s.size());
        auto check = [&](int x) -> bool {
            if (x == 1) {
                int cnt = 0;
                for (int i = 0; i < n; ++i) {
                    int val = s[i] - '0';
                    if (val != (i % 2)) {
                        ++cnt;
                    }
                }
                return min(cnt, n - cnt) <= numOps;
            }
            long long ops = 0;
            int cnt = 1;
            for (int i = 1; i < n; ++i) {
                if (s[i] == s[i - 1]) {
                    ++cnt;
                } else {
                    ops += cnt / (x + 1);
                    cnt = 1;
                }
            }
            ops += cnt / (x + 1);
            return ops <= numOps;
        };

        int left = 1, right = n;
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
    vector<pair<string, int>> tests;
    tests.emplace_back("0", 0);
    tests.emplace_back("1", 1);
    tests.emplace_back("00", 0);
    tests.emplace_back("01", 0);
    tests.emplace_back("010101010101010", 0);
    tests.emplace_back("0010110100110", 2);
    tests.emplace_back("11111111111111111111", 5);
    tests.emplace_back("000111000111000111000111000111", 4);
    tests.emplace_back("10110011100011110000", 2);
    string longRun;
    longRun.reserve(200);
    for (int i = 0; i < 25; ++i) longRun += "11110000";
    tests.emplace_back(longRun, 20);

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.minLength(tc.first, tc.second);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}