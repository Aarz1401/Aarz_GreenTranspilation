int main() {
    // 10 diverse test inputs
    std::vector<std::vector<std::string>> t1 = {
        {"MUC","LHR"}, {"JFK","MUC"}, {"SFO","SJC"}, {"LHR","SFO"}
    };
    std::vector<std::vector<std::string>> t2 = {
        {"JFK","KUL"}, {"JFK","NRT"}, {"NRT","JFK"}
    };
    std::vector<std::vector<std::string>> t3 = {
        {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"}
    };
    std::vector<std::vector<std::string>> t4 = {
        {"JFK","A"}, {"JFK","A"}, {"A","JFK"}
    };
    std::vector<std::vector<std::string>> t5 = {
        {"JFK","A"}, {"A","B"}, {"B","C"}, {"C","D"}, {"D","E"}
    };
    std::vector<std::vector<std::string>> t6 = {
        {"JFK","A"}, {"A","A"}, {"A","JFK"}
    };
    std::vector<std::vector<std::string>> t7 = {
        {"JFK","BBB"}, {"JFK","AAA"}, {"AAA","JFK"}, {"BBB","AAA"}
    };
    std::vector<std::vector<std::string>> t8 = {
        {"JFK","A"}, {"JFK","B"}, {"A","C"}, {"C","A"}, {"B","C"}, {"C","JFK"}
    };
    std::vector<std::vector<std::string>> t9 = {
        {"JFK","SFO"}, {"JFK","SFO"}, {"SFO","JFK"}, {"SFO","LAX"}, {"LAX","JFK"}
    };
    std::vector<std::vector<std::string>> t10 = {
        {"JFK","A"}, {"A","JFK"}, {"JFK","B"}, {"B","C"}, {"C","JFK"},
        {"JFK","D"}, {"D","E"}, {"E","F"}, {"F","JFK"}
    };

    std::vector<std::vector<std::vector<std::string>>> tests = {
        t1, t2, t3, t4, t5, t6, t7, t8, t9, t10
    };

    Solution sol;
    volatile unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tickets : tests) {
            auto res = sol.findItinerary(tickets);
            for (const auto& s : res) {
                for (unsigned char c : s) {
                    checksum = (checksum * 1315423911ull) ^ c;
                }
                checksum ^= static_cast<unsigned long long>(s.size());
            }
            checksum ^= static_cast<unsigned long long>(res.size());
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << us << "\n";

    return 0;
}