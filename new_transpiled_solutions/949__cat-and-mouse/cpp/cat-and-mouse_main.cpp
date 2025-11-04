int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test graphs
    vector<vector<vector<int>>> tests = {
        // G1: triangle
        { {1,2}, {0,2}, {0,1} },
        // G2: chain of 4
        { {1}, {0,2}, {1,3}, {2} },
        // G3: star centered at 0 (hole)
        { {1,2,3,4}, {0}, {0}, {0}, {0} },
        // G4: complete graph of 5
        { {1,2,3,4}, {0,2,3,4}, {0,1,3,4}, {0,1,2,4}, {0,1,2,3} },
        // G5: LeetCode-like example (often a draw)
        { {2,5}, {3}, {0,4,5}, {1,4,5}, {2,3}, {0,2,3} },
        // G6: ring of 6
        { {1,5}, {0,2}, {1,3}, {2,4}, {3,5}, {4,0} },
        // G7: two components, one isolated node
        { {1}, {0}, {3}, {2}, {} },
        // G8: chain of 3
        { {1}, {0,2}, {1} },
        // G9: small star - cat adjacent only to hole
        { {1,2}, {0}, {0} },
        // G10: dense irregular graph of 7
        { {1,2,3}, {0,4,5}, {0,4,6}, {0,5,6}, {1,2,5,6}, {1,3,4,6}, {2,3,4,5} }
    };

    Solution sol;
    volatile long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.catMouseGame(tests[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}