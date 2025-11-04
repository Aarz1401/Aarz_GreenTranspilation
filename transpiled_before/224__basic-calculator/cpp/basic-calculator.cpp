#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

// Time:  O(n)
// Space: O(n)
class Solution {
public:
    int calculate(string s) {
        auto compute = [](vector<long long>& operands, vector<char>& operators) {
            long long right = operands.back(); operands.pop_back();
            long long left = operands.back(); operands.pop_back();
            char op = operators.back(); operators.pop_back();
            long long res = 0;
            switch (op) {
                case '+': res = left + right; break;
                case '-': res = left - right; break;
                case '*': res = left * right; break;
                case '/': res = left / right; break; // C++ truncates toward zero
            }
            operands.push_back(res);
        };

        unordered_map<char, int> precedence{{'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}};
        vector<long long> operands;
        vector<char> operators;
        long long operand = 0;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isspace(static_cast<unsigned char>(c))) {
                continue;
            }
            if (isdigit(static_cast<unsigned char>(c))) {
                operand = operand * 10 + (c - '0');
                if (i == n - 1 || !isdigit(static_cast<unsigned char>(s[i + 1]))) {
                    operands.push_back(operand);
                    operand = 0;
                }
            } else if (c == '(') {
                operators.push_back(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.back() != '(') {
                    compute(operands, operators);
                }
                if (!operators.empty()) {
                    operators.pop_back(); // pop '('
                }
            } else if (precedence.count(c)) {
                while (!operators.empty() && operators.back() != '(' &&
                       precedence[operators.back()] >= precedence[c]) {
                    compute(operands, operators);
                }
                operators.push_back(c);
            }
        }
        while (!operators.empty()) {
            compute(operands, operators);
        }
        return operands.empty() ? 0 : static_cast<int>(operands.back());
    }
};

// Time:  O(n)
// Space: O(n)
class Solution2 {
public:
    int calculate(string s) {
        vector<long long> operands;
        vector<char> operators;
        long long operand = 0;
        long long base = 1;

        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            char c = s[i];
            if (isspace(static_cast<unsigned char>(c))) {
                continue;
            }
            if (isdigit(static_cast<unsigned char>(c))) {
                operand += (c - '0') * base;
                base *= 10;
                if (i == 0 || !isdigit(static_cast<unsigned char>(s[i - 1]))) {
                    operands.push_back(operand);
                    operand = 0;
                    base = 1;
                }
            } else if (c == ')' || c == '+' || c == '-') {
                operators.push_back(c);
            } else if (c == '(') {
                while (!operators.empty() && operators.back() != ')') {
                    compute(operands, operators);
                }
                if (!operators.empty()) {
                    operators.pop_back(); // pop ')'
                }
            }
        }

        while (!operators.empty()) {
            compute(operands, operators);
        }

        return operands.empty() ? 0 : static_cast<int>(operands.back());
    }

private:
    void compute(vector<long long>& operands, vector<char>& operators) {
        long long left = operands.back(); operands.pop_back();
        long long right = operands.back(); operands.pop_back();
        char op = operators.back(); operators.pop_back();
        if (op == '+') {
            operands.push_back(left + right);
        } else if (op == '-') {
            operands.push_back(left - right);
        }
    }
};