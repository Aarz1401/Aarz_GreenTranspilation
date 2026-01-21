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
#include <functional>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        struct LazyMaxHeap {
            priority_queue<long long> pq; // max-heap
            unordered_map<long long, int> delayed;
            int sz = 0;

            void prune() {
                while (!pq.empty()) {
                    long long v = pq.top();
                    auto it = delayed.find(v);
                    if (it == delayed.end() || it->second == 0) break;
                    if (--(it->second) == 0) delayed.erase(it);
                    pq.pop();
                }
            }

            void push(long long v) {
                pq.push(v);
                sz++;
            }

            void remove(long long v) {
                delayed[v]++;
                sz--;
                prune();
            }

            long long top() {
                prune();
                return pq.top();
            }

            void pop() {
                prune();
                pq.pop();
                sz--;
            }

            int size() const { return sz; }
            bool empty() const { return sz == 0; }
        };

        struct LazyMinHeap {
            priority_queue<long long, vector<long long>, greater<long long>> pq; // min-heap
            unordered_map<long long, int> delayed;
            int sz = 0;

            void prune() {
                while (!pq.empty()) {
                    long long v = pq.top();
                    auto it = delayed.find(v);
                    if (it == delayed.end() || it->second == 0) break;
                    if (--(it->second) == 0) delayed.erase(it);
                    pq.pop();
                }
            }

            void push(long long v) {
                pq.push(v);
                sz++;
            }

            void remove(long long v) {
                delayed[v]++;
                sz--;
                prune();
            }

            long long top() {
                prune();
                return pq.top();
            }

            void pop() {
                prune();
                pq.pop();
                sz--;
            }

            int size() const { return sz; }
            bool empty() const { return sz == 0; }
        };

        struct SlidingWindow {
            LazyMaxHeap left;   // max heap
            LazyMinHeap right;  // min heap
            long long total1 = 0, total2 = 0;

            void rebalance() {
                if (left.size() < right.size()) {
                    long long v = right.top();
                    right.pop();
                    total2 -= v;
                    left.push(v);
                    total1 += v;
                } else if (left.size() > right.size() + 1) {
                    long long v = left.top();
                    left.pop();
                    total1 -= v;
                    right.push(v);
                    total2 += v;
                }
            }

            void add(long long val) {
                if (left.size() == 0 || val <= left.top()) {
                    left.push(val);
                    total1 += val;
                } else {
                    right.push(val);
                    total2 += val;
                }
                rebalance();
            }

            void remove(long long val) {
                if (val <= left.top()) {
                    left.remove(val);
                    total1 -= val;
                } else {
                    right.remove(val);
                    total2 -= val;
                }
                rebalance();
            }

            long long median() {
                return left.top();
            }
        };

        const long long INF = LLONG_MAX / 4;
        int n = nums.size();

        SlidingWindow sw;
        vector<long long> cost(n + 1, INF);
        for (int i = 0; i < n; ++i) {
            if (i - x >= 0) {
                sw.remove(nums[i - x]);
            }
            sw.add(nums[i]);
            if (i >= x - 1) {
                long long m = sw.median();
                long long leftSize = sw.left.size();
                long long rightSize = sw.right.size();
                cost[i + 1] = (m * leftSize - sw.total1) + (sw.total2 - m * rightSize);
            }
        }

        vector<long long> dp(n + 1, 0);
        for (int i = 0; i < k; ++i) {
            vector<long long> new_dp(n + 1, INF);
            int start = (i + 1) * x;
            for (int j = start; j <= n; ++j) {
                long long option1 = new_dp[j - 1];
                long long option2 = dp[j - x] >= INF || cost[j] >= INF ? INF : dp[j - x] + cost[j];
                new_dp[j] = min(option1, option2);
            }
            dp.swap(new_dp);
        }
        return dp[n];
    }
};

struct Test {
    vector<int> nums;
    int x;
    int k;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Test> tests;

    // 1) Increasing sequence, x=1 (costs 0), k=5
    tests.push_back(Test{{1,2,3,4,5,6,7,8,9,10}, 1, 5});

    // 2) Random small array, x=2, k=2
    tests.push_back(Test{{5,1,9,3,14,2,8,6}, 2, 2});

    // 3) All equal numbers (costs 0), x=3, k=3
    tests.push_back(Test{{7,7,7,7,7,7,7,7,7}, 3, 3});

    // 4) Mixed negatives and positives, x=3, k=2
    tests.push_back(Test{{-10,-5,0,5,10,-3,3,-2,2,-1,1,4}, 3, 2});

    // 5) x > n (impossible), expect INF-like result
    tests.push_back(Test{{1,2,3,4,5}, 6, 1});

    // 6) k = 0 (no operations), expect 0
    tests.push_back(Test{{9,8,7,6,5,4,3}, 3, 0});

    // 7) Larger array (generated), x=5, k=10
    {
        vector<int> v;
        v.reserve(600);
        for (int i = 0; i < 600; ++i) {
            int val = static_cast<int>((i * 37LL) % 1000) - 500;
            v.push_back(val);
        }
        tests.push_back(Test{move(v), 5, 10});
    }

    // 8) Another larger array with different pattern, x=8, k=16
    {
        vector<int> v;
        v.reserve(400);
        for (int i = 0; i < 400; ++i) {
            int val = static_cast<int>((1LL * i * i + 3LL * i + 7) % 100) - 50;
            v.push_back(val);
        }
        tests.push_back(Test{move(v), 8, 16});
    }

    // 9) Single element, x=1, k=1 (cost 0)
    tests.push_back(Test{{42}, 1, 1});

    // 10) Exact fill: n=12, x=3, k=4
    tests.push_back(Test{{4,1,7,3,2,9,5,8,6,10,11,0}, 3, 4});

    Solution sol;

    auto start_time = high_resolution_clock::now();
    unsigned long long checksum = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            long long res = sol.minOperations(t.nums, t.x, t.k);
            // Mix result into checksum to prevent optimization
            checksum ^= static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + static_cast<unsigned long long>(iter) + static_cast<unsigned long long>(t.nums.size());
        }
    }

    auto end_time = high_resolution_clock::now();
    long long elapsed_us = duration_cast<microseconds>(end_time - start_time).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}