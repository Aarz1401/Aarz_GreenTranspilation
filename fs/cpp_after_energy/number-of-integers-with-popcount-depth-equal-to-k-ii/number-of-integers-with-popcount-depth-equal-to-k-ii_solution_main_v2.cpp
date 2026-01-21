int main() {
    vector<Test> tests;
    tests.reserve(10);

    {
        Test t;
        t.nums = {1};
        t.queries = {
            {1, 0, 0, 0},
            {2, 0, 2},
            {1, 0, 0, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {2, 3, 4};
        t.queries = {
            {1, 0, 2, 1},
            {1, 1, 2, 2},
            {2, 2, 7},
            {1, 0, 2, 3}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1, 2, 15, 16, 31};
        t.queries = {
            {1, 0, 4, 0},
            {1, 0, 4, 1},
            {1, 0, 4, 2},
            {1, 0, 4, 3},
            {1, 0, 4, 4},
            {2, 0, 1024},
            {1, 0, 4, 0}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {6, 10, 12, 24};
        t.queries = {
            {1, 0, 3, 2},
            {2, 1, 10},
            {1, 1, 2, 2},
            {2, 3, 5},
            {1, 0, 3, 2}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {999999999999999LL, 500000000000000LL, 1LL, 2LL, 3LL, 4LL};
        t.queries = {
            {1, 0, 5, 5},
            {1, 2, 5, 0},
            {2, 2, 8},
            {1, 0, 5, 0},
            {1, 0, 5, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {5, 7, 9, 11, 13, 17, 21, 33};
        t.queries = {
            {1, 0, 7, 3},
            {2, 4, 1},
            {1, 0, 7, 0},
            {1, 3, 5, 2}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
        t.queries = {
            {1, 0, 9, 4},
            {2, 9, 1},
            {1, 0, 9, 0},
            {1, 0, 9, 3}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1LL << 49, 1LL << 48, 1LL << 47, 1LL << 46, 1LL << 45};
        t.queries = {
            {1, 0, 4, 1},
            {2, 2, 3},
            {1, 0, 4, 2},
            {1, 1, 3, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {123456789012345LL, 98765432109876LL, 555555555555555LL, 222222222222222LL, 99999999999999LL, 314159265358979LL, 271828182845904LL};
        t.queries = {
            {1, 0, 6, 3},
            {2, 5, 1},
            {1, 0, 6, 0},
            {2, 0, 2},
            {1, 0, 3, 1}
        };
        tests.push_back(t);
    }
    {
        Test t;
        t.nums = {1, 2, 3, 4, 5, 6};
        t.queries = {
            {1, 0, 5, 0},
            {1, 0, 5, 1},
            {2, 0, 7},
            {1, 0, 2, 3},
            {2, 4, 1},
            {1, 0, 5, 0}
        };
        tests.push_back(t);
    }

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int t = 0; t < (int)tests.size(); ++t) {
            Test cur = tests[t];
            Solution sol;
            vector<int> out = sol.popcountDepth(cur.nums, cur.queries);
            for (int v : out) checksum += v;
            checksum += (int)out.size();
        }
        sink = checksum;
    }

    return 0;
}