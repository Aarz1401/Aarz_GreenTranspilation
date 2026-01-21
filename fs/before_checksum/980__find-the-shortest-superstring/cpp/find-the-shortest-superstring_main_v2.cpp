int main() {
    vector<vector<string>> testCases = {
        {"alex","loves","leetcode"},
        {"catg","ctaagt","gcta","ttca","atgcatc"},
        {"abcd","cdef","fgh","de"},
        {"aa","bb","cc","dd"},
        {"a","b","c","a"},
        {"ababa","baba","aba"},
        {"the","there","answer","any","by","their"},
        {"abc","bcd","cde","defg"},
        {"xyz","yzab","zabc","abcd","bc"},
        {"lemon","melon","onion"}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : testCases) {
            vector<string> A = tc;
            string res = sol.shortestSuperstring(A);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}