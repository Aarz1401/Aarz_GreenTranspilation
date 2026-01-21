int main() {
    // Define 10 diverse test inputs (each is a sequence of operations)
    vector<vector<Op>> tests;

    // Test 1: Basic add and queries with adjacency merge
    tests.push_back({
        {OpType::Add, 10, 20},
        {OpType::Query, 10, 15},
        {OpType::Query, 15, 25},
        {OpType::Add, 20, 25},
        {OpType::Query, 18, 22}
    });

    // Test 2: Overlapping adds forming a chain and a split by remove
    tests.push_back({
        {OpType::Add, 5, 7},
        {OpType::Add, 1, 3},
        {OpType::Add, 2, 6},
        {OpType::Query, 1, 7},
        {OpType::Remove, 3, 4},
        {OpType::Query, 3, 4},
        {OpType::Query, 2, 3}
    });

    // Test 3: Remove entire coverage and re-add
    tests.push_back({
        {OpType::Add, 0, 100},
        {OpType::Remove, 0, 100},
        {OpType::Query, 0, 1},
        {OpType::Add, 50, 60},
        {OpType::Query, 55, 56}
    });

    // Test 4: Non-merging adjacency then bridging add and split remove
    tests.push_back({
        {OpType::Add, 30, 40},
        {OpType::Add, 41, 50},
        {OpType::Query, 40, 41},
        {OpType::Add, 40, 41},
        {OpType::Query, 30, 50},
        {OpType::Remove, 35, 45},
        {OpType::Query, 34, 36},
        {OpType::Query, 30, 35}
    });

    // Test 5: Empty structure queries and zero-length intervals behavior
    tests.push_back({
        {OpType::Query, 1, 2},
        {OpType::Add, 1, 1},
        {OpType::Query, 1, 1},
        {OpType::Remove, 1, 1},
        {OpType::Query, 1, 1}
    });

    // Test 6: Extreme integer boundaries and small removals
    tests.push_back({
        {OpType::Add, numeric_limits<int>::min() + 10, numeric_limits<int>::min() + 20},
        {OpType::Add, numeric_limits<int>::max() - 20, numeric_limits<int>::max() - 10},
        {OpType::Query, numeric_limits<int>::min() + 11, numeric_limits<int>::min() + 19},
        {OpType::Query, numeric_limits<int>::max() - 15, numeric_limits<int>::max() - 10},
        {OpType::Remove, numeric_limits<int>::min() + 15, numeric_limits<int>::min() + 16},
        {OpType::Query, numeric_limits<int>::min() + 15, numeric_limits<int>::min() + 16}
    });

    // Test 7: Many small disjoint adds, then a large merge, then a split
    {
        vector<Op> t7;
        for (int i = 0; i < 20; i += 2) {
            t7.push_back({OpType::Add, i, i + 1});
        }
        t7.push_back({OpType::Add, 0, 20});
        t7.push_back({OpType::Remove, 5, 15});
        t7.push_back({OpType::Query, 0, 5});
        t7.push_back({OpType::Query, 15, 20});
        t7.push_back({OpType::Query, 10, 12});
        tests.push_back(t7);
    }

    // Test 8: Bridging add across a removed gap and complete removal
    tests.push_back({
        {OpType::Add, 100, 200},
        {OpType::Remove, 120, 180},
        {OpType::Add, 110, 190},
        {OpType::Query, 150, 160},
        {OpType::Remove, 90, 210},
        {OpType::Query, 100, 101}
    });

    // Test 9: Nibbling edges via multiple removes
    tests.push_back({
        {OpType::Add, 0, 100},
        {OpType::Remove, 0, 10},
        {OpType::Remove, 90, 100},
        {OpType::Remove, 50, 60},
        {OpType::Remove, 10, 11},
        {OpType::Query, 11, 50},
        {OpType::Query, 59, 61},
        {OpType::Query, 60, 90}
    });

    // Test 10: Duplicate adds, nested add, and middle removal
    tests.push_back({
        {OpType::Add, 5, 10},
        {OpType::Add, 5, 10},
        {OpType::Add, 6, 9},
        {OpType::Query, 5, 10},
        {OpType::Remove, 7, 8},
        {OpType::Query, 7, 8},
        {OpType::Query, 6, 7},
        {OpType::Query, 8, 9}
    });

    long long checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& test : tests) {
            RangeModule rm;
            for (const auto& op : test) {
                switch (op.type) {
                    case OpType::Add:
                        rm.addRange(op.l, op.r);
                        break;
                    case OpType::Remove:
                        rm.removeRange(op.l, op.r);
                        break;
                    case OpType::Query:
                        checksum += rm.queryRange(op.l, op.r) ? 1 : 0;
                        break;
                }
            }
        }
    }

    auto end = Clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}