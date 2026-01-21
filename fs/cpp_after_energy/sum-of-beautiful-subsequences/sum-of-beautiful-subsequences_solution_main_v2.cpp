int main() {
    Solution sol;
    vector<vector<int>> tests;
    tests.push_back({1,2,3,4,5,6,7,8,9,10});
    tests.push_back(vector<int>(20, 7));
    tests.push_back({2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97});
    tests.push_back({1,2,4,8,16,32,64,128,256,512});
    tests.push_back({12,18,6,3,9,15,21,27,24,30,36,42,45,48,54,60});
    tests.push_back({999,1000,996,972,945,930,875,840,768,720,660,648,600,588,576});
    tests.push_back({60,59,58,57,56,55,54,53,52,51,50});
    tests.push_back({2000,1995,1980,1920,1800,1600,1500,1400,1350,1300});
    tests.push_back({101,103,107,109,113,127,131,137,139,149});
    tests.push_back({2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3});

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            int res = sol.totalBeauty(tests[i]);
            checksum += res;
            if (checksum >= MOD) checksum -= MOD;
        }
        sink = checksum;
    }
    return 0;
}