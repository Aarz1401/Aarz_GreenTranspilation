#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
private:
    static int addSpaces(int i, int spaceCnt, int extraWidth, bool is_last) {
        if (i < spaceCnt) {
            if (is_last) return 1;
            int base = spaceCnt == 0 ? 0 : (extraWidth / spaceCnt);
            int rem = spaceCnt == 0 ? 0 : (extraWidth % spaceCnt);
            return base + (i < rem ? 1 : 0);
        }
        return 0;
    }

    static std::string connect(const std::vector<std::string>& words, int maxWidth, int begin, int end, int length, bool is_last) {
        std::string line;
        int n = end - begin;
        for (int i = 0; i < n; ++i) {
            line += words[begin + i];
            int spaces = addSpaces(i, n - 1, maxWidth - length, is_last);
            if (spaces > 0) line.append(spaces, ' ');
        }
        if (static_cast<int>(line.size()) < maxWidth) {
            line.append(maxWidth - line.size(), ' ');
        }
        return line;
    }

public:
    std::vector<std::string> fullJustify(std::vector<std::string>& words, int maxWidth) {
        std::vector<std::string> res;
        int begin = 0;
        int length = 0;
        for (int i = 0; i < static_cast<int>(words.size()); ++i) {
            if (length + static_cast<int>(words[i].size()) + (i - begin) > maxWidth) {
                res.emplace_back(connect(words, maxWidth, begin, i, length, false));
                begin = i;
                length = 0;
            }
            length += static_cast<int>(words[i].size());
        }
        res.emplace_back(connect(words, maxWidth, begin, static_cast<int>(words.size()), length, true));
        return res;
    }
};