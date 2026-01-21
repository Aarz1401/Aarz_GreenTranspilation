#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <limits>
#include <chrono>

using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        int n = static_cast<int>(A.size());
        vector<vector<int>> overlaps(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            const string& x = A[i];
            for (int j = 0; j < n; ++j) {
                const string& y = A[j];
                int minLen = static_cast<int>(min(x.size(), y.size()));
                for (int l = minLen - 1; l >= 0; --l) {
                    if (y.compare(0, l, x, static_cast<int>(x.size()) - l, l) == 0) {
                        overlaps[i][j] = l;
                        break;
                    }
                }
            }
        }

        int totalMasks = 1 << n;
        vector<vector<int>> dp(totalMasks, vector<int>(n, 0));
        vector<vector<int>> prev(totalMasks, vector<int>(n, -1));

        for (int mask = 1; mask < totalMasks; ++mask) {
            for (int bit = 0; bit < n; ++bit) {
                if (((mask >> bit) & 1) == 0) continue;
                int prev_mask = mask ^ (1 << bit);
                for (int i = 0; i < n; ++i) {
                    if (((prev_mask >> i) & 1) == 0) continue;
                    int value = dp[prev_mask][i] + overlaps[i][bit];
                    if (value > dp[mask][bit]) {
                        dp[mask][bit] = value;
                        prev[mask][bit] = i;
                    }
                }
            }
        }

        int fullMask = totalMasks - 1;
        int bestBit = 0;
        for (int b = 1; b < n; ++b) {
            if (dp[fullMask][b] > dp[fullMask][bestBit]) {
                bestBit = b;
            }
        }

        vector<int> words;
        int mask = fullMask;
        int bit = bestBit;
        while (bit != -1) {
            words.push_back(bit);
            int nextMask = mask ^ (1 << bit);
            int nextBit = prev[mask][bit];
            mask = nextMask;
            bit = nextBit;
        }
        reverse(words.begin(), words.end());

        vector<char> inSet(n, 0);
        for (int w : words) inSet[w] = 1;
        for (int i = 0; i < n; ++i) {
            if (!inSet[i]) words.push_back(i);
        }

        string result = A[words[0]];
        for (int i = 1; i < static_cast<int>(words.size()); ++i) {
            int overlap = overlaps[words[i - 1]][words[i]];
            result += A[words[i]].substr(overlap);
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> tests;
    tests.reserve(10);

    // 1. Simple overlap
    tests.push_back({"ab", "bc"});

    // 2. No overlaps
    tests.push_back({"abc", "def", "ghi"});

    // 3. Classic multi-overlap case
    tests.push_back({"catgc", "ctaagt", "gcta", "ttca", "atgcatc"});

    // 4. Contains substrings
    tests.push_back({"abcd", "bc", "c", "d"});

    // 5. Duplicates and repeats
    tests.push_back({"aaa", "aaa", "aa"});

    // 6. Mixed with embedded word
    tests.push_back({"leetc", "code", "leetcode", "etco"});

    // 7. Circular overlaps
    tests.push_back({"abc", "bca", "cab"});

    // 8. Many similar strings
    tests.push_back({"aaaaa", "aaaa", "aaa", "aa", "a"});

    // 9. Longer strings with patterned overlaps
    {
        vector<string> t9;
        string t9a(200, 'a'); t9a += 'b'; t9a += string(200, 'c');
        string t9b(150, 'a'); t9b += "bc"; t9b += string(150, 'c');
        string t9c = string(200, 'c') + "d" + string(100, 'e');
        string t9d = string(100, 'a') + string(100, 'b') + string(100, 'c');
        string t9e = string(50, 'b') + string(200, 'c') + 'd';
        t9.push_back(t9a);
        t9.push_back(t9b);
        t9.push_back(t9c);
        t9.push_back(t9d);
        t9.push_back(t9e);
        tests.push_back(std::move(t9));
    }

    // 10. Mixed genome-like overlaps
    tests.push_back({"gttac", "tacga", "acg", "cgat", "gattt"});

    Solution sol;
    unsigned long long checksum = 0;

    const int iterations = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            string res = sol.shortestSuperstring(tests[i]);
            // Simple rolling checksum to prevent optimization
            checksum ^= static_cast<unsigned long long>(res.size());
            if (!res.empty()) {
                checksum = (checksum * 1315423911ULL) ^ static_cast<unsigned long long>(static_cast<unsigned char>(res.front()));
                checksum = (checksum * 2654435761ULL) ^ static_cast<unsigned long long>(static_cast<unsigned char>(res.back()));
            }
            // Mix in a few characters across the string
            if (res.size() > 4) {
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res[res.size() / 2]));
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res[res.size() / 3]));
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res[res.size() / 4]));
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}