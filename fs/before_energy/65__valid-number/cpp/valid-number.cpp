#include <string>
#include <vector>
#include <cctype>

class Solution {
public:
    // Time:  O(n)
    // Space: O(1)
    enum InputType {
        INVALID  = 0,
        SPACE    = 1,
        SIGN     = 2,
        DIGIT    = 3,
        DOT      = 4,
        EXPONENT = 5
    };

    // regular expression: "^\s*[\+-]?((\d+(\.\d*)?)|\.\d+)([eE][\+-]?\d+)?\s*$"
    // automata: http://images.cnitblog.com/i/627993/201405/012016243309923.png
    bool isNumber(std::string s) {
        const std::vector<std::vector<int>> transition_table = {
            {-1,  0,  3,  1,  2, -1},  // state 0
            {-1,  8, -1,  1,  4,  5},  // state 1
            {-1, -1, -1,  4, -1, -1},  // state 2
            {-1, -1, -1,  1,  2, -1},  // state 3
            {-1,  8, -1,  4, -1,  5},  // state 4
            {-1, -1,  6,  7, -1, -1},  // state 5
            {-1, -1, -1,  7, -1, -1},  // state 6
            {-1,  8, -1,  7, -1, -1},  // state 7
            {-1,  8, -1, -1, -1, -1}   // state 8
        };

        int state = 0;
        for (char c : s) {
            InputType inputType = INVALID;
            unsigned char uc = static_cast<unsigned char>(c);
            if (std::isspace(uc)) {
                inputType = SPACE;
            } else if (c == '+' || c == '-') {
                inputType = SIGN;
            } else if (std::isdigit(uc)) {
                inputType = DIGIT;
            } else if (c == '.') {
                inputType = DOT;
            } else if (c == 'e' || c == 'E') {
                inputType = EXPONENT;
            }

            state = transition_table[state][static_cast<int>(inputType)];
            if (state == -1) {
                return false;
            }
        }

        return state == 1 || state == 4 || state == 7 || state == 8;
    }
};