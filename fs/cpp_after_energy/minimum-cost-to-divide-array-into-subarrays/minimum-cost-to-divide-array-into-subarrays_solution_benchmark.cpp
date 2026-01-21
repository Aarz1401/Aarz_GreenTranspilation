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
#include <random>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    // Prepare 10 diverse test cases
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Single element
    tests.push_back({{5}, {3}, 10});

    // 2) Two elements, small values, k = 0
    tests.push_back({{1, 2}, {2, 1}, 0});

    // 3) All equal nums and costs
    tests.push_back({vector<int>(10, 7), vector<int>(10, 7), 5});

    // 4) Increasing nums, uniform cost
    {
        int n = 100;
        vector<int> nums(n), cost(n, 1);
        for (int i = 0; i < n; ++i) nums[i] = i + 1;
        tests.push_back({move(nums), move(cost), 3});
    }

    // 5) Decreasing nums, increasing cost
    {
        int n = 100;
        vector<int> nums(n), cost(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = n - i;
            cost[i] = i + 1;
        }
        tests.push_back({move(nums), move(cost), 2});
    }

    // 6) Random moderate size
    {
        int n = 200;
        vector<int> nums(n), cost(n);
        mt19937 rng(123456);
        uniform_int_distribution<int> dnum(0, 1000);
        uniform_int_distribution<int> dcost(1, 100);
        for (int i = 0; i < n; ++i) {
            nums[i] = dnum(rng);
            cost[i] = dcost(rng);
        }
        tests.push_back({move(nums), move(cost), 7});
    }

    // 7) Large values
    {
        int n = 500;
        vector<int> nums(n, 1000000);
        vector<int> cost(n);
        for (int i = 0; i < n; ++i) cost[i] = 1000000 - (i % 1000);
        tests.push_back({move(nums), move(cost), 1000});
    }

    // 8) Alternating high/low pattern
    {
        int n = 256;
        vector<int> nums(n), cost(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = (i % 2 == 0) ? 0 : 1000000;
            cost[i] = (i % 2 == 0) ? 1 : 1000;
        }
        tests.push_back({move(nums), move(cost), 50});
    }

    // 9) Sparse zeros in cost
    {
        int n = 300;
        vector<int> nums(n), cost(n);
        mt19937 rng(789012);
        uniform_int_distribution<int> dnum(0, 1000);
        for (int i = 0; i < n; ++i) {
            nums[i] = dnum(rng);
            cost[i] = (i % 10 == 0) ? 100 : 0;
        }
        tests.push_back({move(nums), move(cost), 5});
    }

    // 10) Wave-like patterns
    {
        int n = 600;
        vector<int> nums(n), cost(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = (i * 1LL * i) % 1000;
            cost[i] = (i * 7) % 300 + 1;
        }
        tests.push_back({move(nums), move(cost), 17});
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            TestCase& t = tests[i];
            checksum += sol.minimumCost(t.nums, t.cost, t.k) ^ (long long)(iter + i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}