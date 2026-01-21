int main() {
    std::vector<std::string> tests = {
        "(add 1 2)",
        "(mult 3 (add 2 3))",
        "(let x 2 (mult x 5))",
        "(let x 3 x 2 x)",
        "(let x 1 y 2 (add x y))",
        "(let x 2 (let x 3 (let x 4 x)))",
        "(let x 2 (add (let x 3 x) x))",
        "(let a -3 b 2 (mult a (add b 5)))",
        "(add (add 1 2) (mult 3 4))",
        "(let x 2 y (add x 3) z (mult y x) (add z (mult x y)))"
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& expr : tests) {
            checksum += sol.evaluate(expr);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}