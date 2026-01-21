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
