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
#include <set>
#include <chrono>

using namespace std;

struct LineContainer {
    struct Line {
        long long k, m;
        mutable long double p;
    };
    struct Cmp {
        using is_transparent = void;
        bool operator()(const Line& a, const Line& b) const { return a.k < b.k; }
        bool operator()(const Line& a, const long double& x) const { return a.p < x; }
        bool operator()(const long double& x, const Line& a) const { return x < a.p; }
    };
    static constexpr long double INF = 1e30L;
    std::multiset<Line, Cmp> hull;

    // Update intersection point x->p with next line y; return true if x->p >= y->p
    bool isect(multiset<Line, Cmp>::iterator x, multiset<Line, Cmp>::iterator y) {
        if (y == hull.end()) {
            x->p = INF;
            return false;
        }
        if (x->k == y->k) {
            x->p = (x->m > y->m) ? INF : -INF;
        } else {
            x->p = (long double)(y->m - x->m) / (long double)(x->k - y->k);
        }
        return x->p >= y->p;
    }

    void add(long long k, long long m) {
        auto z = hull.insert({k, m, 0});
        auto y = z;
        auto x = y;
        ++y;
        while (isect(x, y)) y = hull.erase(y);
        if (x != hull.begin()) {
            auto x2 = x;
            --x2;
            if (isect(x2, x)) {
                hull.erase(x);
                x = x2;
                isect(x, y);
            }
        }
        while (x != hull.begin()) {
            auto x2 = x;
            --x2;
            if (x2->p < x->p) break;
            hull.erase(x);
            x = x2;
            isect(x, y);
        }
    }

    long long query(long long x) const {
        auto it = hull.lower_bound((long double)x);
        return it->k * x + it->m;
    }
};

class Solution {
public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size();
        vector<long long> prefix1(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix1[i + 1] = prefix1[i] + nums[i];
        }
        vector<long long> prefix2(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix2[i + 1] = prefix2[i] + cost[i];
        }

        long long dp = 0;
        LineContainer lc;
        for (int i = n - 1; i >= 0; --i) {
            long long k1 = prefix1[i + 1];
            long long m1 = -(dp + k1 * prefix2[i + 1]);
            lc.add(k1, m1);
            dp = -lc.query(prefix2[i]) + 1LL * k * (prefix2[n] - prefix2[i]);
        }
        return dp;
    }
};

struct TestCase {
    vector<int> nums;
    vector<int> cost;
    int k;
};
