int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> t1 = {
        {0,0}, {1,1}, {2,0}
    };

    vector<vector<int>> t2 = {
        {0,0}, {0,5}, {5,5}, {5,0}, {2,0}, {3,5}, {0,2}, {5,3}, {2,2}, {0,0}, {5,5}
    };

    vector<vector<int>> t3 = {
        {0,0}, {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {3,3}, {2,2}
    };

    vector<vector<int>> t4 = {
        {42,-7}
    };

    vector<vector<int>> t5 = {
        {-1,-1}, {-3,-3}
    };

    vector<vector<int>> t6 = {
        {0,10}, {2,2}, {10,0}, {2,-2}, {0,-10}, {-2,-2}, {-10,0}, {-2,2}, {0,0}, {4,0}, {-4,0}
    };

    vector<vector<int>> t7 = {
        {10,0}, {8,6}, {6,8}, {0,10}, {-6,8}, {-8,6}, {-10,0}, {-8,-6}, {-6,-8}, {0,-10},
        {6,-8}, {8,-6}, {7,7}, {-7,7}, {-7,-7}, {7,-7}, {0,0}, {3,4}, {-3,-4}
    };

    vector<vector<int>> t8 = {
        {-100,-100}, {-110,-90}, {-120,-110}, {-90,-120}, {-95,-105}, {-105,-95},
        {-130,-100}, {-100,-130}, {-80,-100}, {-100,-80}, {-90,-90}, {-110,-110}
    };

    vector<vector<int>> t9;
    for (int x = 0; x <= 10; ++x) {
        t9.push_back({x, 0});
        t9.push_back({x, 10});
    }
    for (int y = 1; y < 10; ++y) {
        t9.push_back({0, y});
        t9.push_back({10, y});
    }
    t9.push_back({5,5});
    t9.push_back({3,7});
    t9.push_back({7,3});
    t9.push_back({5,5}); // duplicate

    vector<vector<int>> t10 = {
        {1,1}, {1,1}, {1,1}, {0,0}, {0,0}, {2,2}, {2,2}, {2,2}, {0,2}, {2,0}, {-1,-1}, {-1,2}, {2,-1}
    };

    vector<vector<vector<int>>> tests;
    tests.push_back(t1);
    tests.push_back(t2);
    tests.push_back(t3);
    tests.push_back(t4);
    tests.push_back(t5);
    tests.push_back(t6);
    tests.push_back(t7);
    tests.push_back(t8);
    tests.push_back(t9);
    tests.push_back(t10);

    Solution sol;

    volatile long long checksum = 0; // volatile to reduce optimization risk

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& base : tests) {
            auto input = base; // copy because the function mutates the input
            auto hull = sol.outerTrees(input);
            for (const auto& p : hull) {
                checksum += (static_cast<long long>(p[0]) * 1000003LL) ^ (static_cast<long long>(p[1]) * 911LL + 1LL);
            }
            checksum += static_cast<long long>(hull.size());
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}