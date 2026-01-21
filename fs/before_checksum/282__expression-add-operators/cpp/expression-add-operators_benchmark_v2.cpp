#include <iostream>
#include <string>
#include <vector>
#include <utility>

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
    Solution s;
    vector<pair<string, int>> tests = {
        {"123", 6},
        {"232", 8},
        {"105", 5},
        {"00", 0},
        {"345", 17},
        {"999", -9},
        {"1234", 21},
        {"123", 123},
        {"1111", 4},
        {"246", 12}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            auto res = s.addOperators(t.first, t.second);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}