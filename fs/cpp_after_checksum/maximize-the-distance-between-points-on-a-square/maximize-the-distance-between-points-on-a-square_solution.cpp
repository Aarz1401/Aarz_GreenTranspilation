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
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        using ll = long long;
        vector<ll> p;
        p.reserve(points.size());
        for (const auto& pt : points) {
            ll x = pt[0], y = pt[1];
            if (x == 0) {
                p.emplace_back(0LL * side + y);
            } else if (y == side) {
                p.emplace_back(1LL * side + x);
            } else if (x == side) {
                p.emplace_back(2LL * side + (side - y));
            } else {
                p.emplace_back(3LL * side + (side - x));
            }
        }
        sort(p.begin(), p.end());

        auto check = [&](ll d) -> bool {
            if (p.empty()) return false;
            struct Interval { int l, r, c; };
            vector<Interval> intervals;
            intervals.push_back({0, 0, 1});
            int i = 0;
            int maxCnt = 1;
            for (int right = 1; right < (int)p.size(); ++right) {
                int left = right;
                int cnt = 1;
                while (i < (int)intervals.size()) {
                    int l = intervals[i].l;
                    int r = intervals[i].r;
                    int c = intervals[i].c;
                    if (p[right] - p[r] < d) {
                        break;
                    }
                    if ((p[l] + 4LL * side) - p[right] >= d) {
                        if (c + 1 >= cnt) {
                            cnt = c + 1;
                            left = l;
                        }
                    }
                    ++i;
                }
                intervals.push_back({left, right, cnt});
                if (cnt > maxCnt) maxCnt = cnt;
            }
            return maxCnt >= k;
        };

        auto binary_search_right = [&](ll left, ll right) -> ll {
            ll l = left, r = right;
            while (l <= r) {
                ll mid = l + (r - l) / 2;
                if (!check(mid)) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            return r;
        };

        if (k <= 0) return 0;
        ll perimeter = 4LL * side;
        ll upper = (k == 0 ? 0 : perimeter / k);
        return (int)binary_search_right(1, upper);
    }
};

struct TestCase {
    int side;
    vector<vector<int>> points;
    int k;
};
