#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    string generateString(string str1, string str2) {
        auto z_function = [](const string& s) {
            vector<int> z(s.size(), 0);
            int l = 0, r = 0;
            for (int i = 1; i < (int)s.size(); ++i) {
                if (i <= r) {
                    z[i] = min(r - i + 1, z[i - l]);
                }
                while (i + z[i] < (int)s.size() && s[z[i]] == s[i + z[i]]) {
                    ++z[i];
                }
                if (i + z[i] - 1 > r) {
                    l = i;
                    r = i + z[i] - 1;
                }
            }
            return z;
        };

        int n = str1.size(), m = str2.size();
        string candidate(n + m - 1, '*');
        vector<int> z = z_function(str2);
        int prev = -m;
        for (int i = 0; i < n; ++i) {
            char x = str1[i];
            if (x != 'T') {
                continue;
            }
            int diff = i - prev;
            if (diff < m) {
                if (z[diff] == m - diff) {
                    // candidate[prev+m : i+m] = str2[m-diff :]
                    int startCand = prev + m;
                    int startStr2 = m - diff;
                    for (int k = 0; k < diff; ++k) {
                        candidate[startCand + k] = str2[startStr2 + k];
                    }
                } else {
                    return "";
                }
            } else {
                // candidate[i : i+m] = str2
                for (int k = 0; k < m; ++k) {
                    candidate[i + k] = str2[k];
                }
            }
            prev = i;
        }
        string result = str2 + "#" + candidate;
        vector<int> idxs;
        for (int i = m + 1; i < (int)result.size(); ++i) {
            if (result[i] == '*') {
                result[i] = 'a';
                idxs.push_back(i);
            }
        }
        vector<int> z_all = z_function(result);
        deque<int> dq;
        int i = m + 1;
        int j = 0;
        while (i - (m + 1) < n) {
            while (!dq.empty() && dq.front() < i) {
                dq.pop_front();
            }
            while (j < (int)idxs.size() && idxs[j] <= i + (m - 1)) {
                dq.push_back(idxs[j]);
                ++j;
            }
            if (str1[i - (m + 1)] == 'F' && z_all[i] == m) {
                if (dq.empty()) {
                    return "";
                }
                result[dq.back()] = 'b';
                i += m;
            } else {
                ++i;
            }
        }
        return result.substr(m + 1);
    }
};

int main() {
    Solution sol;

    vector<pair<string, string>> tests = {
        {"TFTFTF", "ab"},
        {"FFFFF", "xyz"},
        {"TTTTT", "aaaa"},
        {"TFTFT", "abab"},
        {"FTTFFTTF", "abcabc"},
        {"F", "z"},
        {"T", "z"},
        {"FFTFFTFF", "aba"},
        {"TFFFFT", "aaaaa"},
        {"TFTF", "a"}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            string out = sol.generateString(tc.first, tc.second);
            DoNotOptimize(out);
            // checksum += static_cast<int>(out.size());
            // if (!out.empty()) {
            //     checksum += static_cast<unsigned char>(out.front());
            //     checksum += static_cast<unsigned char>(out.back());
            // }
        }
        //sink = checksum;
    }

    return 0;
}