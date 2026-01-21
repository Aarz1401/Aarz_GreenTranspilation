int main() {
    vector<vector<string>> tests = {
        {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"},
        {"a","b","ab","abc","cd","abcd","ef","abcdef"},
        {"cat","dog","catdog","dogcat","catdogcat","dogcatdog","c","at","do","g","catcat"},
        {"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","aaaaaaaaaaa"},
        {"tree","tre","e","tr","ee","treetree","trtreee","eetree","treee"},
        {"a","b","c","ab","bc","abc","abcd","bcda","cab","cabcab","abcabc"},
        {"rock","star","rockstar","super","superstar","stars","tar","ro","ck","starrock","starstar"},
        {"news","paper","newspaper","newsnews","papernews","new","sp","apers","newspapern","n"},
        {"leet","code","leetcode","le","et","co","de","leetco","decode","leetcodede","leetleetcode"},
        {"home","work","homework","frame","workframe","framework","me","or","k","framehomework"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            auto& t = tests[i];
            auto res = sol.findAllConcatenatedWordsInADict(t);
            checksum += static_cast<int>(res.size());
        }
        sink = checksum;
    }

    return 0;
}