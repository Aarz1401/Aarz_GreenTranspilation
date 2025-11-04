int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<string>> tests;
    tests.push_back(vector<string>{ "@.a" }); // simple linear, one key
    tests.push_back(vector<string>{ "@..aA..b" }); // two keys with a lock
    tests.push_back(vector<string>{ "@#a" }); // unreachable key
    tests.push_back(vector<string>{ "@..aA", "..B#.", "....b" }); // multi-row, multiple keys/locks
    tests.push_back(vector<string>{ "@A..b" }); // lock without its key makes key unreachable
    tests.push_back(vector<string>{ "@..", ".#aA", "..b" }); // jagged rows
    tests.push_back(vector<string>{ "@....", "abcde", "ABCDE", "....." }); // many keys in a row
    tests.push_back(vector<string>{ "@..#..a", "..#....", "##.##.#", "..b.A.." }); // maze with walls and locks
    tests.push_back(vector<string>{ "@Aa" }); // lock blocks the only path to its key
    tests.push_back(vector<string>{ "@." }); // no keys

    Solution sol;
    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& grid : tests) {
            int res = sol.shortestPathAllKeys(grid);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = elapsed_ns / 1e6;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}