int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    tests.push_back({"e + 8 - a + 5", {"e"}, {1}});
    tests.push_back({"e - 8 + temperature - pressure", {"e", "temperature"}, {1, 12}});
    tests.push_back({"(e + 8) * (e - 8)", {}, {}});
    tests.push_back({"7 - 7", {}, {}});
    tests.push_back({"a * b * c + b * a * c * 2", {}, {}});
    tests.push_back({"((a + b) * (c + d) * (e + f))", {"a","b","c","d","e","f"}, {1,2,3,4,5,6}});
    tests.push_back({"a - b + c - d + e - f + g - h + i - j", {"a","b","c","d","e"}, {10,9,8,7,6}});
    tests.push_back({"a*b*b*b + b*a*a + 3*a*b", {"a","b"}, {2,3}});
    tests.push_back({"42", {"x"}, {1}});
    tests.push_back({"x*y + y*z + z*x + x*x*y", {"x","z"}, {2,5}});

    Solution solver;

    using chrono::high_resolution_clock;
    using chrono::duration;
    using chrono::duration_cast;
    auto start = high_resolution_clock::now();

    uint64_t checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<string> vars = tc.vars;
            vector<int> vals = tc.vals;
            vector<string> res = solver.basicCalculatorIV(tc.expr, vars, vals);
            for (const auto& s : res) {
                checksum ^= (static_cast<uint64_t>(std::hash<string>{}(s)) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2));
            }
            checksum += res.size();
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ms = duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}