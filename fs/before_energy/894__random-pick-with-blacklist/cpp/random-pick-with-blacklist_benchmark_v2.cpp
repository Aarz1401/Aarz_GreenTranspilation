#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
using namespace std;

// Time:  ctor: O(b)
//        pick: O(1)
// Space: O(b)
class Solution {
public:
    Solution(int N, vector<int>& blacklist) : gen(random_device{}()) {
        n_ = N - static_cast<int>(blacklist.size());
        unordered_set<int> blackset(blacklist.begin(), blacklist.end());
        vector<int> whites;
        whites.reserve(N - n_);
        for (int x = n_; x < N; ++x) {
            if (!blackset.count(x)) {
                whites.emplace_back(x);
            }
        }
        int wi = 0;
        for (int b : blacklist) {
            if (b < n_) {
                lookup[b] = whites[wi++];
            }
        }
        dist = (n_ > 0) ? uniform_int_distribution<int>(0, n_ - 1)
                        : uniform_int_distribution<int>(0, 0);
    }
    
    int pick() {
        int index = dist(gen);
        auto it = lookup.find(index);
        return (it != lookup.end()) ? it->second : index;
    }

private:
    int n_;
    unordered_map<int, int> lookup;
    mt19937 gen;
    uniform_int_distribution<int> dist;
};

struct TestCase {
    int N;
    vector<int> blacklist;
};

int main() {
    vector<TestCase> tests = {
        {1, {}},
        {2, {1}},
        {3, {0}},
        {4, {2}},
        {5, {0, 4}},
        {10, {1, 2, 3, 4, 5, 6, 7, 8}},
        {7, {5, 6}},
        {1000, {}},
        {1000, {0, 10, 999, 500, 250, 750, 333, 666, 100, 900}},
        {100000, {0, 1, 2, 3, 4, 5, 42, 123, 4567, 54321, 75000, 99998, 99999}}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            Solution sol(t.N, t.blacklist);
            int r = sol.pick();
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}