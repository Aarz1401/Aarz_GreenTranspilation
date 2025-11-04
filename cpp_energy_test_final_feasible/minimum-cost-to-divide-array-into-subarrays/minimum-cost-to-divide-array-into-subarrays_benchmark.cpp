#include <iostream>
#include <vector>
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<TestCase> tests;

    // 1) Minimal case
    tests.push_back({{1}, {1}, 0});

    // 2) Small case with mixed values
    tests.push_back({{5, 3}, {2, 4}, 1});

    // 3) Increasing nums, decreasing cost
    tests.push_back({{1, 2, 3}, {3, 2, 1}, 2});

    // 4) Zeros in nums, uniform cost
    tests.push_back({{0, 0, 0, 0}, {1, 1, 1, 1}, 5});

    // 5) Equal nums, increasing cost
    tests.push_back({{10, 10, 10, 10, 10}, {1, 2, 3, 4, 5}, 3});

    // 6) Odd sequence nums, uniform cost
    tests.push_back({{1, 3, 5, 7, 9, 11}, {2, 2, 2, 2, 2, 2}, 4});

    // 7) Decreasing nums, increasing cost
    tests.push_back({{9, 8, 7, 6, 5, 4, 3}, {1, 3, 5, 7, 9, 11, 13}, 7});

    // 8) Larger nums, decreasing cost
    tests.push_back({{1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000}, {8, 7, 6, 5, 4, 3, 2, 1}, 10});

    // 9) Duplicates in nums and cost, large k
    tests.push_back({{2, 2, 2, 2, 2, 2, 2, 2, 2}, {9, 9, 9, 9, 9, 9, 9, 9, 9}, 100});

    // 10) Alternating zeros and ones, costs with zeros
    tests.push_back({{0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, {0, 1, 2, 0, 1, 2, 0, 1, 2, 0}, 13});

    const int iterations = 1000;

    Solution sol;
    volatile long long total = 0; // volatile to prevent optimization away

    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            total += sol.minimumCost(t.nums, t.cost, t.k);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Total: " << total << "\n";
    cout << "Time (microseconds): " << micros << "\n";

    return 0;
}