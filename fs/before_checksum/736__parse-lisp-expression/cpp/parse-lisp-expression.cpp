#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

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