#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <limits>
#include <chrono>

using namespace std;

// Helper to compute positional matches of 6-letter words
static inline int match6(const string& a, const string& b) {
    int cnt = 0;
    for (int i = 0; i < 6; ++i) cnt += (a[i] == b[i]);
    return cnt;
}

// Master API implementation for benchmarking
class Master {
public:
    explicit Master(const string& secret) : secret_(secret), attempts_(0) {}
    int guess(string word) {
        ++attempts_;
        if (secret_.size() == 6 && word.size() == 6) {
            return match6(secret_, word);
        }
        return 0;
    }
    int attempts() const { return attempts_; }
private:
    string secret_;
    int attempts_;
};

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */

class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        const int L = 6;
        const int N = static_cast<int>(wordlist.size());
        vector<vector<int>> H(N, vector<int>(N, 0));
        for (int i = 0; i < N; ++i) {
            H[i][i] = L;
            for (int j = i + 1; j < N; ++j) {
                int m = match(wordlist[i], wordlist[j], L);
                H[i][j] = m;
                H[j][i] = m;
            }
        }

        vector<int> possible(N);
        for (int i = 0; i < N; ++i) possible[i] = i;

        for (int attempt = 0; attempt < 10 && !possible.empty(); ++attempt) {
            int guess = solve(H, possible);
            int n = master.guess(wordlist[guess]);
            if (n == L) return;
            vector<int> next;
            next.reserve(possible.size());
            for (int j : possible) {
                if (H[guess][j] == n) {
                    next.push_back(j);
                }
            }
            possible.swap(next);
        }
    }

private:
    static int match(const string& a, const string& b, int L) {
        int cnt = 0;
        for (int i = 0; i < L; ++i) {
            if (a[i] == b[i]) ++cnt;
        }
        return cnt;
    }

    static int solve(const vector<vector<int>>& H, const vector<int>& possible) {
        int best_guess = -1;
        int min_max_group_size = numeric_limits<int>::max();
        for (int guess : possible) {
            array<int, 7> sizes{};
            sizes.fill(0);
            for (int j : possible) {
                if (j == guess) continue;
                int m = H[guess][j];
                if (m >= 0 && m <= 6) {
                    ++sizes[m];
                }
            }
            int max_group_size = 0;
            for (int s : sizes) max_group_size = max(max_group_size, s);
            if (max_group_size < min_max_group_size) {
                min_max_group_size = max_group_size;
                best_guess = guess;
            }
        }
        return best_guess;
    }
};

// Benchmark test case container
struct TestCase {
    vector<string> words;
    string secret;
};

static vector<TestCase> makeTestCases() {
    vector<TestCase> tcs;
    tcs.reserve(10);

    // 0) Empty wordlist
    tcs.push_back(TestCase{{}, "aaaaaa"});

    // 1) Single element (secret present)
    tcs.push_back(TestCase{{"planet"}, "planet"});

    // 2) Two elements
    tcs.push_back(TestCase{{"absent", "planet"}, "planet"});

    // 3) Clustered similar prefixes
    {
        vector<string> w = {
            "aaaaaa","aaaabb","aaabbb","aabbbb","abbbbb","bbbbbb","abaabb","abbaab","bbaabb"
        };
        tcs.push_back(TestCase{w, "aaabbb"});
    }

    // 4) Typical mixed set
    {
        vector<string> w = {
            "acckzz","ccbazz","eiowzz","abcczz","babbbc","cccbdd","azzzzz","acckza"
        };
        tcs.push_back(TestCase{w, "acckzz"});
    }

    // 5) Rotations and reversals around "abcdef"
    {
        vector<string> w = {
            "abcdef","abcdeg","abcdfe","abcedf","abcfde","acbdef","bacdef",
            "cdefab","defabc","efabcd","fabcde","bcdefa","cabdef","dabcef",
            "aedcbf","badcfe","abdfec","acbedf","abcedg","fedcba"
        };
        // Ensure all are 6 letters (replace any wrong-length entries)
        for (auto& s : w) {
            if (s.size() != 6) s = "abcdef";
        }
        tcs.push_back(TestCase{w, "fedcba"});
    }

    // 6) Fixed first 4 letters with variations on last 2 (4x4 = 16)
    {
        vector<string> w;
        for (char c1 = 'a'; c1 <= 'd'; ++c1) {
            for (char c2 = 'a'; c2 <= 'd'; ++c2) {
                string s = "test  ";
                s[4] = c1;
                s[5] = c2;
                s[0] = 't'; s[1] = 'e'; s[2] = 's'; s[3] = 't';
                w.push_back(s);
            }
        }
        tcs.push_back(TestCase{w, "testcd"});
    }

    // 7) Pseudo-random 50-word set, deterministic LCG
    {
        vector<string> w;
        w.reserve(50);
        uint64_t state = 0x123456789abcdefULL;
        auto next = [&]() {
            state = state * 6364136223846793005ULL + 1ULL;
            return state;
        };
        for (int i = 0; i < 50; ++i) {
            string s(6, 'a');
            for (int j = 0; j < 6; ++j) {
                s[j] = 'a' + static_cast<int>((next() >> 33) % 26);
            }
            w.push_back(s);
        }
        string secret = w.back(); // ensure secret exists
        tcs.push_back(TestCase{w, secret});
    }

    // 8) High Hamming distances: uniform letters a..z
    {
        vector<string> w;
        for (char c = 'a'; c <= 'z'; ++c) {
            w.emplace_back(string(6, c));
        }
        tcs.push_back(TestCase{w, string(6, 'm')});
    }

    // 9) Structured set: "abc" + 3 chars from {a,b,c}
    {
        vector<string> w;
        for (char a = 'a'; a <= 'c'; ++a) {
            for (char b = 'a'; b <= 'c'; ++b) {
                for (char c = 'a'; c <= 'c'; ++c) {
                    string s = "abc   ";
                    s[3] = a; s[4] = b; s[5] = c;
                    w.push_back(s);
                }
            }
        }
        tcs.push_back(TestCase{w, "abccba"});
    }

    // 10th case: Mixed alternation patterns
    {
        vector<string> w = {
            "ababab","bababa","aabbcc","ccbbaa","abcabc","bcabca",
            "cababc","bcaabc","cabbac","abccba","baabcc","ccaabb"
        };
        tcs.push_back(TestCase{w, "abccba"});
    }

    // Ensure exactly 10 by trimming if we accidentally made more
    if (tcs.size() > 10) tcs.resize(10);
    return tcs;
}

int main() {
    vector<TestCase> tests = makeTestCases();

    Solution solver;
    volatile long long checksum = 0; // prevent optimization

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            Master master(tc.secret);
            // Make a modifiable copy since API expects non-const reference
            vector<string> words = tc.words;
            solver.findSecretWord(words, master);
            checksum += master.attempts();
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}