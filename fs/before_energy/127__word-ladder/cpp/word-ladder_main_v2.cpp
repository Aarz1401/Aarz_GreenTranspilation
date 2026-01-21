int main() {
    vector<TestCase> tests = {
        {"hit", "cog", {"hot","dot","dog","lot","log","cog"}},
        {"hit", "cog", {"hot","dot","dog","lot","log"}},
        {"aab", "abb", {"abb","aba","bbb"}},
        {"lead", "gold", {"load","goad","gold","golf","gald"}},
        {"lost", "cost", {"most","host","cost","lost","lose"}},
        {"abc", "xyz", {"xbc","xyc","xyz","xya","abx"}},
        {"aaaa", "bbbb", {"baaa","bbaa","bbba","bbbb","abaa"}},
        {"talk", "tail", {"tall","tail","balk","tark","tauk"}},
        {"abcd", "dcba", {"abce","abde","acde","bcde","dcba"}},
        {"aaaaa", "zzzzz", {"zaaaa","zzaaa","zzzaa","zzzza","zzzzz","aaaaz"}}
    };

    volatile int sink = 0;
    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.ladderLength(tests[i].begin, tests[i].end, tests[i].wordList);
        }
        sink = checksum;
    }
    return 0;
}