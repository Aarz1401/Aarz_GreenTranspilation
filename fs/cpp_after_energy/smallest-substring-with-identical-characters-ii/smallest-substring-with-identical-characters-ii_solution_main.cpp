int main() {
    // Prepare diverse test inputs
    vector<pair<string, int>> tests;
    tests.emplace_back(string("0"), 0);                              // 1: single char, zero ops
    tests.emplace_back(string("1"), 1);                              // 2: single char, one op
    tests.emplace_back(string("0101010101"), 0);                     // 3: alternating, even length, zero ops
    tests.emplace_back(string("1010101010101"), 5);                  // 4: alternating, odd length, some ops
    tests.emplace_back(string("0000000000"), 0);                     // 5: all zeros
    tests.emplace_back(string("1111111111"), 4);                     // 6: all ones
    tests.emplace_back(string("0011001111001100"), 3);               // 7: grouped pairs
    tests.emplace_back(string("000111000111000111000"), 2);          // 8: repeating runs
    {
        // 9: long runs with varied lengths (total length 1000)
        string s9;
        s9.reserve(1000);
        s9.append(200, '0');
        s9.append(300, '1');
        s9.append(150, '0');
        s9.append(350, '1');
        tests.emplace_back(move(s9), 100);
    }
    {
        // 10: long alternating (length 1000)
        string s10;
        s10.reserve(1000);
        for (int i = 0; i < 1000; ++i) {
            s10.push_back((i % 2 == 0) ? '0' : '1');
        }
        tests.emplace_back(move(s10), 10);
    }

    Solution sol;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += sol.minLength(tc.first, tc.second);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}