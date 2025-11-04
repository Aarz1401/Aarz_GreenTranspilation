int main() {
    std::vector<std::string> tests = {
        "(add 1 2)",
        "(mult 3 4)",
        "(add 1 (mult 2 3))",
        "(let x 2 (add x 3))",
        "(let x 2 (let y (mult x 5) (add y x)))",
        "(let x 1 (let x 2 (add x x)))",
        "(let x 5 (add (let x 3 x) x))",
        "(let x 1 y 2 z 3 (add x (add y z)))",
        "(add -3 (mult -2 4))",
        "(let x 2 x (add x 3) x (mult x 2) x)"
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& expr : tests) {
            checksum += sol.evaluate(expr);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}