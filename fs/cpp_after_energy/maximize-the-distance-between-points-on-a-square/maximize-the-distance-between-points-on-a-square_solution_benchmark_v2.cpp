#include <vector>
#include <algorithm>

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
    vector<TestCase> tests = {
        {10, {{0,0},{0,5},{0,10},{4,10},{10,10},{10,7},{10,3},{6,0},{3,0},{10,0}}, 1},
        {10, {{0,0},{10,0}}, 2},
        {5,  {{0,0},{0,5},{5,5},{5,0},{0,3},{2,5},{5,2},{3,0}}, 3},
        {1000, {{0,500},{250,1000},{1000,250},{500,0},{1000,999},{1,0},{0,1},{999,1000}}, 4},
        {7,  {{3,0}}, 2},
        {12, {{1,0},{3,0},{6,0},{8,0},{11,0}}, 3},
        {9,  {{0,0},{0,9},{9,9},{9,0}}, 4},
        {20, {{0,10},{5,20},{20,15},{10,0},{0,1},{19,20},{20,1},{1,0},{0,19},{15,20},{20,19},{19,0}}, 8},
        {3,  {{0,0},{3,0},{0,3},{1,0},{3,2}}, 2},
        {50, {{0,0},{0,25},{0,50},{25,50},{50,50},{50,25},{50,0},{25,0},{10,50},{40,0},{0,10},{50,40},{5,0},{0,5}}, 5}
    };

    Solution s;
    //volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = s.maxDistance(t.side, t.points, t.k);
        }
        //sink = checksum;
    }
    return 0;
}