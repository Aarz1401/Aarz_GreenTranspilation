int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: all 2's
    {
        vector<int> a(60, 2);
        tests.push_back({a, 5});
    }

    // Test 2: all 1's
    {
        vector<int> a(20, 1);
        tests.push_back({a, 0});
    }

    // Test 3: primes
    {
        vector<int> a = {2,3,5,7,11,13,17,19,23,29,31,37};
        tests.push_back({a, 8});
    }

    // Test 4: repeating mixed pattern
    {
        vector<int> base = {6, 10, 15, 21, 14, 22};
        vector<int> a;
        for (int i = 0; i < 6; ++i) {
            a.insert(a.end(), base.begin(), base.end());
        }
        tests.push_back({a, 4});
    }

    // Test 5: powers of two
    {
        vector<int> a;
        for (int i = 1; i <= 16; ++i) a.push_back(1 << i);
        tests.push_back({a, 1});
    }

    // Test 6: mixed composites and multiples
    {
        vector<int> a = {12,18,6,9,3,27,30,15,21,14,7,28,35,5,10,20,25,50,75,100};
        tests.push_back({a, 3});
    }

    // Test 7: single element
    {
        vector<int> a = {2};
        tests.push_back({a, 0});
    }

    // Test 8: alternating 2 and 3, length 200
    {
        vector<int> a(200);
        for (int i = 0; i < 200; ++i) a[i] = (i % 2 == 0) ? 2 : 3;
        tests.push_back({a, 80});
    }

    // Test 9: diverse composites
    {
        vector<int> a = {30,42,70,105,210,330,66,198,462,924,231,77,143,187,221};
        tests.push_back({a, 2});
    }

    // Test 10: alternating 4 and 6, length 256
    {
        vector<int> a(256);
        for (int i = 0; i < 256; ++i) a[i] = (i % 2 == 0) ? 4 : 6;
        tests.push_back({a, 100});
    }

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (int i = 0; i < 10; ++i) {
            vector<int> nums = tests[i].nums;
            int res = sol.minStable(nums, tests[i].maxC);
            checksum += res;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}