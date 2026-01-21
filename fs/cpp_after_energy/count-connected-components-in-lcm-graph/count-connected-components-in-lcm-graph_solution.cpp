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
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

// Time:  O(n + tlogt), t = threshold
// Space: O(t)

// union find, number theory
class UnionFind {  // Time: O(n * alpha(n)), Space: O(n)
public:
    vector<int> parent;
    vector<int> rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int find_set(int x) {
        int r = x;
        while (parent[r] != r) {
            r = parent[r];
        }
        // path compression
        while (parent[x] != x) {
            int p = parent[x];
            parent[x] = r;
            x = p;
        }
        return r;
    }
    bool union_set(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y) {
            return false;
        }
        if (rank_[x] > rank_[y]) {
            swap(x, y);
        }
        parent[x] = y;
        if (rank_[x] == rank_[y]) {
            rank_[y] += 1;
        }
        return true;
    }
};

class Solution {
public:
    int countComponents(vector<int>& nums, int threshold) {
        UnionFind uf(threshold);
        vector<int> lookup(threshold, -1);
        int result = static_cast<int>(nums.size());
        for (const int& x : nums) {
            if (x - 1 >= threshold) {
                continue;
            }
            for (int i = x; i <= threshold; i += x) {
                if (lookup[i - 1] == -1) {
                    lookup[i - 1] = x - 1;
                    continue;
                }
                if (uf.union_set(lookup[i - 1], x - 1)) {
                    result -= 1;
                }
                if (i == x) {
                    break;
                }
            }
        }
        return result;
    }
};
