int main() {
    vector<string> tests = {
        "3+2*2",
        " 3/2 ",
        " 3+5 / 2 ",
        "(1+(4+5+2)-3)+(6+8)",
        "14-3/2",
        "2*(5+5*2)/3+(6/2+8)",
        "1-(2+3*(4-5))+6/2",
        "((10+20)-(30-40))/5",
        "1000000*3/2",
        " (  7 + (8/  4) * (  3 + 5 )  ) - 6 "
    };

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += solver.calculate(s);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (us): " << elapsed_us << "\n";
    return 0;
}