#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <limits>
#include <cmath>
#include <chrono>

using namespace std;

// Hash for vector<int> to use in unordered containers
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t seed = 0xcbf29ce484222325ULL; // FNV offset basis
        for (int x : v) {
            seed ^= static_cast<size_t>(x) + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

// A* Search Algorithm (greedy variant with closer/detour)
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        auto dot = [](const pair<int, int>& p1, const pair<int, int>& p2) -> int {
            return p1.first * p2.first + p1.second * p2.second;
        };

        auto heuristic_estimate = [&](const vector<int>& flat, int R, int C, const vector<pair<int,int>>& expected_pos) -> int {
            int result = 0;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    int val = flat[C * i + j];
                    if (val == 0) continue;
                    auto [r, c] = expected_pos[val];
                    result += abs(r - i) + abs(c - j);
                }
            }
            return result;
        };

        int R = board.size();
        int C = board[0].size();

        vector<int> begin;
        begin.reserve(R * C);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                begin.push_back(board[i][j]);
            }
        }

        vector<int> end;
        end.reserve(R * C);
        for (int v = 1; v < R * C; ++v) end.push_back(v);
        end.push_back(0);

        vector<pair<int,int>> expected(R * C);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                int key = (C * i + j + 1) % (R * C);
                expected[key] = {i, j};
            }
        }

        int min_steps = heuristic_estimate(begin, R, C, expected);

        vector<pair<int, vector<int>>> closer;
        vector<pair<int, vector<int>>> detour;
        int begin_zero = int(find(begin.begin(), begin.end(), 0) - begin.begin());
        closer.emplace_back(begin_zero, begin);

        unordered_set<vector<int>, VectorHash> lookup;

        while (true) {
            if (closer.empty()) {
                if (detour.empty()) {
                    return -1;
                }
                min_steps += 2;
                closer.swap(detour);
            }
            auto [zero, state] = closer.back();
            closer.pop_back();

            if (state == end) {
                return min_steps;
            }
            if (lookup.find(state) == lookup.end()) {
                lookup.insert(state);
                int r = zero / C, c = zero % C;
                const int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
                for (const auto& d : dirs) {
                    int i = r + d[0], j = c + d[1];
                    if (0 <= i && i < R && 0 <= j && j < C) {
                        int new_zero = i * C + j;
                        vector<int> tmp = state;
                        // tile moved into zero
                        int moved_tile = tmp[new_zero];
                        swap(tmp[zero], tmp[new_zero]);
                        vector<int> new_state = std::move(tmp);

                        auto [r2, c2] = expected[moved_tile];
                        int r1 = r, c1 = c;
                        int r0 = new_zero / C, c0 = new_zero % C;

                        bool is_closer = dot({r1 - r0, c1 - c0}, {r2 - r0, c2 - c0}) > 0;
                        if (is_closer) {
                            closer.emplace_back(new_zero, std::move(new_state));
                        } else {
                            detour.emplace_back(new_zero, std::move(new_state));
                        }
                    }
                }
            }
        }
        // Unreachable
        // return min_steps;
    }
};

int main() {
    // Define 10 diverse 2x3 sliding puzzle boards
    vector<vector<vector<int>>> tests = {
        {{1,2,3},{4,5,0}}, // solved
        {{1,2,3},{4,0,5}}, // 1 move
        {{1,2,0},{4,5,3}}, // solvable
        {{1,2,3},{5,4,0}}, // unsolvable
        {{4,1,2},{5,0,3}}, // LC example
        {{3,2,4},{1,5,0}}, // LC example
        {{1,0,2},{3,4,5}}, // solvable
        {{0,5,4},{3,2,1}}, // solvable, far
        {{2,1,3},{4,5,0}}, // unsolvable
        {{2,3,0},{1,4,5}}  // solvable
    };

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto board = tests[i]; // copy since function takes non-const reference
            int res = solver.slidingPuzzle(board);
            checksum += res * static_cast<long long>(i + 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}