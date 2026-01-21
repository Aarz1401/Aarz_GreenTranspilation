int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    tests.push_back(TestCase{
        {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        },
        {"oath","pea","eat","rain","hklf","hf"}
    });

    tests.push_back(TestCase{
        {
            {'a','b','c','d','e','f'}
        },
        {"abc","cde","fed","abf","ace"}
    });

    tests.push_back(TestCase{
        {
            {'g'},
            {'h'},
            {'i'},
            {'j'},
            {'k'}
        },
        {"ghi","ijk","ghij","hg","jk"}
    });

    tests.push_back(TestCase{
        {
            {'a','a','a'},
            {'a','a','a'},
            {'a','a','a'}
        },
        {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa"}
    });

    tests.push_back(TestCase{
        {
            {'x','y','z'},
            {'p','q','r'},
            {'l','m','n'}
        },
        {"abc","def","ghi","uvw","rst"}
    });

    tests.push_back(TestCase{
        {
            {'s','e','e','d'},
            {'s','e','n','d'},
            {'s','e','e','d'}
        },
        {"see","seen","seed","sees","send","ends"}
    });

    tests.push_back(TestCase{
        {
            {'t','h','i','s','i','s','a'},
            {'s','i','m','p','l','e','x'}
        },
        {"this","is","a","simple","isth","xis","thisis","plex","simplex"}
    });

    tests.push_back(TestCase{
        {
            {'a','b','c','d'},
            {'e','f','g','h'},
            {'i','j','k','l'},
            {'m','n','o','p'}
        },
        {"abfj","mnop","aeim","cfk","ghkl"}
    });

    tests.push_back(TestCase{
        {
            {'a','b','a'},
            {'b','a','b'},
            {'a','b','a'}
        },
        {"aba","bab","ababa","babab","aaaa","abba"}
    });

    tests.push_back(TestCase{
        {
            {'l','e','e','t','c'},
            {'o','d','e','c','o'},
            {'d','e','l','e','t'},
            {'c','o','e','d','e'},
            {'c','o','d','e','s'}
        },
        {"leet","code","codes","leetcode","cool","deco","decode"}
    });

    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (auto& tc : tests) {
            auto res = sol.findWords(tc.board, tc.words);
            checksum += static_cast<int>(res.size());
        }
        sink = checksum;
    }

    return 0;
}