int main() {
    // Define 10 diverse test inputs
    std::vector<std::pair<std::string, std::vector<std::string>>> tests;
    tests.push_back({"catsanddog", {"cat","cats","and","sand","dog"}});
    tests.push_back({"pineapplepenapple", {"apple","pen","applepen","pine","pineapple"}});
    tests.push_back({"aaaaaaaa", {"a","aa","aaa","aaaa"}});
    tests.push_back({"leetcode", {"leet","code"}});
    tests.push_back({"catsandog", {"cats","dog","sand","and","cat"}});
    tests.push_back({"bb", {"a","b","bb","bbb"}});
    tests.push_back({"abcdabcdabcd", {"ab","abc","cd","abcd","d","cda","bca"}});
    tests.push_back({"aaaaab", {"a","aa","aaa","aaaa","aaaaa"}});
    tests.push_back({"catscatscats", {"cat","cats","scat","s","catsc","ats","ca","ts","atsc","at","t","c"}});
    tests.push_back({"thequickbrownfox", {"the","quick","brown","fox","thequick","quickbrown","brownfox"}});

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            auto res = sol.wordBreak(t.first, t.second);
            checksum += static_cast<uint64_t>(res.size());
            for (const auto& sentence : res) {
                checksum += static_cast<uint64_t>(sentence.size());
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}