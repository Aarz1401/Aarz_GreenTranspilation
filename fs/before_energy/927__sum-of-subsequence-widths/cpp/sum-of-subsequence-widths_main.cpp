int main() {
    // Prepare 10 diverse test inputs
    std::vector<std::vector<int>> inputs;
    inputs.reserve(10);

    // 1) Empty
    inputs.push_back({});

    // 2) Single element
    inputs.push_back({42});

    // 3) Two elements
    inputs.push_back({1, 2});

    // 4) All equal values
    inputs.emplace_back(100, 7);

    // 5) Increasing sequence 0..999
    {
        std::vector<int> v(1000);
        for (int i = 0; i < 1000; ++i) v[i] = i;
        inputs.push_back(std::move(v));
    }

    // 6) Decreasing sequence 1000..1
    {
        std::vector<int> v(1000);
        for (int i = 0; i < 1000; ++i) v[i] = 1000 - i;
        inputs.push_back(std::move(v));
    }

    // 7) Mixed negatives and positives
    inputs.push_back({-1000, -1, 0, 1, 1000, 500, -500, 123456, -654321});

    // 8) Extreme int values
    inputs.push_back({INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1, 0, -12345, 12345});

    // 9) Pseudo-random 2000 elements (deterministic)
    {
        std::vector<int> v;
        v.reserve(2000);
        uint32_t seed = 123456789u;
        for (int i = 0; i < 2000; ++i) {
            seed = seed * 1664525u + 1013904223u;
            int val = static_cast<int>(seed % 2000000001u) - 1000000000; // [-1e9, 1e9]
            v.push_back(val);
        }
        inputs.push_back(std::move(v));
    }

    // 10) Repeating pattern
    {
        std::vector<int> pattern = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0, 0, -1, -1, 100, -100};
        std::vector<int> v;
        v.reserve(static_cast<size_t>(pattern.size()) * 200);
        for (int r = 0; r < 200; ++r) {
            v.insert(v.end(), pattern.begin(), pattern.end());
        }
        inputs.push_back(std::move(v));
    }

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            std::vector<int> A = inputs[i]; // copy to preserve original unsorted inputs
            int res = sol.sumSubseqWidths(A);
            // Mix result into checksum to prevent optimization
            checksum = (checksum * 1315423911ULL) ^ (static_cast<uint64_t>(res) + static_cast<uint64_t>(A.size()) + static_cast<uint64_t>(iter));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}