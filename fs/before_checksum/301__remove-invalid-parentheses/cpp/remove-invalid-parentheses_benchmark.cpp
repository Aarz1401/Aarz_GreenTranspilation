#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>
#include <functional>
#include <chrono>
#include <cstdint>

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
    std::vector<std::string> test_inputs = {
        "()",
        ")(",
        "(a)())()",
        "(()",
        "())())",
        "(((k)))",
        "(a(b(c)d)e)f)",
        "",
        "abc",
        "((())())(()"
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : test_inputs) {
            auto out = sol.removeInvalidParentheses(s);
            checksum += static_cast<unsigned long long>(out.size());
            for (const auto& t : out) {
                // FNV-1a hash to incorporate content into checksum
                unsigned long long h = 1469598103934665603ull;
                for (unsigned char c : t) {
                    h ^= c;
                    h *= 1099511628211ull;
                }
                // mix into checksum
                checksum ^= h + 0x9e3779b97f4a7c15ull + (checksum << 6) + (checksum >> 2);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}