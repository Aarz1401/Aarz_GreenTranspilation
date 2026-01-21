int main() {
    vector<vector<pair<char, string>>> tests;

    // Test 1
    tests.push_back({
        {'I',"a"}, {'I',"b"}, {'I',"a"}, {'I',"c"}, {'I',"b"}, {'I',"a"}
    });

    // Test 2
    tests.push_back({
        {'I',"apple"}, {'I',"apple"}, {'I',"apple"}, {'I',"apple"}, {'I',"apple"},
        {'I',"banana"}, {'I',"banana"}, {'I',"banana"},
        {'I',"cherry"},
        {'I',"date"}, {'I',"date"}
    });

    // Test 3
    tests.push_back({
        {'I',"x"}, {'I',"x"}, {'I',"x"}, {'I',"x"},
        {'I',"y"},
        {'I',"z"}, {'I',"z"}, {'I',"z"}
    });

    // Test 4
    tests.push_back({
        {'I',"m"}, {'I',"m"},
        {'I',"n"}, {'I',"n"},
        {'D',"n"}, {'D',"n"},
        {'I',"n"},
        {'I',"o"}, {'D',"o"}
    });

    // Test 5
    tests.push_back({
        {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"},
        {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"},
        {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"},
        {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"},
        {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"},
        {'I',"k3"}, {'I',"k3"}, {'I',"k3"},
        {'I',"k4"}, {'I',"k4"}, {'I',"k4"}, {'I',"k4"}, {'I',"k4"},
        {'I',"k4"}, {'I',"k4"},
        {'I',"k5"}, {'I',"k5"}, {'I',"k5"}, {'I',"k5"}, {'I',"k5"}, {'I',"k5"}
    });

    // Test 6
    tests.push_back({
        {'I',"alpha"}, {'I',"alpha"},
        {'I',"beta"}, {'I',"beta"}, {'I',"beta"},
        {'D',"alpha"},
        {'D',"beta"},
        {'I',"gamma"}, {'I',"gamma"}, {'I',"gamma"}, {'I',"gamma"},
        {'D',"gamma"}, {'D',"gamma"},
        {'I',"beta"}
    });

    // Test 7
    tests.push_back({
        {'I',"aa"},
        {'I',"bb"}, {'I',"bb"}, {'I',"bb"}, {'I',"bb"},
        {'I',"cc"}, {'I',"cc"},
        {'I',"dd"}, {'I',"dd"}, {'I',"dd"}
    });

    // Test 8
    tests.push_back({
        {'I',"t1"}, {'I',"t1"}, {'I',"t1"},
        {'I',"t2"}, {'I',"t2"},
        {'I',"t3"}, {'I',"t3"}, {'I',"t3"}, {'I',"t3"}, {'I',"t3"}, {'I',"t3"},
        {'I',"t4"}, {'I',"t4"}, {'I',"t4"},
        {'D',"t3"}, {'D',"t3"},
        {'I',"t1"}, {'I',"t1"},
        {'I',"t3"}, {'I',"t3"}, {'I',"t3"},
        {'D',"t4"},
        {'D',"t2"}
    });

    // Test 9
    tests.push_back({
        {'I',"k0"}, {'I',"k0"}, {'I',"k0"}, {'I',"k0"}, {'I',"k0"},
        {'I',"k0"}, {'I',"k0"}, {'I',"k0"}, {'I',"k0"},
        {'I',"k1"},
        {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"},
        {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}
    });

    // Test 10
    tests.push_back({
        {'I',"w1"}, {'I',"w1"}, {'I',"w1"},
        {'I',"w2"}, {'I',"w2"}, {'D',"w2"},
        {'I',"w3"}, {'I',"w3"},
        {'I',"w4"}, {'I',"w4"}, {'I',"w4"}, {'I',"w4"}, {'I',"w4"},
        {'I',"w5"}, {'I',"w5"}, {'I',"w5"}, {'I',"w5"}
    });

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code
        int checksum = 0;
        for (const auto& ops : tests) {
            AllOne ds;
            for (const auto& op : ops) {
                if (op.first == 'I') ds.inc(op.second);
                else if (op.first == 'D') ds.dec(op.second);
            }
            string mx = ds.getMaxKey();
            string mn = ds.getMinKey();
            checksum += shash(mx) + shash(mn);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}