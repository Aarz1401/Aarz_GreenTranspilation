#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>
#include <functional>

class Solution {
public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        // Calculate the minimum left and right parentheses to remove
        auto findMinRemove = [](const std::string& str) -> std::pair<int, int> {
            int left_removed = 0, right_removed = 0;
            for (char c : str) {
                if (c == '(') {
                    ++left_removed;
                } else if (c == ')') {
                    if (!left_removed) {
                        ++right_removed;
                    } else {
                        --left_removed;
                    }
                }
            }
            return {left_removed, right_removed};
        };

        // Check whether s is valid or not.
        auto isValid = [](const std::string& str) -> bool {
            int sum = 0;
            for (char c : str) {
                if (c == '(') {
                    ++sum;
                } else if (c == ')') {
                    --sum;
                }
                if (sum < 0) {
                    return false;
                }
            }
            return sum == 0;
        };

        std::vector<std::string> res;
        std::unordered_set<int> removed;

        auto [left_needed, right_needed] = findMinRemove(s);
        int n = static_cast<int>(s.size());

        std::function<void(int, int, int)> dfs = [&](int start, int left_removed, int right_removed) {
            if (left_removed == 0 && right_removed == 0) {
                std::string tmp;
                tmp.reserve(n);
                for (int i = 0; i < n; ++i) {
                    if (!removed.count(i)) {
                        tmp.push_back(s[i]);
                    }
                }
                if (isValid(tmp)) {
                    res.emplace_back(std::move(tmp));
                }
                return;
            }

            for (int i = start; i < n; ++i) {
                if (right_removed == 0 && left_removed > 0 && s[i] == '(') {
                    if (i == start || s[i] != s[i - 1]) {  // Skip duplicated.
                        removed.insert(i);
                        dfs(i + 1, left_removed - 1, right_removed);
                        removed.erase(i);
                    }
                } else if (right_removed > 0 && s[i] == ')') {
                    if (i == start || s[i] != s[i - 1]) {  // Skip duplicated.
                        removed.insert(i);
                        dfs(i + 1, left_removed, right_removed - 1);
                        removed.erase(i);
                    }
                }
            }
        };

        dfs(0, left_needed, right_needed);
        return res;
    }
};

int main() {
    std::vector<std::string> inputs = {
        "()())()",
        "(a)())()",
        ")(",
        "(((",
        "abcde",
        "((a)(b))",
        "((())",
        "())((()a)",
        "n)()(m)",
        "(((x)))(y))("
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : inputs) {
            auto res = sol.removeInvalidParentheses(s);
            checksum += static_cast<int>(res.size());
            for (const auto& t : res) {
                checksum += static_cast<int>(t.size());
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}