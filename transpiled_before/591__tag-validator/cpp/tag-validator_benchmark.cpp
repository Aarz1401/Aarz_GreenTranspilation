#include <string>
#include <utility>

class Solution {
public:
    bool isValid(std::string code) {
        auto res = validTag(code, 0);
        return res.first && res.second == static_cast<int>(code.size());
    }

private:
    std::pair<bool, int> validText(const std::string& s, int i) {
        int j = i;
        std::size_t pos = s.find('<', static_cast<std::size_t>(i));
        int ni = (pos == std::string::npos) ? static_cast<int>(s.size()) : static_cast<int>(pos);
        return {ni != j, ni};
    }

    std::pair<bool, int> validCData(const std::string& s, int i) {
        const std::string start = "<![CDATA[";
        const std::string end = "]]>";
        if (i < 0 || i + static_cast<int>(start.size()) > static_cast<int>(s.size())) {
            return {false, i};
        }
        if (s.compare(static_cast<std::size_t>(i), start.size(), start) != 0) {
            return {false, i};
        }
        std::size_t j = s.find(end, static_cast<std::size_t>(i));
        if (j == std::string::npos) {
            return {false, i};
        }
        return {true, static_cast<int>(j + end.size())};
    }

    std::pair<std::string, int> parseTagName(const std::string& s, int i) {
        if (i < 0 || i >= static_cast<int>(s.size()) || s[i] != '<') {
            return {"", i};
        }
        std::size_t j = s.find('>', static_cast<std::size_t>(i));
        if (j == std::string::npos) {
            return {"", i};
        }
        int len = static_cast<int>(j) - i - 1;
        if (len < 1 || len > 9) {
            return {"", i};
        }
        std::string tag = s.substr(static_cast<std::size_t>(i + 1), static_cast<std::size_t>(len));
        for (char c : tag) {
            if (c < 'A' || c > 'Z') {
                return {"", i};
            }
        }
        return {tag, static_cast<int>(j) + 1};
    }

    int parseContent(const std::string& s, int i) {
        while (i < static_cast<int>(s.size())) {
            auto t1 = validText(s, i);
            if (t1.first) {
                i = t1.second;
                continue;
            }
            auto t2 = validCData(s, i);
            if (t2.first) {
                i = t2.second;
                continue;
            }
            auto t3 = validTag(s, i);
            if (t3.first) {
                i = t3.second;
                continue;
            }
            break;
        }
        return i;
    }

    std::pair<bool, int> validTag(const std::string& s, int i) {
        auto p = parseTagName(s, i);
        const std::string& tag = p.first;
        if (tag.empty()) {
            return {false, i};
        }
        int j = parseContent(s, p.second);
        std::string closing = "</" + tag + ">";
        if (j + static_cast<int>(closing.size()) > static_cast<int>(s.size())) {
            return {false, i};
        }
        if (s.compare(static_cast<std::size_t>(j), closing.size(), closing) != 0) {
            return {false, i};
        }
        return {true, j + static_cast<int>(closing.size())};
    }
};

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

int main() {
    std::vector<std::string> tests = {
        "<A>TEXT</A>",
        "<A><B><![CDATA[<C>not parsed</C>]]></B></A>",
        "<ABC><D>E</D><F><![CDATA[123]]>G</F></ABC>",
        "TEXT<A></A>",
        "<Aaa></Aaa>",
        "<A><B></A></B>",
        "<ABCDEFGHIJ></ABCDEFGHIJ>",
        "<A><B></B></A",
        "<A><![CDATA[unfinished</A>",
        "<A>t1<B>t2</B>t3</A>"
    };

    Solution sol;

    std::uint64_t checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (std::size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.isValid(tests[i]);
            checksum += res ? (static_cast<std::uint64_t>(tests[i].size()) + i + static_cast<std::uint64_t>(iter))
                            : (static_cast<std::uint64_t>((tests[i].size() ^ iter) + i + 1));
        }
    }

    auto end = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed.count() << "\n";
    return 0;
}