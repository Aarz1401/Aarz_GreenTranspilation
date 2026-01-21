#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <chrono>

class Solution {
public:
    int evaluate(std::string expression) {
        std::vector<std::string> tokens(1, "");
        std::unordered_map<std::string, std::string> lookup;
        std::vector<std::pair<std::vector<std::string>, std::unordered_map<std::string, std::string>>> stk;

        for (char c : expression) {
            if (c == '(') {
                if (!tokens.empty() && tokens[0] == "let") {
                    // Apply previous let assignments before new scope
                    evalTokens(tokens, lookup);
                }
                stk.emplace_back(tokens, lookup);
                tokens.assign(1, "");
            } else if (c == ' ') {
                tokens.emplace_back("");
            } else if (c == ')') {
                std::string val = evalTokens(tokens, lookup);
                auto top = std::move(stk.back());
                stk.pop_back();
                tokens = std::move(top.first);
                lookup = std::move(top.second);
                if (tokens.empty()) tokens.emplace_back("");
                tokens.back() += val;
            } else {
                tokens.back().push_back(c);
            }
        }
        return std::stoi(tokens[0]);
    }

private:
    static std::string getval(const std::unordered_map<std::string, std::string>& lookup, const std::string& x) {
        auto it = lookup.find(x);
        return (it != lookup.end()) ? it->second : x;
    }

    static std::string evalTokens(std::vector<std::string>& tokens, std::unordered_map<std::string, std::string>& lookup) {
        if (!tokens.empty() && (tokens[0] == "add" || tokens[0] == "mult")) {
            std::string v1 = getval(lookup, tokens[1]);
            std::string v2 = getval(lookup, tokens[2]);
            int a = std::stoi(v1);
            int b = std::stoi(v2);
            long long res = (tokens[0] == "add") ? static_cast<long long>(a) + b : static_cast<long long>(a) * b;
            return std::to_string(res);
        }
        // let or general evaluation
        for (size_t i = 1; i + 1 < tokens.size(); i += 2) {
            if (!tokens[i + 1].empty()) {
                lookup[tokens[i]] = getval(lookup, tokens[i + 1]);
            }
        }
        return getval(lookup, tokens.back());
    }
};

int main() {
    std::vector<std::string> tests = {
        "(add 1 2)",
        "(mult 3 4)",
        "(add 1 (mult 2 3))",
        "(let x 2 (add x 3))",
        "(let x 2 (let y (mult x 5) (add y x)))",
        "(let x 1 (let x 2 (add x x)))",
        "(let x 5 (add (let x 3 x) x))",
        "(let x 1 y 2 z 3 (add x (add y z)))",
        "(add -3 (mult -2 4))",
        "(let x 2 x (add x 3) x (mult x 2) x)"
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& expr : tests) {
            checksum += sol.evaluate(expr);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}