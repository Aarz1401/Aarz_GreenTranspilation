#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

class Solution {
public:
    int minSwapsCouples(std::vector<int>& row) {
        int N = static_cast<int>(row.size()) / 2;
        std::vector<std::vector<int>> couples(N);
        for (int seat = 0; seat < static_cast<int>(row.size()); ++seat) {
            int num = row[seat];
            couples[num / 2].push_back(seat / 2);
        }
        std::vector<std::vector<int>> adj(N);
        for (const auto& c : couples) {
            int couch1 = c[0], couch2 = c[1];
            adj[couch1].push_back(couch2);
            adj[couch2].push_back(couch1);
        }

        auto removeEdge = [](std::vector<int>& vec, int val) {
            for (auto it = vec.begin(); it != vec.end(); ++it) {
                if (*it == val) {
                    vec.erase(it);
                    break;
                }
            }
        };

        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) continue;
            int couch1 = couch, couch2 = adj[couch].back();
            adj[couch].pop_back();
            while (couch2 != couch) {
                result += 1;
                removeEdge(adj[couch2], couch1);
                couch1 = couch2;
                couch2 = adj[couch2].back();
                adj[couch2].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }
};

static std::vector<int> make_identity(int N) {
    std::vector<int> row(2 * N);
    for (int i = 0; i < 2 * N; ++i) row[i] = i;
    return row;
}

static std::vector<int> make_chain(int N) {
    std::vector<int> row = make_identity(N);
    for (int i = 0; i < N - 1; ++i) {
        std::swap(row[2 * i + 1], row[2 * (i + 1)]);
    }
    return row;
}

static std::vector<int> make_pair_reversed(int N) {
    std::vector<int> row(2 * N);
    for (int i = 0; i < N; ++i) {
        row[2 * i] = 2 * i + 1;
        row[2 * i + 1] = 2 * i;
    }
    return row;
}

static std::vector<int> make_alternating(int N) {
    std::vector<int> row;
    row.reserve(2 * N);
    for (int i = 0; i < N; ++i) row.push_back(2 * i);
    for (int i = 0; i < N; ++i) row.push_back(2 * i + 1);
    return row;
}

static std::vector<int> make_random(int N, uint32_t seed) {
    std::vector<int> row = make_identity(N);
    std::mt19937 rng(seed);
    std::shuffle(row.begin(), row.end(), rng);
    return row;
}

int main() {
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.push_back(make_identity(1));            // [0,1]
    tests.push_back(make_chain(2));               // N=2 chain
    tests.push_back(make_chain(3));               // N=3 chain
    tests.push_back(make_pair_reversed(4));       // within-pair reversed
    tests.push_back(make_alternating(5));         // evens then odds
    tests.push_back(make_random(8, 42));          // random with fixed seed
    tests.push_back(make_identity(12));           // larger identity
    tests.push_back(make_chain(25));              // medium chain
    tests.push_back(make_random(60, 1234567));    // larger random
    tests.push_back(make_chain(1000));            // big chain

    Solution solution;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& row : tests) {
            checksum += solution.minSwapsCouples(row);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}