int main() {
    // Prepare 10 diverse test cases
    std::vector<std::vector<int>> pricesList;
    std::vector<int> ks;
    pricesList.reserve(10);
    ks.reserve(10);

    // 1. Empty prices
    pricesList.push_back({});
    ks.push_back(3);

    // 2. Single element
    pricesList.push_back({5});
    ks.push_back(1);

    // 3. Strictly increasing
    pricesList.push_back({1, 2, 3, 4, 5});
    ks.push_back(10);

    // 4. Strictly decreasing
    pricesList.push_back({5, 4, 3, 2, 1});
    ks.push_back(2);

    // 5. Mixed typical case
    pricesList.push_back({3, 2, 6, 5, 0, 3});
    ks.push_back(2);

    // 6. All equal elements
    pricesList.push_back({2, 2, 2, 2, 2, 2});
    ks.push_back(100);

    // 7. Multiple rising peaks
    pricesList.push_back({1, 7, 2, 8, 3, 9, 4, 10, 5, 11});
    ks.push_back(4);

    // 8. Alternating high-low
    pricesList.push_back({10, 1, 10, 1, 10, 1, 10, 1});
    ks.push_back(2);

    // 9. Long repeating up-down pattern (size ~2000)
    {
        std::vector<int> pattern = {1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10};
        std::vector<int> longPattern;
        longPattern.reserve(2000);
        while (longPattern.size() < 2000) {
            longPattern.insert(longPattern.end(), pattern.begin(), pattern.end());
        }
        longPattern.resize(2000);
        pricesList.push_back(std::move(longPattern));
        ks.push_back(500);
    }

    // 10. Pseudo-random-like large sequence (size 3000)
    {
        std::vector<int> largeSeq;
        largeSeq.reserve(3000);
        uint32_t x = 123456789u;
        for (int i = 0; i < 3000; ++i) {
            // Linear Congruential Generator for determinism
            x = 1664525u * x + 1013904223u;
            largeSeq.push_back(static_cast<int>(x % 100000u));
        }
        pricesList.push_back(std::move(largeSeq));
        ks.push_back(1000);
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        checksum += sol.maxProfit(ks[0], pricesList[0]);
        checksum += sol.maxProfit(ks[1], pricesList[1]);
        checksum += sol.maxProfit(ks[2], pricesList[2]);
        checksum += sol.maxProfit(ks[3], pricesList[3]);
        checksum += sol.maxProfit(ks[4], pricesList[4]);
        checksum += sol.maxProfit(ks[5], pricesList[5]);
        checksum += sol.maxProfit(ks[6], pricesList[6]);
        checksum += sol.maxProfit(ks[7], pricesList[7]);
        checksum += sol.maxProfit(ks[8], pricesList[8]);
        checksum += sol.maxProfit(ks[9], pricesList[9]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}