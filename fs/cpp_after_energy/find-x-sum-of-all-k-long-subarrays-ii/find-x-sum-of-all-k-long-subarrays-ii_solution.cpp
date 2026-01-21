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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
