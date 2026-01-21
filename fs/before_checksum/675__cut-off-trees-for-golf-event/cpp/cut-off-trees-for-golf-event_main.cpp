int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test inputs
    vector<vector<int>> f1; // empty -> -1
    vector<vector<int>> f2 = { { } }; // n == 0 -> -1
    vector<vector<int>> f3 = { {0} }; // start blocked -> -1
    vector<vector<int>> f4 = { {1,1}, {1,1} }; // no trees -> 0
    vector<vector<int>> f5 = { {1,2} }; // single tree -> reachable
    vector<vector<int>> f6 = {
        {1,2,3},
        {0,0,4},
        {7,6,5}
    }; // reachable classic
    vector<vector<int>> f7 = {
        {1,2,3},
        {0,0,0},
        {4,5,6}
    }; // unreachable later -> -1
    vector<vector<int>> f8 = {
        {1,0,2,0,3},
        {0,4,0,5,0},
        {6,0,7,0,8},
        {0,9,0,10,0},
        {11,0,12,0,13}
    }; // unreachable early -> -1
    vector<vector<int>> f9 = {
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,1,2,3,0,1},
        {1,1,4,5,0,1},
        {1,1,6,7,0,1},
        {1,1,1,1,1,1}
    }; // reachable with corridor
    vector<vector<int>> f10 = {
        {1,2,3,4,5,6,7},
        {0,0,0,0,0,0,8},
        {15,14,13,12,11,10,9},
        {16,0,0,0,0,0,0},
        {17,18,19,20,21,22,23}
    }; // zigzag path reachable

    long long checksum = 0;

    const int iterations = 1;
    auto begin = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        checksum += sol.cutOffTree(f1);
        checksum += sol.cutOffTree(f2);
        checksum += sol.cutOffTree(f3);
        checksum += sol.cutOffTree(f4);
        checksum += sol.cutOffTree(f5);
        checksum += sol.cutOffTree(f6);
        checksum += sol.cutOffTree(f7);
        checksum += sol.cutOffTree(f8);
        checksum += sol.cutOffTree(f9);
        checksum += sol.cutOffTree(f10);
        // minor dependency on iter to avoid over-aggressive optimization
        checksum += iter & 1;
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time: " << elapsed_us << " us\n";

    return 0;
}