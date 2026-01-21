#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
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


// Time:  ctor: O(b log b)
//        pick: O(log b)
// Space: O(b)
class Solution2 {
public:
    Solution2(int N, vector<int>& blacklist) : gen(random_device{}()) {
        n_ = N - static_cast<int>(blacklist.size());
        bl = blacklist;
        sort(bl.begin(), bl.end());
        dist = (n_ > 0) ? uniform_int_distribution<int>(0, n_ - 1)
                        : uniform_int_distribution<int>(0, 0);
    }
    
    int pick() {
        int index = dist(gen);
        int left = 0, right = static_cast<int>(bl.size()) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (index + mid < bl[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return index + left;
    }

private:
    int n_;
    vector<int> bl;
    mt19937 gen;
    uniform_int_distribution<int> dist;
};