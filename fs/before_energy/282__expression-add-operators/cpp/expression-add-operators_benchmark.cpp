#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <string>
#include <vector>
#include <chrono>

using namespace std;

// Time:  O(4^n)
// Space: O(n)

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        vector<string> expr;
        const size_t n = num.size();
        if (n == 0) return result;

        long long val = 0;
        string val_str;
        for (size_t i = 0; i < n; ++i) {
            val = val * 10 + (num[i] - '0');
            val_str.push_back(num[i]);
            // Avoid "00...".
            if (val_str.size() > 1 && val_str[0] == '0') break;

            expr.push_back(val_str);
            addOperatorsDFS(num, static_cast<long long>(target), i + 1, 0LL, val, expr, result);
            expr.pop_back();
        }
        return result;
    }

private:
    void addOperatorsDFS(const string& num, long long target, size_t pos,
                         long long operand1, long long operand2,
                         vector<string>& expr, vector<string>& result) {
        if (pos == num.size()) {
            if (operand1 + operand2 == target) {
                string s;
                for (const auto& token : expr) s += token;
                result.emplace_back(move(s));
            }
            return;
        }

        long long val = 0;
        string val_str;
        for (size_t i = pos; i < num.size(); ++i) {
            val = val * 10 + (num[i] - '0');
            val_str.push_back(num[i]);
            // Avoid "00...".
            if (val_str.size() > 1 && val_str[0] == '0') break;

            // Case '+':
            expr.push_back("+" + val_str);
            addOperatorsDFS(num, target, i + 1, operand1 + operand2, val, expr, result);
            expr.pop_back();

            // Case '-':
            expr.push_back("-" + val_str);
            addOperatorsDFS(num, target, i + 1, operand1 + operand2, -val, expr, result);
            expr.pop_back();

            // Case '*':
            expr.push_back("*" + val_str);
            addOperatorsDFS(num, target, i + 1, operand1, operand2 * val, expr, result);
            expr.pop_back();
        }
    }
};

int main() {
    vector<pair<string, int>> tests = {
        {"123", 6},
        {"232", 8},
        {"105", 5},
        {"00", 0},
        {"00", 1},
        {"3456", 21},
        {"9999", 100},
        {"12345", 15},
        {"1005", 5},
        {"214", 9}
    };

    Solution sol;
    size_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            auto res = sol.addOperators(tc.first, tc.second);
            checksum += res.size();
            for (const auto& s : res) {
                checksum += s.size();
                if (!s.empty()) checksum += static_cast<unsigned char>(s[0]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}