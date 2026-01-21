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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
    vector<TestCase> tests;

    // 1. Corners of a 10x10 square, moderate k
    tests.push_back(TestCase{
        10,
        {{0,0},{0,10},{10,10},{10,0}},
        2
    });

    // 2. Small side=1, all four corners/edges, higher k
    tests.push_back(TestCase{
        1,
        {{0,0},{0,1},{1,1},{1,0}},
        3
    });

    // 3. Mixed positions on all edges, side=50
    tests.push_back(TestCase{
        50,
        {{0,17},{12,50},{50,49},{33,0},{50,1},{0,25},{25,50},{50,25}},
        4
    });

    // 4. Single point, k=1
    tests.push_back(TestCase{
        5,
        {{0,3}},
        1
    });

    // 5. Many points on bottom edge, larger side and k
    tests.push_back(TestCase{
        100,
        {{0,0},{10,0},{20,0},{30,0},{40,0},{50,0},{60,0},{70,0},{80,0},{90,0},{100,0}},
        5
    });

    // 6. Duplicates and corners on side=7
    tests.push_back(TestCase{
        7,
        {{0,0},{0,0},{7,7},{7,7},{3,7},{7,3},{0,7}},
        3
    });

    // 7. Mixed across edges, side=12
    tests.push_back(TestCase{
        12,
        {{0,6},{4,12},{12,8},{8,0},{12,4},{0,0}},
        4
    });

    // 8. Large side, sparse points
    tests.push_back(TestCase{
        1000,
        {{0,0},{0,1000},{1000,1000},{1000,0},{500,1000},{1000,500}},
        2
    });

    // 9. Dense small square, many perimeter points
    tests.push_back(TestCase{
        2,
        {{0,0},{0,1},{0,2},{1,2},{2,2},{2,1},{2,0},{1,0}},
        4
    });

    // 10. Empty points with k=0 (early return path)
    tests.push_back(TestCase{
        3,
        {},
        0
    });

    Solution sol;
    long long checksum = 0;

    using clock_type = std::chrono::high_resolution_clock;
    auto start = clock_type::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.maxDistance(tests[i].side, tests[i].points, tests[i].k);
            checksum += (res ^ static_cast<int>(i) ^ iter);
        }
    }

    auto end = clock_type::now();
    std::chrono::duration<double, std::milli> elapsed_ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms.count() << "\n";
    return 0;
}