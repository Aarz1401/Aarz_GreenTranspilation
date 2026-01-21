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

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        struct Node {
            int cnt;
            int v;
        };
        struct Comp {
            bool operator()(const Node& a, const Node& b) const {
                if (a.cnt != b.cnt) return a.cnt > b.cnt; // higher count first
                if (a.v != b.v) return a.v > b.v;         // higher value first
                return false;
            }
        };

        multiset<Node, Comp> L, R; // L: top x, R: rest
        long long sumL = 0;
        unordered_map<int, int> cnt;

        auto add_to_L = [&](const Node& n) {
            L.insert(n);
            sumL += 1LL * n.cnt * n.v;
        };
        auto add_to_R = [&](const Node& n) {
            R.insert(n);
        };
        auto erase_from_L = [&](const Node& n) {
            auto it = L.find(n);
            if (it != L.end()) {
                sumL -= 1LL * it->cnt * it->v;
                L.erase(it);
            }
        };
        auto erase_from_R = [&](const Node& n) {
            auto it = R.find(n);
            if (it != R.end()) {
                R.erase(it);
            }
        };

        auto comp = Comp();

        auto rebalance = [&]() {
            // Ensure L has at most x elements
            while ((int)L.size() > x) {
                auto it = prev(L.end());
                Node n = *it;
                sumL -= 1LL * n.cnt * n.v;
                L.erase(it);
                R.insert(n);
            }
            // Ensure L has up to x elements by moving best from R
            while ((int)L.size() < x && !R.empty()) {
                auto it = R.begin();
                Node n = *it;
                R.erase(it);
                sumL += 1LL * n.cnt * n.v;
                L.insert(n);
            }
            // Ensure ordering between L and R: no element in R better than worst in L
            while (!L.empty() && !R.empty()) {
                const Node& bestR = *R.begin();
                const Node& worstL = *prev(L.end());
                if (comp(bestR, worstL)) {
                    // swap bestR into L and worstL into R
                    Node br = bestR;
                    Node wl = worstL;
                    R.erase(R.begin());
                    auto itW = prev(L.end());
                    sumL -= 1LL * itW->cnt * itW->v;
                    L.erase(itW);
                    sumL += 1LL * br.cnt * br.v;
                    L.insert(br);
                    R.insert(wl);
                } else {
                    break;
                }
            }
            // If still size(L) < x and R has elements (could happen after swaps), move best
            while ((int)L.size() < x && !R.empty()) {
                auto it = R.begin();
                Node n = *it;
                R.erase(it);
                sumL += 1LL * n.cnt * n.v;
                L.insert(n);
            }
        };

        auto increase = [&](int v) {
            int old = cnt[v];
            if (old > 0) {
                Node oldN{old, v};
                auto itL = L.find(oldN);
                if (itL != L.end()) {
                    sumL -= 1LL * itL->cnt * itL->v;
                    L.erase(itL);
                } else {
                    erase_from_R(oldN);
                }
            }
            cnt[v] = old + 1;
            Node newN{old + 1, v};
            // Insert into L first, then rebalance
            add_to_L(newN);
            rebalance();
        };

        auto decrease = [&](int v) {
            int old = cnt[v];
            if (old == 0) return;
            Node oldN{old, v};
            auto itL = L.find(oldN);
            if (itL != L.end()) {
                sumL -= 1LL * itL->cnt * itL->v;
                L.erase(itL);
            } else {
                erase_from_R(oldN);
            }
            if (old - 1 == 0) {
                cnt.erase(v);
            } else {
                cnt[v] = old - 1;
                Node newN{old - 1, v};
                // Insert into L first, then rebalance
                add_to_L(newN);
            }
            rebalance();
        };

        vector<long long> result;
        for (int i = 0; i < (int)nums.size(); ++i) {
            increase(nums[i]);
            if (i < k - 1) continue;
            result.push_back(sumL);
            decrease(nums[i - (k - 1)]);
        }
        return result;
    }
};

struct TestCase {
    vector<int> nums;
    int k;
    int x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Prepare 10 diverse test cases
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Mixed small array
    tests.push_back(TestCase{
        {1, 2, 3, 2, 2, 3, 1, 4, 4, 4, 5, 5, 6, 1, 2, 3, 7, 7, 7, 8}, 5, 3
    });

    // 2) All same values
    {
        vector<int> v(200, 42);
        tests.push_back(TestCase{v, 50, 1});
    }

    // 3) Strictly increasing sequence
    {
        vector<int> v(500);
        for (int i = 0; i < 500; ++i) v[i] = i + 1;
        tests.push_back(TestCase{v, 100, 10});
    }

    // 4) Negative and positive mix with modular pattern
    {
        vector<int> v(256);
        for (int i = 0; i < 256; ++i) v[i] = (i * 7 % 101) - 50;
        tests.push_back(TestCase{v, 60, 8});
    }

    // 5) k = 1, small ranges
    {
        vector<int> v(100);
        for (int i = 0; i < 100; ++i) v[i] = (i * 31 + 7) % 9 - 4;
        tests.push_back(TestCase{v, 1, 1});
    }

    // 6) k = n, repeated pattern
    {
        vector<int> v(150);
        for (int i = 0; i < 150; ++i) v[i] = i % 20;
        tests.push_back(TestCase{v, 150, 20});
    }

    // 7) x = 0
    {
        vector<int> v(80);
        for (int i = 0; i < 80; ++i) v[i] = (i % 5) - 2;
        tests.push_back(TestCase{v, 10, 0});
    }

    // 8) Many distinct values in a higher range
    {
        vector<int> v(300);
        for (int i = 0; i < 300; ++i) v[i] = 1000 + i;
        tests.push_back(TestCase{v, 30, 15});
    }

    // 9) k > n (should result in empty output)
    {
        vector<int> v(30);
        for (int i = 0; i < 30; ++i) v[i] = (i * 97 + 12345) % 1000 - 500;
        tests.push_back(TestCase{v, 100, 10});
    }

    // 10) Large magnitude values alternating sign
    {
        vector<int> v(200);
        for (int i = 0; i < 200; ++i) {
            if (i % 2 == 0) v[i] = INT_MAX / 4 - i;
            else v[i] = INT_MIN / 4 + i;
        }
        tests.push_back(TestCase{v, 50, 25});
    }

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            // Work on a non-const reference as required by the function signature
            auto& tc = tests[i];
            vector<long long> res = sol.findXSum(tc.nums, tc.k, tc.x);

            // Accumulate a checksum to prevent optimization
            for (size_t j = 0; j < res.size(); ++j) {
                checksum += res[j] + 1315423911ULL + ((iter + 1) * (i + 1) * (j + 1));
            }
            checksum += static_cast<long long>(res.size() * (i + 1) + iter);
        }
    }

    auto end = clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ns): " << elapsed_ns << "\n";

    return 0;
}