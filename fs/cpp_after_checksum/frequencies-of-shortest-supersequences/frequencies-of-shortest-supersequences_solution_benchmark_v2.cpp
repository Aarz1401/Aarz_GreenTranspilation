#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <climits>
#include <utility>
using namespace std;

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
    vector<vector<string>> tests = {
        {"ab","bc","cd"},
        {"ab","cd"},
        {"ab","ac","bd","cd"},
        {"ab","ac","bd"},
        {"az"},
        {"ab","ac","ad","ae","af"},
        {"ab","bc","bd","de","cf"},
        {"ab","bc","de","ef","gh"},
        {"ab","bc","ce","ad","df"},
        {"ab","bc","cd","de","ef","fg","gh"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            auto res = sol.supersequences(tests[i]);
            checksum += static_cast<int>(res.size());
            for (const auto& v : res) {
                for (int x : v) checksum += x;
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}