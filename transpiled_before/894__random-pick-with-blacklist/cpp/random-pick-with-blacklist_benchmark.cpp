#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
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

int main() {
    using namespace std::chrono;

    // Define 10 diverse test inputs
    vector<pair<int, vector<int>>> tests;
    tests.reserve(10);

    // 1) N=1, empty blacklist
    tests.push_back({1, {}});

    // 2) N=2, single blacklisted element at top
    tests.push_back({2, {1}});

    // 3) N=10, empty blacklist
    tests.push_back({10, {}});

    // 4) N=10, first half blacklisted
    tests.push_back({10, {0,1,2,3,4}});

    // 5) N=10, second half blacklisted
    tests.push_back({10, {5,6,7,8,9}});

    // 6) N=1000, even numbers blacklisted
    {
        vector<int> bl;
        bl.reserve(500);
        for (int i = 0; i < 1000; i += 2) bl.push_back(i);
        tests.push_back({1000, std::move(bl)});
    }

    // 7) N=1000, upper half blacklisted
    {
        vector<int> bl;
        bl.reserve(500);
        for (int i = 500; i < 1000; ++i) bl.push_back(i);
        tests.push_back({1000, std::move(bl)});
    }

    // 8) N=100000, 200 pseudo-random unique blacklisted indices
    {
        int N = 100000;
        unordered_set<int> s;
        s.reserve(256);
        int i = 0;
        while (s.size() < 200) {
            int val = (i * 7919 + 12345) % N;
            s.insert(val);
            ++i;
        }
        vector<int> bl;
        bl.reserve(s.size());
        for (int v : s) bl.push_back(v);
        tests.push_back({N, std::move(bl)});
    }

    // 9) N=100000, first 10000 numbers blacklisted
    {
        int N = 100000;
        vector<int> bl;
        bl.reserve(10000);
        for (int i = 0; i < 10000; ++i) bl.push_back(i);
        tests.push_back({N, std::move(bl)});
    }

    // 10) N=9973, mixed regions blacklisted
    {
        int N = 9973;
        vector<int> bl;
        // Block near the end
        for (int i = 9000; i < 9200 && i < N; ++i) bl.push_back(i);
        // Some multiples within range
        for (int i = 0; i < 300; i += 35) bl.push_back(i);
        tests.push_back({N, std::move(bl)});
    }

    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int N = tests[i].first;
            vector<int>& bl = tests[i].second;

            Solution sol(N, bl);

            // Perform several picks to exercise the picker
            int local = 0;
            for (int k = 0; k < 32; ++k) {
                local += sol.pick();
            }
            // Mix in some variation with additional picks
            local ^= sol.pick();
            checksum += (local + N) ^ static_cast<int>(i);
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (us): " << elapsed_us << "\n";
    return 0;
}