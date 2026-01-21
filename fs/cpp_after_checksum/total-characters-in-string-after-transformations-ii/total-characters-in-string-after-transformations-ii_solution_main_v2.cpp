int main() {
    Solution sol;
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1
    vector<int> nums1(26, 0);
    tests.push_back({"a", 0, nums1});

    // Test 2
    vector<int> nums2(26, 1);
    tests.push_back({"abc", 1, nums2});

    // Test 3
    vector<int> nums3(26, 0);
    nums3[25] = 2; // 'z'
    tests.push_back({"zzz", 2, nums3});

    // Test 4
    vector<int> nums4(26);
    for (int i = 0; i < 26; ++i) nums4[i] = i % 3;
    tests.push_back({"leetcode", 3, nums4});

    // Test 5
    vector<int> nums5(26);
    for (int i = 0; i < 26; ++i) nums5[i] = i % 5;
    tests.push_back({"abcdefghijklmnopqrstuvwxyz", 5, nums5});

    // Test 6
    vector<int> nums6(26, 0);
    nums6[0] = 3; // 'a'
    tests.push_back({"aaaaaaaaaaaaaaaaaaaa", 10, nums6});

    // Test 7
    vector<int> nums7(26, 2);
    tests.push_back({"mixandmatch", 26, nums7});

    // Test 8
    vector<int> nums8(26);
    for (int i = 0; i < 26; ++i) nums8[i] = (i % 2 == 0) ? 2 : 1;
    tests.push_back({"bcdxyzab", 12, nums8});

    // Test 9
    vector<int> nums9(26, 0);
    nums9[16] = 4; // 'q'
    nums9[22] = 3; // 'w'
    nums9[19] = 2; // 't'
    tests.push_back({"qwerty", 32, nums9});

    // Test 10
    vector<int> nums10 = {3,0,1,2,0,1,3,0,2,1,0,3,1,0,2,1,0,2,3,0,1,2,0,1,2,3};
    tests.push_back({"thequickbrownfox", 20, nums10});

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.lengthAfterTransformations(tc.s, tc.t, tc.nums);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}