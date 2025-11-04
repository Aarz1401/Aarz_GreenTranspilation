#include <iostream>
#include <vector>
#include <algorithm>
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

int main() {
    // Define 10 diverse test cases
    vector<TestCase> tests;

    // 1) Mixed edges and corners
    tests.push_back(TestCase{
        10,
        {
            {0,0}, {0,5}, {10,10}, {10,5}, {5,10}, {5,0}
        },
        3
    });

    // 2) All points on left edge, dense
    tests.push_back(TestCase{
        7,
        {
            {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6}, {0,7}
        },
        4
    });

    // 3) Bottom edge only
    tests.push_back(TestCase{
        12,
        {
            {1,0}, {5,0}, {6,0}, {11,0}
        },
        2
    });

    // 4) Right edge with duplicates
    tests.push_back(TestCase{
        9,
        {
            {9,0}, {9,3}, {9,9}, {9,9}
        },
        3
    });

    // 5) Spread across all edges
    tests.push_back(TestCase{
        100,
        {
            {0,20}, {0,80},
            {30,100}, {70,100},
            {100,90}, {100,10},
            {90,0}, {10,0}
        },
        5
    });

    // 6) Minimal square with all corners
    tests.push_back(TestCase{
        1,
        {
            {0,0}, {0,1}, {1,1}, {1,0}
        },
        2
    });

    // 7) No points
    tests.push_back(TestCase{
        50,
        {
        },
        4
    });

    // 8) Mixed edges including a corner
    tests.push_back(TestCase{
        8,
        {
            {0,2}, {0,7}, {3,8}, {8,6}, {4,0}, {8,0}
        },
        4
    });

    // 9) k = 0 edge case
    tests.push_back(TestCase{
        13,
        {
            {0,0}, {13,0}, {0,13}, {13,13}, {6,13}, {13,6}, {7,0}
        },
        0
    });

    // 10) Very large side with few points, large k to keep search range small
    tests.push_back(TestCase{
        1000000000,
        {
            {0,0}, {1000000000,0}, {0,1000000000}, {1000000000,1000000000}, {500000000,0}
        },
        1000000000
    });

    Solution sol;

    volatile long long total = 0; // volatile to prevent optimization
    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            total += sol.maxDistance(tc.side, tc.points, tc.k);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Print to ensure computations aren't optimized away
    std::cout << "Total result: " << total << "\n";
    std::cout << "Elapsed time (ms): " << dur << "\n";
    return 0;
}