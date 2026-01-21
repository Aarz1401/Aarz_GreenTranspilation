int main() {
    vector<Test> tests;

    // 1
    tests.push_back({2, {
        {'p',1,1}, {'p',2,2}, {'g',1,0}, {'p',3,3}, {'g',2,0},
        {'g',3,0}, {'p',4,4}, {'g',1,0}, {'g',3,0}, {'g',4,0}
    }});

    // 2
    tests.push_back({1, {
        {'p',1,10}, {'g',1,0}, {'p',2,20}, {'g',1,0}, {'g',2,0},
        {'p',2,200}, {'g',2,0}
    }});

    // 3
    tests.push_back({3, {
        {'p',1,1}, {'p',2,2}, {'p',3,3}, {'g',1,0}, {'g',2,0},
        {'p',4,4}, {'g',3,0}, {'g',4,0}, {'g',1,0}, {'p',5,5},
        {'g',2,0}, {'g',5,0}
    }});

    // 4
    tests.push_back({3, {
        {'p',1,100}, {'p',2,200}, {'p',3,300}, {'g',1,0}, {'g',1,0},
        {'g',1,0}, {'g',2,0}, {'p',4,400}, {'g',3,0}, {'g',1,0}, {'g',4,0}
    }});

    // 5
    tests.push_back({2, {
        {'p',1,1}, {'p',2,2}, {'g',1,0}, {'p',1,10}, {'g',1,0},
        {'p',3,3}, {'g',2,0}, {'g',3,0}
    }});

    // 6
    tests.push_back({4, {
        {'p',1,1}, {'p',2,2}, {'p',3,3}, {'p',4,4}, {'g',1,0}, {'g',2,0},
        {'p',5,5}, {'g',3,0}, {'g',4,0}, {'p',6,6}, {'g',4,0}, {'g',5,0}, {'g',6,0}
    }});

    // 7
    tests.push_back({3, {
        {'p',1,10}, {'p',2,20}, {'p',3,30}, {'g',2,0}, {'p',4,40},
        {'g',1,0}, {'g',3,0}, {'g',2,0}
    }});

    // 8
    tests.push_back({5, {
        {'p',1,10}, {'p',2,20}, {'p',3,30}, {'p',4,40}, {'p',5,50},
        {'g',1,0}, {'g',1,0}, {'p',1,100}, {'g',1,0}, {'p',6,60},
        {'g',2,0}, {'g',6,0}
    }});

    // 9
    tests.push_back({2, {
        {'p',1,1}, {'g',1,0}, {'g',1,0}, {'g',1,0}, {'g',1,0}, {'g',1,0},
        {'p',2,2}, {'p',3,3}, {'g',1,0}, {'g',2,0}, {'g',3,0}
    }});

    // 10
    tests.push_back({3, {
        {'p',0,0}, {'p',1,1}, {'p',2,2}, {'g',0,0}, {'g',1,0},
        {'p',3,3}, {'g',2,0}, {'p',0,5}, {'g',0,0}
    }});

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& test : tests) {
            LFUCache cache(test.capacity);
            int local = 0;
            for (const auto& op : test.ops) {
                if (op.type == 'p') {
                    cache.put(op.key, op.value);
                } else if (op.type == 'g') {
                    local += cache.get(op.key);
                }
            }
            checksum += local;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}