int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test inputs
    vector<string> inputs;
    inputs.push_back("");                                   // empty
    inputs.push_back("a");                                  // very short, lowercase only
    inputs.push_back("AAAAAA");                             // length 6, uppercase only, repeats
    inputs.push_back("123456");                             // length 6, digits only
    inputs.push_back("Aa1");                                // short but all types present
    inputs.push_back("aaaB1");                              // short with triple repeat
    inputs.push_back("aaaAAA111");                          // multiple triples, all types present
    inputs.push_back("abcdeFGHIJKLmnopQR");                 // length 18, missing digit
    inputs.push_back(string(21, 'a'));                      // length 21, single long repeat
    inputs.push_back(string("A1") + string(6,'a') + string(7,'b') + string(8,'c')); // length 23, runs with mod 0/1/2

    Solution solver;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : inputs) {
            checksum += solver.strongPasswordChecker(s);
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}