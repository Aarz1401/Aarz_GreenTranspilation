int main() {
    using namespace std;

    vector<string> tests;
    tests.reserve(10);
    tests.push_back("");                 // 0-length
    tests.push_back("I");                // single I
    tests.push_back("D");                // single D
    tests.push_back("ID");               // simple mixed
    tests.push_back("DI");               // simple mixed reversed
    tests.push_back("IIDDD");            // clustered I then D
    tests.push_back(string(10, 'D'));    // all D
    tests.push_back(string(10, 'I'));    // all I
    tests.push_back("IDIDIDIDID");       // alternating length 10
    string s10;
    s10.reserve(80);                     // longer mixed deterministic pattern
    for (int i = 0; i < 80; ++i) {
        s10.push_back(((i * 37 + 13) % 5 < 2) ? 'I' : 'D');
    }
    tests.push_back(s10);

    Solution sol;
    long long checksum = 0;

    using clock = chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            int res = sol.numPermsDISequence(s);
            checksum += res;
        }
    }

    auto end = clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}