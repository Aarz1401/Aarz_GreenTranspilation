int main() {
    // Define 10 diverse test inputs
    std::vector<std::pair<std::vector<std::string>, int>> tests;
    tests.emplace_back(std::vector<std::string>{"This","is","an","example","of","text","justification."}, 16);
    tests.emplace_back(std::vector<std::string>{"a","b","c","d"}, 1);
    tests.emplace_back(std::vector<std::string>{"helloworld"}, 10);
    tests.emplace_back(std::vector<std::string>{"a"}, 5);
    tests.emplace_back(std::vector<std::string>{"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"}, 20);
    tests.emplace_back(std::vector<std::string>{"a","b","c","d","e"}, 2);
    tests.emplace_back(std::vector<std::string>{}, 5);
    tests.emplace_back(std::vector<std::string>{"hello","world"}, 50);
    tests.emplace_back(std::vector<std::string>{"abcdef","g","hijkl","mn","o"}, 6);
    tests.emplace_back(std::vector<std::string>{"a","bb","ccc","dddd","eeeee","f","gg","hhh","i","jjjjjj"}, 10);

    Solution solver;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto &tc : tests) {
            std::vector<std::string> result = solver.fullJustify(tc.first, tc.second);
            // Accumulate into checksum to avoid optimization
            checksum += static_cast<uint64_t>(result.size());
            for (const auto& line : result) {
                checksum ^= static_cast<uint64_t>(line.size());
                for (unsigned char c : line) {
                    checksum = (checksum * 1315423911ull) ^ c;
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed << "\n";
    return 0;
}