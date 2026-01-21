int main() {
    std::vector<std::vector<std::vector<std::string>>> tests = {
        { {"MUC","LHR"}, {"JFK","MUC"}, {"SFO","SJC"}, {"LHR","SFO"} },
        { {"JFK","KUL"}, {"JFK","NRT"}, {"NRT","JFK"} },
        { {"JFK","AAA"}, {"JFK","AAA"}, {"AAA","JFK"} },
        { {"JFK","ATL"}, {"ATL","SFO"}, {"SFO","JFK"} },
        { {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"} },
        { {"JFK","AAA"}, {"JFK","BBB"}, {"AAA","CCC"}, {"CCC","JFK"}, {"BBB","DDD"}, {"DDD","EEE"} },
        { {"JFK","AAB"}, {"JFK","AAA"}, {"AAA","JFK"}, {"AAB","AAA"} },
        { {"JFK","LAX"}, {"JFK","LAX"}, {"LAX","JFK"}, {"LAX","SFO"}, {"SFO","LAX"} },
        { {"JFK","AAA"}, {"AAA","BBB"}, {"BBB","AAA"}, {"AAA","JFK"}, {"JFK","CCC"}, {"CCC","DDD"}, {"DDD","JFK"}, {"CCC","EEE"}, {"EEE","CCC"} },
        { {"JFK","MUC"}, {"JFK","LHR"}, {"LHR","MUC"}, {"MUC","SFO"}, {"SFO","ATL"}, {"ATL","JFK"} }
    };

    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tickets : tests) {
            std::vector<std::string> res = sol.findItinerary(tickets);
            checksum += static_cast<int>(res.size());
            if (!res.empty()) {
                checksum += static_cast<int>(static_cast<unsigned char>(res.front()[0]));
                checksum += static_cast<int>(static_cast<unsigned char>(res.back()[0]));
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}