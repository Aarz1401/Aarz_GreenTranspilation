#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <deque>
#include <unordered_set>
#include <algorithm>
#include <utility>
using namespace std;

class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int M = stamp.size(), N = target.size();
        deque<int> q;
        vector<bool> lookup(N, false);
        vector<int> result;
        vector<pair<unordered_set<int>, unordered_set<int>>> A;

        for (int i = 0; i <= N - M; ++i) {
            A.emplace_back();
            auto& made = A.back().first;
            auto& todo = A.back().second;
            for (int j = 0; j < M; ++j) {
                if (stamp[j] == target[i + j]) {
                    made.insert(i + j);
                } else {
                    todo.insert(i + j);
                }
            }
            if (!todo.empty()) continue;
            result.push_back(i);
            for (int m : made) {
                if (lookup[m]) continue;
                q.push_back(m);
                lookup[m] = true;
            }
        }

        while (!q.empty()) {
            int i = q.front(); q.pop_front();
            int start = max(0, i - M + 1);
            int end = min(N - M, i);
            for (int j = start; j <= end; ++j) {
                auto& made = A[j].first;
                auto& todo = A[j].second;
                if (todo.find(i) == todo.end()) continue;
                todo.erase(i);
                if (!todo.empty()) continue;
                result.push_back(j);
                for (int m : made) {
                    if (lookup[m]) continue;
                    q.push_back(m);
                    lookup[m] = true;
                }
            }
        }

        if (all_of(lookup.begin(), lookup.end(), [](bool b){ return b; })) {
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }
};

volatile int sink = 0;

int main() {
    vector<pair<string, string>> tests = {
        {"abca", "aabcaca"},
        {"abc", "ababc"},
        {"a", "aaaaa"},
        {"aa", "aaaa"},
        {"xyz", "xyzxyzxyz"},
        {"aba", "ababa"},
        {"z", "zzzzzz"},
        {"abcde", "abcde"},
        {"abc", "abcabc"},
        {"aba", "abaaba"}
    };

    Solution s;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            auto res = s.movesToStamp(t.first, t.second);
            DoNotOptimize(res);
            //checksum += static_cast<int>(res.size());
            // for (int v : res) {
            //     checksum += v;
            // }
        }
        //sink = checksum;
    }
    return 0;
}