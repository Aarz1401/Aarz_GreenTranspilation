#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits>
#include <tuple>
#include <utility>
#include <algorithm>
#include <chrono>

using namespace std;

// Time:  O(k*r*c + |E|log|V|) = O(k*r*c + (k*|V|)*log|V|)
//                             = O(k*r*c + (k*(k*2^k))*log(k*2^k))
//                             = O(k*r*c + (k*(k*2^k))*(logk + k*log2))
//                             = O(k*r*c + (k*(k*2^k))*k)
//                             = O(k*r*c + k^3*2^k)
// Space: O(|V|) = O(k*2^k)
class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        const vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        // Collect all special locations: start '@', keys 'a'-'z', locks 'A'-'Z'
        unordered_map<char, pair<int, int>> locations;
        for (int r = 0; r < (int)grid.size(); ++r) {
            for (int c = 0; c < (int)grid[r].size(); ++c) {
                char place = grid[r][c];
                if (place != '.' && place != '#') {
                    locations[place] = {r, c};
                }
            }
        }

        // BFS to compute shortest distances from a source special location to other special locations
        auto bfs = [&](char source) {
            unordered_map<char, int> dist;
            auto it = locations.find(source);
            int sr = it->second.first, sc = it->second.second;

            int R = (int)grid.size();
            vector<vector<bool>> visited(R);
            for (int i = 0; i < R; ++i) visited[i] = vector<bool>((int)grid[i].size(), false);

            queue<tuple<int, int, int>> q;
            visited[sr][sc] = true;
            q.emplace(sr, sc, 0);

            while (!q.empty()) {
                auto [r, c, d] = q.front();
                q.pop();
                char cell = grid[r][c];
                if (cell != source && cell != '.') {
                    dist[cell] = d;
                    continue;
                }
                for (const auto& dir : directions) {
                    int nr = r + dir.first;
                    int nc = c + dir.second;
                    if (!(0 <= nr && nr < (int)grid.size())) continue;
                    if (!(0 <= nc && nc < (int)grid[nr].size())) continue;
                    if (grid[nr][nc] != '#' && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.emplace(nr, nc, d + 1);
                    }
                }
            }
            return dist;
        };

        unordered_map<char, unordered_map<char, int>> dists;
        for (const auto& kv : locations) {
            char place = kv.first;
            dists[place] = bfs(place);
        }

        // Dijkstra's algorithm on the state graph
        using State = tuple<int, char, int>; // (distance, place, key_mask)
        priority_queue<State, vector<State>, greater<State>> min_heap;
        unordered_map<char, unordered_map<int, int>> best;

        min_heap.emplace(0, '@', 0);
        best['@'][0] = 0;

        int target_state = 0;
        for (const auto& kv : locations) {
            char ch = kv.first;
            if ('a' <= ch && ch <= 'z') {
                target_state |= (1 << (ch - 'a'));
            }
        }

        while (!min_heap.empty()) {
            auto [cur_d, place, state] = min_heap.top();
            min_heap.pop();
            auto& bmap = best[place];
            auto itb = bmap.find(state);
            if (itb != bmap.end() && itb->second < cur_d) {
                continue;
            }
            if (state == target_state) {
                return cur_d;
            }
            const auto& adj = dists[place];
            for (const auto& p : adj) {
                char dest = p.first;
                int d = p.second;
                int next_state = state;
                if ('a' <= dest && dest <= 'z') {
                    next_state |= (1 << (dest - 'a'));
                } else if ('A' <= dest && dest <= 'Z') {
                    if (!(state & (1 << (dest - 'A')))) {
                        continue;
                    }
                }
                int nd = cur_d + d;
                auto& bdest = best[dest];
                auto it = bdest.find(next_state);
                if (it == bdest.end() || nd < it->second) {
                    bdest[next_state] = nd;
                    min_heap.emplace(nd, dest, next_state);
                }
            }
        }
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<string>> tests;
    tests.push_back(vector<string>{ "@.a" }); // simple linear, one key
    tests.push_back(vector<string>{ "@..aA..b" }); // two keys with a lock
    tests.push_back(vector<string>{ "@#a" }); // unreachable key
    tests.push_back(vector<string>{ "@..aA", "..B#.", "....b" }); // multi-row, multiple keys/locks
    tests.push_back(vector<string>{ "@A..b" }); // lock without its key makes key unreachable
    tests.push_back(vector<string>{ "@..", ".#aA", "..b" }); // jagged rows
    tests.push_back(vector<string>{ "@....", "abcde", "ABCDE", "....." }); // many keys in a row
    tests.push_back(vector<string>{ "@..#..a", "..#....", "##.##.#", "..b.A.." }); // maze with walls and locks
    tests.push_back(vector<string>{ "@Aa" }); // lock blocks the only path to its key
    tests.push_back(vector<string>{ "@." }); // no keys

    Solution sol;
    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& grid : tests) {
            int res = sol.shortestPathAllKeys(grid);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = elapsed_ns / 1e6;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}