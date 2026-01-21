#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <functional>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

volatile int sink = 0;

int main() {
    vector<Test> tests = {
        {{1, 2, 3, 4, 5}, 1, 2},
        {{1, 10, 1, 10, 1, 10}, 2, 3},
        {{1, 2, 3, 100, 100, 100, 4, 5}, 3, 2},
        {{-5, -1, -3, -2, 100, 101, 102, 103, 0, 0}, 4, 2},
        {{7, 7, 7, 1, 2, 3, 7, 7, 7}, 3, 3},
        {{1, 100, 100, 100, 100, 1, 1, 1, 1, 1, 1, 50}, 5, 2},
        {{0, -1, -2, -3, 4, 5, -6}, 2, 2},
        {{10, 10, 10, 20, 20, 19, 30, 31, 32, 5, 5, 5, 100, 100, 100}, 3, 4},
        {{1, 2, 100, 2, 1, 50, 50, 50, 50, 50}, 5, 2},
        {{8, 1, 9, 2, 7, 3, 6, 4, 5, 0, 5, 0, 100, -100, 100, -100, 50, 51, 49, 50}, 4, 3}
    };

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            long long res = sol.minOperations(const_cast<vector<int>&>(t.nums), t.x, t.k);
            DoNotOptimize(res); 
            //checksum += static_cast<int>(res);
        }
        //sink = checksum;
    }
    return 0;
}