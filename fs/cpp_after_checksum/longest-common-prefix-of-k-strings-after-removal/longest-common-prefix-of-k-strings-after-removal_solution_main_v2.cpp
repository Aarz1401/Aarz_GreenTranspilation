int main() {
    vector<TestCase> tests = {
        {{"apple", "apricot", "ape"}, 2},
        {{"aaa", "aaa", "aaa", "aaa"}, 2},
        {{"dog", "cat", "bird", "fish"}, 3},
        {{"a", "ab", "abc", "abcd", "b", "ba", "bac"}, 2},
        {{"prefix", "preform", "prevent", "preview", "prelude"}, 5},
        {{"one", "two", "three", "four", "five", "six"}, 1},
        {{"abcde", "abfgh", "abxyz", "ab"}, 3},
        {{"test", "testing", "tester", "testament", "testify", "testimonial", "testable", "testbed", "testcase", "testdrive"}, 4},
        {{"Alpha", "alphabet", "ALPHA", "alphanumeric"}, 2},
        {{"123abc", "123", "12345", "12"}, 2}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            vector<int> res = sol.longestCommonPrefix(const_cast<vector<string>&>(tc.words), tc.k);
            for (int v : res) checksum += v;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}