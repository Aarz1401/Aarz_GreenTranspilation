#include <string>
#include <algorithm>
#include <cstdlib>

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