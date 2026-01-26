#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>

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

struct Case {
    std::vector<std::string> words;
    int width;
};

int main() {
    std::vector<Case> tests = {
        {{"Hello"}, 5},
        {{"Hi"}, 4},
        {{"This","is","an","example","of","text","justify"}, 16},
        {{"a","b","c"}, 6},
        {{"lorem","ipsum","dolor","sit","amet","consect","adipis"}, 14},
        {{"a","group","of","words","to","fill","the","last","line"}, 12},
        {{"aa","bb","cc","dd"}, 11},
        {{"a","b","c","d"}, 1},
        {{"longword","tiny","mid","size","words","here"}, 10},
        {{"abc","def","ghi"}, 11}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            std::vector<std::string> words = tc.words;
            std::vector<std::string> res = sol.fullJustify(words, tc.width);
            DoNotOptimize(res); 
            // for (const auto& line : res) {
            //     checksum += static_cast<int>(line.size());
            //     checksum += static_cast<unsigned char>(line[0]);
            //     checksum += static_cast<unsigned char>(line[line.size() - 1]);
            // }
        }
        //sink = checksum;
    }

    return 0;
}