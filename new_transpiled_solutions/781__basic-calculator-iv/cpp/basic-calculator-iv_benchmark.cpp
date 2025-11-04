#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <functional>

using namespace std;

class Poly {
public:
    map<vector<string>, long long> terms;

    Poly() {}

    explicit Poly(const string& expr) {
        if (expr.empty()) return;
        bool is_num = true;
        for (char ch : expr) {
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                is_num = false;
                break;
            }
        }
        if (is_num) {
            long long val = stoll(expr);
            if (val != 0) {
                terms[vector<string>()] += val;
            }
        } else {
            terms[vector<string>{expr}] += 1;
        }
    }

    static void clear(map<vector<string>, long long>& m) {
        for (auto it = m.begin(); it != m.end(); ) {
            if (it->second == 0) {
                it = m.erase(it);
            } else {
                ++it;
            }
        }
    }

    friend Poly operator+(const Poly& a, const Poly& b) {
        Poly res;
        res.terms = a.terms;
        for (const auto& kv : b.terms) {
            res.terms[kv.first] += kv.second;
        }
        clear(res.terms);
        return res;
    }

    friend Poly operator-(const Poly& a, const Poly& b) {
        Poly res;
        res.terms = a.terms;
        for (const auto& kv : b.terms) {
            res.terms[kv.first] -= kv.second;
        }
        clear(res.terms);
        return res;
    }

    static vector<string> mergeKeys(const vector<string>& k1, const vector<string>& k2) {
        vector<string> result;
        result.reserve(k1.size() + k2.size());
        size_t i = 0, j = 0;
        while (i < k1.size() || j < k2.size()) {
            if (j == k2.size() || (i < k1.size() && k1[i] < k2[j])) {
                result.push_back(k1[i++]);
            } else {
                result.push_back(k2[j++]);
            }
        }
        return result;
    }

    friend Poly operator*(const Poly& a, const Poly& b) {
        Poly res;
        for (const auto& kv1 : a.terms) {
            for (const auto& kv2 : b.terms) {
                vector<string> key = mergeKeys(kv1.first, kv2.first);
                res.terms[key] += kv1.second * kv2.second;
            }
        }
        clear(res.terms);
        return res;
    }

    Poly eval(const unordered_map<string, long long>& lookup) const {
        Poly res;
        for (const auto& kv : terms) {
            const vector<string>& polies = kv.first;
            long long c = kv.second;
            vector<string> key;
            key.reserve(polies.size());
            for (const string& var : polies) {
                auto it = lookup.find(var);
                if (it != lookup.end()) {
                    c *= it->second;
                } else {
                    key.push_back(var);
                }
            }
            res.terms[key] += c;
        }
        clear(res.terms);
        return res;
    }

    vector<string> to_list() const {
        vector<pair<vector<string>, long long>> items;
        items.reserve(terms.size());
        for (const auto& kv : terms) {
            items.emplace_back(kv.first, kv.second);
        }
        sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
            if (a.first.size() != b.first.size()) return a.first.size() > b.first.size();
            return a.first < b.first;
        });
        vector<string> res;
        res.reserve(items.size());
        for (const auto& it : items) {
            string s = to_string(it.second);
            for (const string& var : it.first) {
                s.push_back('*');
                s += var;
            }
            res.push_back(s);
        }
        if (res.empty()) {
            return vector<string>{ "0" };
        }
        return res;
    }
};

class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        auto precedence = [](char c) -> int {
            if (c == '+' || c == '-') return 0;
            if (c == '*') return 1;
            return -1;
        };

        auto compute = [](vector<Poly>& operands, vector<char>& operators) {
            Poly right = operands.back(); operands.pop_back();
            Poly left = operands.back(); operands.pop_back();
            char op = operators.back(); operators.pop_back();
            if (op == '+') {
                operands.push_back(left + right);
            } else if (op == '-') {
                operands.push_back(left - right);
            } else if (op == '*') {
                operands.push_back(left * right);
            }
        };

        auto parse = [&](const string& s) -> Poly {
            vector<Poly> operands;
            vector<char> operators;
            string token;
            int n = static_cast<int>(s.size());
            for (int i = 0; i < n; ++i) {
                char ch = s[i];
                if (std::isspace(static_cast<unsigned char>(ch))) continue;
                if (std::isalnum(static_cast<unsigned char>(ch))) {
                    token.push_back(ch);
                    bool endToken = (i == n - 1) || !std::isalnum(static_cast<unsigned char>(s[i + 1]));
                    if (endToken) {
                        operands.emplace_back(Poly(token));
                        token.clear();
                    }
                } else if (ch == '(') {
                    operators.push_back(ch);
                } else if (ch == ')') {
                    while (!operators.empty() && operators.back() != '(') {
                        compute(operands, operators);
                    }
                    if (!operators.empty() && operators.back() == '(') operators.pop_back();
                } else if (ch == '+' || ch == '-' || ch == '*') {
                    while (!operators.empty() && operators.back() != '(' &&
                           precedence(operators.back()) >= precedence(ch)) {
                        compute(operands, operators);
                    }
                    operators.push_back(ch);
                }
            }
            while (!operators.empty()) {
                compute(operands, operators);
            }
            if (!operands.empty()) return operands.back();
            return Poly();
        };

        unordered_map<string, long long> lookup;
        for (size_t i = 0; i < evalvars.size(); ++i) {
            lookup[evalvars[i]] = static_cast<long long>(evalints[i]);
        }
        Poly result = parse(expression).eval(lookup);
        return result.to_list();
    }
};

struct TestCase {
    string expr;
    vector<string> vars;
    vector<int> vals;
};

int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    tests.push_back({"e + 8 - a + 5", {"e"}, {1}});
    tests.push_back({"e - 8 + temperature - pressure", {"e", "temperature"}, {1, 12}});
    tests.push_back({"(e + 8) * (e - 8)", {}, {}});
    tests.push_back({"7 - 7", {}, {}});
    tests.push_back({"a * b * c + b * a * c * 2", {}, {}});
    tests.push_back({"((a + b) * (c + d) * (e + f))", {"a","b","c","d","e","f"}, {1,2,3,4,5,6}});
    tests.push_back({"a - b + c - d + e - f + g - h + i - j", {"a","b","c","d","e"}, {10,9,8,7,6}});
    tests.push_back({"a*b*b*b + b*a*a + 3*a*b", {"a","b"}, {2,3}});
    tests.push_back({"42", {"x"}, {1}});
    tests.push_back({"x*y + y*z + z*x + x*x*y", {"x","z"}, {2,5}});

    Solution solver;

    using chrono::high_resolution_clock;
    using chrono::duration;
    using chrono::duration_cast;
    auto start = high_resolution_clock::now();

    uint64_t checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<string> vars = tc.vars;
            vector<int> vals = tc.vals;
            vector<string> res = solver.basicCalculatorIV(tc.expr, vars, vals);
            for (const auto& s : res) {
                checksum ^= (static_cast<uint64_t>(std::hash<string>{}(s)) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2));
            }
            checksum += res.size();
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ms = duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}