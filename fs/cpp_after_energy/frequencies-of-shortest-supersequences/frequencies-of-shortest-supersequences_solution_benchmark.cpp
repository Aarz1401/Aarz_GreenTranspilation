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
#include <numeric>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        vector<vector<int>> adj(26);
        vector<int> char_to_int(26, -1);
        vector<int> int_to_char(26, 0);
        vector<int> indegree;

        auto f = [&](char ch) -> int {
            int x = ch - 'a';
            if (char_to_int[x] == -1) {
                int idx = static_cast<int>(indegree.size());
                int_to_char[idx] = x;
                char_to_int[x] = idx;
                indegree.push_back(0);
            }
            return char_to_int[x];
        };

        for (const auto& w : words) {
            int u = f(w[0]);
            int v = f(w[1]);
            adj[u].push_back(v);
            indegree[v] += 1;
        }

        int k = static_cast<int>(indegree.size());
        int best = INT_MAX;
        vector<vector<int>> best_cnts;

        auto topological_sort = [&](const vector<int>& cnt) {
            int total = accumulate(cnt.begin(), cnt.end(), 0);
            if (total > best) return;

            vector<int> new_cnt = cnt;
            vector<int> new_indegree = indegree;
            vector<char> lookup(k, false);
            vector<int> q;

            for (int u = 0; u < k; ++u) {
                if (new_indegree[u] == 0 || new_cnt[u] == 2) {
                    new_cnt[u] -= 1;
                    lookup[u] = true;
                    q.push_back(u);
                }
            }

            while (!q.empty()) {
                vector<int> new_q;
                for (int u : q) {
                    for (int v : adj[u]) {
                        new_indegree[v] -= 1;
                        if (new_indegree[v] != 0) continue;
                        new_cnt[v] -= 1;
                        if (lookup[v]) continue;
                        lookup[v] = true;
                        new_q.push_back(v);
                    }
                }
                q.swap(new_q);
            }

            for (int x : new_cnt) {
                if (x > 0) return;
            }
            if (total < best) {
                best = total;
                best_cnts.clear();
            }
            best_cnts.push_back(cnt);
        };

        for (int mask = 0; mask < (1 << k); ++mask) {
            vector<int> cnt(k, 1);
            for (int i = 0; i < k; ++i) {
                if (mask & (1 << i)) cnt[i] = 2;
            }
            topological_sort(cnt);
        }

        vector<vector<int>> result;
        for (const auto& cnt : best_cnts) {
            vector<int> new_cnt(26, 0);
            for (int i = 0; i < static_cast<int>(cnt.size()); ++i) {
                new_cnt[int_to_char[i]] = cnt[i];
            }
            result.push_back(move(new_cnt));
        }
        return result;
    }
};

int main() {
    // Define 10 diverse test inputs
    vector<vector<string>> tests;

    // 1) Empty input
    tests.push_back({});

    // 2) Single edge
    tests.push_back({"ab"});

    // 3) Simple chain
    tests.push_back({"ab", "bc", "cd", "de"});

    // 4) Branching from a with further dependencies
    tests.push_back({"ab", "ac", "ad", "be", "cf"});

    // 5) Multiple disconnected components
    tests.push_back({"ab", "cd", "ef", "gh"});

    // 6) Simple cycle
    tests.push_back({"ab", "bc", "ca"});

    // 7) Self-loops
    tests.push_back({"aa", "bb", "cc"});

    // 8) Duplicated edges and a cycle
    tests.push_back({"ab", "ab", "bc", "bc", "cd", "da"});

    // 9) Large 10-cycle
    tests.push_back({"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "ja"});

    // 10) Mixed cycles and branches
    tests.push_back({"az", "zb", "bc", "cd", "de", "ea", "ay", "yx"});

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<string> words = tests[i];
            auto res = sol.supersequences(words);
            // Accumulate checksum based on results
            long long local = 0;
            for (const auto& vec : res) {
                for (int v : vec) local += v;
            }
            // Mix in test index and iteration to avoid trivial constant folding
            checksum += local * static_cast<long long>((i + 1) + (iter & 7));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}