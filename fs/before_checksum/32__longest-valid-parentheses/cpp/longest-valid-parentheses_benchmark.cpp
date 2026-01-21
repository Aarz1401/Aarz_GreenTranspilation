#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <chrono>

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
    // Generate 10 diverse test inputs
    std::vector<std::string> inputs;
    inputs.reserve(10);

    inputs.push_back("");                        // 1. Empty
    inputs.push_back(std::string(10, '('));      // 2. All '('
    inputs.push_back(std::string(10, ')'));      // 3. All ')'
    inputs.push_back("()");                      // 4. Simple valid
    inputs.push_back("(())");                    // 5. Nested valid
    inputs.push_back(")()())");                  // 6. Mixed, typical case
    inputs.push_back("(()");                     // 7. Unbalanced opening
    inputs.push_back("())(())");                 // 8. Split segments
    inputs.push_back(std::string(100, '(') + std::string(100, ')')); // 9. Long nested
    { // 10. Alternating pattern "()" repeated
        std::string alt;
        alt.reserve(300);
        for (int i = 0; i < 300; ++i) {
            alt += (i % 2 == 0) ? '(' : ')';
        }
        inputs.push_back(std::move(alt));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : inputs) {
            int res = sol.longestValidParentheses(s);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}