#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include <chrono>

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

int main() {
    vector<string> tests = {
        "3+2*2",
        " 3/2 ",
        " 3+5 / 2 ",
        "(1+(4+5+2)-3)+(6+8)",
        "14-3/2",
        "2*(5+5*2)/3+(6/2+8)",
        "1-(2+3*(4-5))+6/2",
        "((10+20)-(30-40))/5",
        "1000000*3/2",
        " (  7 + (8/  4) * (  3 + 5 )  ) - 6 "
    };

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += solver.calculate(s);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (us): " << elapsed_us << "\n";
    return 0;
}