#include <iostream>
#include <vector>
#include <set>

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

int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1
    tests.push_back({{5}, {3}, 2});

    // Test 2
    tests.push_back({{1, 2}, {3, 4}, 5});

    // Test 3
    tests.push_back({{3, 1, 4, 1, 5}, {2, 7, 1, 8, 2}, 3});

    // Test 4: increasing nums and costs
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 8; ++i) {
            nums.push_back(10 * i);
            cost.push_back(i);
        }
        tests.push_back({nums, cost, 4});
    }

    // Test 5: uniform nums, patterned cost
    {
        vector<int> nums(10, 1), cost;
        for (int i = 0; i < 10; ++i) {
            int v = (i % 3 == 0 ? 2 : (i % 3 == 1 ? 5 : 3));
            cost.push_back(v);
        }
        tests.push_back({nums, cost, 1});
    }

    // Test 6: descending nums, varied costs
    {
        vector<int> nums, cost;
        for (int i = 12; i >= 1; --i) {
            nums.push_back(i * 2);
        }
        for (int i = 12; i >= 1; --i) {
            cost.push_back((i * 5) % 9 + 1);
        }
        tests.push_back({nums, cost, 7});
    }

    // Test 7: larger nums
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 15; ++i) {
            nums.push_back(i * 100 + (i % 7));
            cost.push_back(16 - i);
        }
        tests.push_back({nums, cost, 10});
    }

    // Test 8: quadratic pattern nums, modular cost
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 18; ++i) {
            nums.push_back((i * i) % 50 + 1);
            cost.push_back((i * 7) % 10 + 1);
        }
        tests.push_back({nums, cost, 6});
    }

    // Test 9: Fibonacci-like nums, small cyclic costs
    {
        vector<int> nums, cost;
        int a = 1, b = 2;
        nums.push_back(a);
        nums.push_back(b);
        for (int i = 3; i <= 20; ++i) {
            int c = a + b;
            nums.push_back(c);
            a = b;
            b = c;
        }
        for (int i = 1; i <= 20; ++i) {
            cost.push_back((i % 5) + 1);
        }
        tests.push_back({nums, cost, 8});
    }

    // Test 10: alternating pattern
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 25; ++i) {
            int v = (i % 4 == 0 ? 100 : (i % 4 == 1 ? 30 : (i % 4 == 2 ? 60 : 10)));
            nums.push_back(v);
            cost.push_back((i % 7) + 1);
        }
        tests.push_back({nums, cost, 9});
    }

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            long long res = sol.minimumCost(tests[i].nums, tests[i].cost, tests[i].k);
            checksum += static_cast<int>(res);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}