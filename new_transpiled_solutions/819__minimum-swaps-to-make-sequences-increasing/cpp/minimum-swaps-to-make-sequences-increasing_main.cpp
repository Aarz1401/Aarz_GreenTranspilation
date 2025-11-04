int main() {
    // Prepare 10 diverse test inputs
    std::vector<TestCase> tests;
    tests.reserve(10);

    // 1) Empty arrays
    tests.push_back(TestCase{ {}, {} });

    // 2) Single element equal arrays
    tests.push_back(TestCase{ {1}, {1} });

    // 3) Classic example that needs 1 swap
    tests.push_back(TestCase{ {1, 3, 5, 4}, {1, 2, 3, 7} });

    // 4) Already strictly increasing sequences
    tests.push_back(TestCase{ {1, 2, 3, 4}, {2, 3, 4, 5} });

    // 5) Mixed requiring swaps
    tests.push_back(TestCase{ {0, 3, 5, 8, 9}, {2, 1, 4, 6, 9} });

    // 6) Negative numbers
    tests.push_back(TestCase{ {-5, -3, -1, 2, 4}, {-6, -4, 0, 3, 5} });

    // 7) Interleaved increasing
    tests.push_back(TestCase{ {1, 4, 6, 8, 10}, {2, 3, 5, 7, 9} });

    // 8) Zig-zag pattern
    tests.push_back(TestCase{ {1, 5, 3, 9, 10, 13, 15}, {2, 3, 7, 4, 12, 14, 16} });

    // 9) Large easy case (1000 elements, solvable without swaps)
    {
        std::vector<int> A(1000), B(1000);
        for (int i = 0; i < 1000; ++i) {
            A[i] = i * 3 + ((i % 10 == 0) ? 2 : 1);
            B[i] = i * 3 + ((i % 10 == 0) ? 1 : 2);
        }
        tests.push_back(TestCase{ std::move(A), std::move(B) });
    }

    // 10) Medium-sized with periodic perturbations
    {
        std::vector<int> A(120), B(120);
        for (int i = 0; i < 120; ++i) {
            A[i] = i * 2 + ((i % 3 == 0) ? 1 : 0);
            B[i] = i * 2 + 1 - ((i % 4 == 0) ? 1 : 0);
        }
        tests.push_back(TestCase{ std::move(A), std::move(B) });
    }

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases
        for (auto& tc : tests) {
            // Solution::minSwap expects non-const references; inputs are not modified by the algorithm.
            checksum += solver.minSwap(tc.A, tc.B);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}