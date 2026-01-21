int main() {
    vector<pair<string, string>> tests = {
        {"g", "ggg"},
        {"abcde", "ade"},
        {"godding", "gd"},
        {"aaaaa", "aaaaa"},
        {"abcdefghijklmnopqrstuvwxyz", "leetcode"},
        {"pqrstuvwxyzaaabbbccc", "abcxyzp"},
        {"azbzczdz", "zzzzd"},
        {"helloworld", "hello"},
        {"rotationringexample", "example"},
        {"thequickbrownfoxjumpsoverthelazydog", "packmybox"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.findRotateSteps(t.first, t.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}