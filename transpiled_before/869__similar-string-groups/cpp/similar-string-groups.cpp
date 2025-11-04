#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Time:  O(n^2 * l) ~ O(n * l^4)
// Space: O(n) ~ O(n * l^3)

class UnionFind {
public:
    explicit UnionFind(int n) : parent(n), __size(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find_set(int x) {
        if (parent[x] != x) {
            parent[x] = find_set(parent[x]);  // path compression
        }
        return parent[x];
    }

    bool union_set(int x, int y) {
        int x_root = find_set(x);
        int y_root = find_set(y);
        if (x_root == y_root) return false;
        if (x_root < y_root) parent[x_root] = y_root;
        else parent[y_root] = x_root;
        --__size;
        return true;
    }

    int size() const {
        return __size;
    }

private:
    vector<int> parent;
    int __size;
};

class Solution {
public:
    int numSimilarGroups(vector<string>& A) {
        auto isSimilar = [](const string& a, const string& b) -> bool {
            int diff = 0;
            for (size_t i = 0; i < a.size(); ++i) {
                if (a[i] != b[i]) {
                    ++diff;
                    if (diff > 2) return false;
                }
            }
            return diff == 2;
        };

        int N = static_cast<int>(A.size());
        if (N == 0) return 0;
        int L = static_cast<int>(A[0].size());
        UnionFind union_find(N);

        if (static_cast<long long>(N) < 1LL * L * L) {
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    if (isSimilar(A[i], A[j])) {
                        union_find.union_set(i, j);
                    }
                }
            }
        } else {
            unordered_map<string, vector<int>> buckets;
            unordered_set<string> lookup;
            for (int i = 0; i < N; ++i) {
                string word = A[i];
                if (!lookup.count(A[i])) {
                    buckets[A[i]].push_back(i);
                    lookup.insert(A[i]);
                }
                for (int j1 = 0; j1 < L; ++j1) {
                    for (int j2 = j1 + 1; j2 < L; ++j2) {
                        swap(word[j1], word[j2]);
                        buckets[word].push_back(i);
                        swap(word[j1], word[j2]);
                    }
                }
            }
            for (const string& word : A) {  // Time:  O(n * l^4)
                auto it = buckets.find(word);
                if (it == buckets.end()) continue;
                const vector<int>& idxs = it->second;
                for (size_t p = 0; p < idxs.size(); ++p) {
                    for (size_t q = p + 1; q < idxs.size(); ++q) {
                        union_find.union_set(idxs[p], idxs[q]);
                    }
                }
            }
        }
        return union_find.size();
    }
};