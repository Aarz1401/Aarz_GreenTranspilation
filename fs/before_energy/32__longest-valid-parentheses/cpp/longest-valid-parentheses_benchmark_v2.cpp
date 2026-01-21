#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>

class Solution {
public:
    // Time:  O(n)
    // Space: O(1)
    int longestValidParentheses(const std::string& s) {
        auto length = [&](int start, char c, int begin, int end, int step) {
            int depth = 0, longest = 0;
            for (int i = begin; i != end; i += step) {
                if (s[i] == c) {
                    ++depth;
                } else {
                    --depth;
                    if (depth < 0) {
                        start = i;
                        depth = 0;
                    } else if (depth == 0) {
                        longest = std::max(longest, std::abs(i - start));
                    }
                }
            }
            return longest;
        };

        int n = static_cast<int>(s.size());
        return std::max(
            length(-1, '(', 0, n, 1),
            length(n,  ')', n - 1, -1, -1)
        );
    }
};

int main() {
    std::vector<std::string> tests = {
        "()",
        ")()())",
        "()(()",
        "((()))",
        "()()()",
        "(((((",
        "))))))",
        "(()())",
        "())((())",
        ")(()())(()())"
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // int checksum = 0;
        for (const auto& s : tests) {
            int r = sol.longestValidParentheses(s);
            DoNotOptimize(r);
        }
        // sink = checksum;
    }
    return 0;
}