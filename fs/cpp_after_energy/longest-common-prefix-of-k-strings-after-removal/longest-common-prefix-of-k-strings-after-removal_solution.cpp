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
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        int n = words.size();
        vector<int> idxs(n);
        iota(idxs.begin(), idxs.end(), 0);
        sort(idxs.begin(), idxs.end(), [&](int a, int b) {
            return words[a] < words[b];
        });

        auto lcp_for_k = [&](int kk) -> vector<int> {
            vector<int> lcp(n, 0);
            int upto = n - (kk - 1);
            if (upto < 0) upto = 0;
            for (int i = 0; i < upto; ++i) {
                const string& left = words[idxs[i]];
                const string& right = words[idxs[i + kk - 1]];
                int l = static_cast<int>(min(left.size(), right.size()));
                int j = 0;
                while (j < l && left[j] == right[j]) {
                    ++j;
                }
                lcp[i] = j;
            }
            return lcp;
        };

        vector<int> lcp = lcp_for_k(k);

        vector<int> prefix(n, 0);
        if (n > 0) {
            prefix[0] = lcp[0];
            for (int i = 0; i + 1 < n; ++i) {
                prefix[i + 1] = max(prefix[i], lcp[i + 1]);
            }
        }

        vector<int> suffix(n, 0);
        if (n > 0) {
            suffix[n - 1] = lcp[n - 1];
            for (int i = n - 2; i >= 0; --i) {
                suffix[i] = max(suffix[i + 1], lcp[i]);
            }
        }

        vector<int> res(n, 0);
        vector<int> lcp_k1 = lcp_for_k(k + 1);
        int mx = 0;
        if (!lcp_k1.empty()) {
            mx = *max_element(lcp_k1.begin(), lcp_k1.end());
        }

        for (int i = 0; i < n; ++i) {
            int origIdx = idxs[i];
            int mx1 = (i - k >= 0) ? prefix[i - k] : 0;
            int mx2 = (i + 1 < n) ? suffix[i + 1] : 0;
            res[origIdx] = max({mx, mx1, mx2});
        }

        return res;
    }
};
