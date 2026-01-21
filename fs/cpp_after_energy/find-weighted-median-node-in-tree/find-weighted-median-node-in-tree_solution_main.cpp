int main() {
    // Build 10 diverse test inputs
    vector<TestCase> tests;

    // 1) Single node, trivial queries
    {
        TestCase t;
        t.n = 1;
        t.edges = {};
        t.queries = {{0,0}, {0,0}};
        tests.push_back(t);
    }

    // 2) Two-node tree
    {
        TestCase t;
        t.n = 2;
        t.edges = {{0,1,5}};
        t.queries = {{0,1}, {1,0}, {0,0}, {1,1}};
        tests.push_back(t);
    }

    // 3) Star tree with center 0
    {
        TestCase t;
        t.n = 7;
        t.edges = {{0,1,3},{0,2,5},{0,3,2},{0,4,7},{0,5,11},{0,6,1}};
        t.queries = {{1,2},{3,4},{5,6},{1,6},{2,5},{3,0},{4,1},{2,3}};
        tests.push_back(t);
    }

    // 4) Path of length 10
    {
        TestCase t;
        t.n = 10;
        for (int i = 0; i < 9; ++i) t.edges.push_back({i, i+1, i+1});
        t.queries = {{0,9},{2,7},{8,4},{3,3},{9,1},{0,0},{5,9},{1,6}};
        tests.push_back(t);
    }

    // 5) Balanced-ish binary tree n=15
    {
        TestCase t;
        t.n = 15;
        for (int i = 0; i <= 6; ++i) {
            int l = 2*i+1, r = 2*i+2;
            if (l < t.n) t.edges.push_back({i, l, i+2});
            if (r < t.n) t.edges.push_back({i, r, i+3});
        }
        t.queries = {{14,0},{7,8},{10,11},{3,4},{13,9},{6,1},{2,14},{5,12},{0,0}};
        tests.push_back(t);
    }

    // 6) Random-like tree n=20 (fixed)
    {
        TestCase t;
        t.n = 20;
        t.edges = {
            {0,1,4},{0,2,8},{2,3,3},{1,4,7},{3,5,6},{2,6,5},{5,7,9},{4,8,2},{6,9,1},
            {7,10,4},{8,11,3},{9,12,8},{10,13,2},{11,14,7},{12,15,5},{13,16,4},{14,17,6},{15,18,3},{16,19,9}
        };
        t.queries = {{0,19},{4,14},{10,3},{12,7},{5,15},{11,6},{18,2},{9,9},{1,13},{8,0}};
        tests.push_back(t);
    }

    // 7) Heavy weights path n=8
    {
        TestCase t;
        t.n = 8;
        int w = 1000000000;
        for (int i = 0; i < 7; ++i) t.edges.push_back({i, i+1, w - (i*3)});
        t.queries = {{0,7},{1,6},{2,5},{3,4},{0,0},{7,7},{1,1}};
        tests.push_back(t);
    }

    // 8) Repeated queries on a moderate tree n=12
    {
        TestCase t;
        t.n = 12;
        t.edges = {
            {0,1,1},{0,2,2},{1,3,3},{1,4,4},{2,5,5},{2,6,6},
            {3,7,7},{4,8,8},{5,9,9},{6,10,10},{6,11,11}
        };
        t.queries = {{7,9},{7,9},{7,9},{8,10},{8,10},{3,11},{3,11},{0,11},{5,1},{2,8},{4,4}};
        tests.push_back(t);
    }

    // 9) Non-empty tree but zero queries
    {
        TestCase t;
        t.n = 5;
        t.edges = {{0,1,2},{1,2,3},{2,3,4},{3,4,5}};
        t.queries = {};
        tests.push_back(t);
    }

    // 10) Larger path n=50 with mixed queries
    {
        TestCase t;
        t.n = 50;
        for (int i = 0; i < 49; ++i) t.edges.push_back({i, i+1, (i%7)+1});
        t.queries = {
            {0,49},{10,40},{5,25},{12,12},{3,44},{7,33},{0,1},{1,2},{2,3},{3,4},
            {20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{30,35}
        };
        tests.push_back(t);
    }

    Solution sol;
    volatile uint64_t checksum = 0; // volatile to avoid optimization

    auto t1 = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            auto n = tests[ti].n;
            auto edges = tests[ti].edges;
            auto queries = tests[ti].queries;
            vector<int> res = sol.findMedian(n, edges, queries);
            // Accumulate into checksum
            checksum ^= (uint64_t)res.size() + (ti + 1);
            for (size_t i = 0; i < res.size(); ++i) {
                checksum = checksum * 1000003ULL + (uint64_t)(res[i] + 1) + (i + 1);
            }
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}