int main() {
    vector<TestInput> tests;

    // Test 1: Single node
    tests.push_back({
        1,
        {},
        { {2,1} }
    });

    // Test 2: Small chain with updates
    tests.push_back({
        3,
        { {1,2,5}, {2,3,7} },
        { {2,3}, {1,2,3,10}, {2,3}, {1,1,2,1}, {2,3}, {2,2}, {2,1} }
    });

    // Test 3: Star tree
    tests.push_back({
        5,
        { {1,2,1}, {1,3,2}, {1,4,3}, {1,5,4} },
        { {2,5}, {1,1,3,10}, {2,3}, {2,5}, {1,1,5,1}, {2,5}, {2,1} }
    });

    // Test 4: Balanced tree
    tests.push_back({
        7,
        { {1,2,3}, {1,3,4}, {2,4,5}, {2,5,6}, {3,6,7}, {3,7,8} },
        { {2,4}, {2,7}, {1,3,7,2}, {2,7}, {1,1,3,10}, {2,6}, {2,2}, {1,2,5,1}, {2,5} }
    });

    // Test 5: Random small tree with multiple updates
    tests.push_back({
        6,
        { {1,2,2}, {1,3,5}, {2,4,1}, {2,5,2}, {3,6,3} },
        { {2,6}, {1,1,3,1}, {2,6}, {1,2,5,10}, {2,5}, {1,2,4,5}, {2,4}, {2,3} }
    });

    // Test 6: Chain of 10 nodes with several updates
    tests.push_back({
        10,
        { {1,2,1}, {2,3,2}, {3,4,3}, {4,5,4}, {5,6,5}, {6,7,6}, {7,8,7}, {8,9,8}, {9,10,9} },
        { {2,10}, {1,5,6,10}, {2,10}, {1,1,2,0}, {2,1}, {2,2}, {2,3}, {1,9,10,1}, {2,10}, {2,5} }
    });

    // Test 7: Star with only queries
    tests.push_back({
        4,
        { {1,2,7}, {1,3,8}, {1,4,9} },
        { {2,2}, {2,3}, {2,4}, {2,1}, {2,3}, {2,2} }
    });

    // Test 8: Mixed weights with larger values
    tests.push_back({
        8,
        { {1,2,100}, {2,3,200}, {2,4,300}, {1,5,400}, {5,6,500}, {5,7,600}, {7,8,700} },
        { {2,8}, {1,5,7,1000}, {2,8}, {1,1,5,50}, {2,8}, {2,6}, {1,2,4,100}, {2,4} }
    });

    // Test 9: Complete binary tree up to 15
    tests.push_back({
        15,
        { {1,2,2}, {1,3,3}, {2,4,4}, {2,5,5}, {3,6,6}, {3,7,7}, {4,8,8}, {4,9,9},
          {5,10,10}, {5,11,11}, {6,12,12}, {6,13,13}, {7,14,14}, {7,15,15} },
        { {2,15}, {1,7,15,1}, {2,15}, {1,1,3,10}, {2,15}, {2,14}, {1,2,5,1}, {2,11} }
    });

    // Test 10: Random tree with repeated updates
    tests.push_back({
        9,
        { {1,2,5}, {1,3,2}, {3,4,4}, {3,5,1}, {2,6,3}, {6,7,6}, {6,8,2}, {8,9,7} },
        { {2,9}, {1,6,8,5}, {2,9}, {1,1,2,1}, {2,9}, {1,3,4,10}, {2,4}, {1,3,5,7}, {2,5}, {2,6} }
    });

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            Solution sol;
            vector<int> out = sol.treeQueries(t.n, t.edges, t.queries);
            for (int v : out) checksum += v;
        }
        sink = checksum;
    }

    return 0;
}