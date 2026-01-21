#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>
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
