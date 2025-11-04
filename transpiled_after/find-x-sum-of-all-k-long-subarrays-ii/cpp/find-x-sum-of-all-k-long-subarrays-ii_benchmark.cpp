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
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    tests.push_back(TestCase{{1, 2, 3, 4, 5}, 3, 1});                            // simple increasing
    tests.push_back(TestCase{{7, 7, 7, 7, 7, 7}, 2, 2});                         // all equal
    tests.push_back(TestCase{{1, 1, 2, 2, 3, 3, 4, 4}, 5, 3});                   // increasing with duplicates
    tests.push_back(TestCase{{-5, -1, 0, 2, -1, 2, 3, -5}, 4, 2});               // includes negatives
    tests.push_back(TestCase{{1000000000, -1000000000, 999999999, -999999999, 0, 123456789, -123456789}, 3, 2}); // large magnitude
    tests.push_back(TestCase{{10, -10, 20, -20, 0}, 1, 5});                      // k = 1, x >= unique
    tests.push_back(TestCase{{4, 4, 4, 2, 2, 7, 7, 7}, 8, 0});                   // x = 0
    tests.push_back(TestCase{{5, 5, 5, 5, 3, 3, 3, 2, 2}, 6, 2});                // many duplicates
    tests.push_back(TestCase{{0, 1, 0, 1, 0, 1, 2, 2, 2, 3, 0}, 5, 3});          // zigzag with zeros
    tests.push_back(TestCase{{8, 1, 8, 2, 8, 3, 8, 4, 8, 5, 7, 7, 9, 9, 1, 2}, 10, 4}); // mixed pattern

    Solution sol;
    const int iterations = 1000;

    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<int> nums = tc.nums; // copy to prevent any aliasing assumptions
            auto res = sol.findXSum(nums, tc.k, tc.x);
            if (!res.empty()) {
                checksum += static_cast<unsigned long long>(res.back());
            }
            checksum ^= static_cast<unsigned long long>(res.size());
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto dur_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (nanoseconds): " << dur_ns << "\n";

    return 0;
}