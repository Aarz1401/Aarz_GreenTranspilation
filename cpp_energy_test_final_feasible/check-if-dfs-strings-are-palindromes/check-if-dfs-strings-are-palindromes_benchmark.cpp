#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <chrono>
using namespace std;

class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int v = 1; v < n; ++v) {
            adj[parent[v]].push_back(v);
        }

        // Iterative DFS to build postorder string 'curr' and lookup intervals [left, right]
        int cnt = 0;
        vector<char> curr;
        curr.reserve(n);
        vector<pair<int, int>> lookup(n, {-1, -1});

        struct Frame {
            int step;
            int u;
            int left;
        };
        vector<Frame> stk;
        stk.push_back({1, 0, 0});
        while (!stk.empty()) {
            Frame f = stk.back();
            stk.pop_back();
            if (f.step == 1) {
                int u = f.u;
                stk.push_back({2, u, cnt});
                // push children in reverse to process in original order
                for (int i = (int)adj[u].size() - 1; i >= 0; --i) {
                    stk.push_back({1, adj[u][i], 0});
                }
            } else { // step 2
                int u = f.u;
                int left = f.left;
                curr.push_back(s[u]);
                lookup[u] = {left, cnt};
                ++cnt;
            }
        }

        // Manacher's algorithm on curr
        auto manacher = [](const vector<char>& arr) -> vector<int> {
            string T;
            T.reserve(2 * arr.size() + 3);
            T.push_back('^');
            T.push_back('#');
            for (char c : arr) {
                T.push_back(c);
                T.push_back('#');
            }
            T.push_back('$');

            int m = T.size();
            vector<int> P(m, 0);
            int C = 0, R = 0;
            for (int i = 1; i < m - 1; ++i) {
                int i_mirror = 2 * C - i;
                if (R > i) {
                    P[i] = min(R - i, P[i_mirror]);
                }
                while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                    ++P[i];
                }
                if (i + P[i] > R) {
                    C = i;
                    R = i + P[i];
                }
            }
            return P;
        };

        vector<int> P = manacher(curr);

        vector<bool> ans(n, false);
        for (int u = 0; u < n; ++u) {
            int left = lookup[u].first;
            int right = lookup[u].second;
            int center = (2 * (left + 1) + 2 * (right + 1)) / 2;
            ans[u] = (P[center] >= right - left + 1);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<int>> parents;
    vector<string> strings;

    // 1) Single node
    parents.push_back({0});
    strings.push_back("a");

    // 2) Root with one child (star of size 2)
    parents.push_back({0, 0});
    strings.push_back("ab");

    // 3) Chain of length 3
    parents.push_back({0, 0, 1}); // 0->1->2
    strings.push_back("aba");

    // 4) Star with 3 children
    parents.push_back({0, 0, 0, 0});
    strings.push_back("abba");

    // 5) Chain of length 5 (palindromic)
    parents.push_back({0, 0, 1, 2, 3});
    strings.push_back("abcba");

    // 6) Balanced-ish size 6, choose chars so postorder is palindrome
    // Tree: 0->{1,2}, 1->{3,4}, 2->{5}
    parents.push_back({0, 0, 0, 1, 1, 2});
    // Postorder sequence = [s3, s4, s1, s5, s2, s0] -> a b c c b a
    strings.push_back("acbabc"); // indices: [0]='a',[1]='c',[2]='b',[3]='a',[4]='b',[5]='c'

    // 7) 8-node with all same chars
    // Tree: 0->{1,2}, 1->{3,4}, 2->{5,6}, 3->{7}
    parents.push_back({0, 0, 0, 1, 1, 2, 2, 3});
    strings.push_back("aaaaaaaa");

    // 8) Chain size 7 with alternating characters (non-palindromic)
    parents.push_back({0, 0, 1, 2, 3, 4, 5});
    strings.push_back("abababc");

    // 9) 9-node mixed branching
    // Tree: 0->{1,2,3}, 1->{4,5}, 2->{6,7}, 3->{8}
    parents.push_back({0, 0, 0, 0, 1, 1, 2, 2, 3});
    strings.push_back("abcabcabc");

    // 10) Star size 10 (root + 9 children) with children forming a palindrome
    parents.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    strings.push_back("xabacdcaba"); // s[1..9] is a palindrome, root char 'x'

    // Sanity: ensure sizes match
    for (size_t i = 0; i < parents.size(); ++i) {
        if (parents[i].size() != strings[i].size()) {
            cerr << "Mismatched test input sizes at index " << i << "\n";
            return 1;
        }
    }

    Solution sol;

    unsigned long long totalTrue = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;


    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < parents.size(); ++t) {
            auto ans = sol.findAnswer(parents[t], strings[t]);
            for (bool b : ans) totalTrue += b ? 1ULL : 0ULL;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;

    // Print checksum and time to avoid optimization and to report timing
    cout << "Checksum (total palindromic subtrees across runs): " << totalTrue << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}
