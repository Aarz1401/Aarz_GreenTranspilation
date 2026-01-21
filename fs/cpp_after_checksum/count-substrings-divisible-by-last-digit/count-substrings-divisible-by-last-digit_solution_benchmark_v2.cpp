#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    long long countSubstrings(string s) {
        int n = static_cast<int>(s.size());
        long long result = 0;

        // digit 1, 2, 5
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1' || s[i] == '2' || s[i] == '5') {
                result += static_cast<long long>(i) + 1;
            }
        }

        // digit 3, 6
        {
            int remain = 0;
            vector<long long> cnt(3, 0);
            cnt[0] = 1;
            for (int i = 0; i < n; ++i) {
                remain = (remain + (s[i] - '0')) % 3;
                if (s[i] == '3' || s[i] == '6') {
                    result += cnt[remain];
                }
                cnt[remain] += 1;
            }
        }

        // digit 9
        {
            int remain = 0;
            vector<long long> cnt(9, 0);
            cnt[0] = 1;
            for (int i = 0; i < n; ++i) {
                remain = (remain + (s[i] - '0')) % 9;
                if (s[i] == '9') {
                    result += cnt[remain];
                }
                cnt[remain] += 1;
            }
        }

        // digit 4
        for (int i = 0; i < n; ++i) {
            if (s[i] == '4') {
                result += 1;
                if (i - 1 >= 0) {
                    int val2 = (s[i - 1] - '0') * 10 + (s[i] - '0');
                    if (val2 % 4 == 0) {
                        result += i;
                    }
                }
            }
        }

        // digit 8
        for (int i = 0; i < n; ++i) {
            if (s[i] == '8') {
                result += 1;
                if (i - 1 >= 0) {
                    int val2 = (s[i - 1] - '0') * 10 + (s[i] - '0');
                    if (val2 % 8 == 0) {
                        result += 1;
                    }
                }
                if (i - 2 >= 0) {
                    int val3 = (s[i - 2] - '0') * 100 + (s[i - 1] - '0') * 10 + (s[i] - '0');
                    if (val3 % 8 == 0) {
                        result += i - 1;
                    }
                }
            }
        }

        // digit 7
        {
            int base = 1;
            int remain = 0;
            vector<long long> cnt(7, 0);
            for (int i = 0; i < n; ++i) {
                int pos = n - 1 - i;
                int d = s[pos] - '0';
                remain = (remain + (base * d) % 7) % 7;
                result += cnt[remain];
                if (s[pos] == '7') {
                    result += 1;
                    cnt[remain] += 1;
                }
                base = (base * 10) % 7;
            }
        }

        return result;
    }
};

int main() {
    vector<string> tests = {
        "1",
        "0",
        "999",
        "36",
        "4444",
        "888",
        "77777",
        "1234567890",
        "5050505050",
        "3141592653589793238462643383279"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += static_cast<int>(sol.countSubstrings(s));
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}