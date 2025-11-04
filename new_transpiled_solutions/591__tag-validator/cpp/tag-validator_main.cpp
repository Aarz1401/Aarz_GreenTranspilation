int main() {
    std::vector<std::string> tests = {
        "<A>TEXT</A>",
        "<A><B><![CDATA[<C>not parsed</C>]]></B></A>",
        "<ABC><D>E</D><F><![CDATA[123]]>G</F></ABC>",
        "TEXT<A></A>",
        "<Aaa></Aaa>",
        "<A><B></A></B>",
        "<ABCDEFGHIJ></ABCDEFGHIJ>",
        "<A><B></B></A",
        "<A><![CDATA[unfinished</A>",
        "<A>t1<B>t2</B>t3</A>"
    };

    Solution sol;

    std::uint64_t checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (std::size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.isValid(tests[i]);
            checksum += res ? (static_cast<std::uint64_t>(tests[i].size()) + i + static_cast<std::uint64_t>(iter))
                            : (static_cast<std::uint64_t>((tests[i].size() ^ iter) + i + 1));
        }
    }

    auto end = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed.count() << "\n";
    return 0;
}