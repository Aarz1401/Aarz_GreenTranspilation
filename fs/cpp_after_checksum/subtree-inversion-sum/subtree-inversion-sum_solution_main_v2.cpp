int main() {
    vector<Test> tests = {
        // 1) Single node
        { {}, {7}, 1 },
        // 2) Chain of 5
        { {{0,1},{1,2},{2,3},{3,4}}, {3,-1,4,-2,1}, 1 },
        // 3) Balanced binary tree of 7
        { {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}}, {-5,-4,-3,2,1,0,7}, 2 },
        // 4) Star with 6 nodes
        { {{0,1},{0,2},{0,3},{0,4},{0,5}}, {10,-10,5,-5,2,-2}, 3 },
        // 5) Mixed branching with 8 nodes
        { {{0,1},{1,2},{1,3},{3,4},{3,5},{5,6},{6,7}}, {1,2,3,4,5,6,7,8}, 2 },
        // 6) 10 nodes with zeros and negatives
        { {{0,1},{0,2},{2,3},{2,4},{4,5},{4,6},{1,7},{7,8},{8,9}}, {0,-1,-2,-3,0,3,2,1,-4,5}, 4 },
        // 7) 15-node near-complete binary
        { {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{3,8},{4,9},{4,10},{5,11},{5,12},{6,13},{6,14}},
          {-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7}, 5 },
        // 8) 9 nodes with large positives
        { {{0,1},{1,2},{2,3},{2,4},{4,5},{5,6},{3,7},{7,8}}, {100,200,300,400,500,600,700,800,900}, 3 },
        // 9) Small branched 4-node
        { {{0,1},{1,2},{1,3}}, {-1000,0,1000,-500}, 1 },
        // 10) 12-node mixed
        { {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{4,7},{4,8},{6,9},{9,10},{10,11}}, {5,-3,8,-2,7,0,-1,4,-4,6,-6,2}, 6 }
    };

    Solution solver;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            long long r = solver.subtreeInversionSum(const_cast<vector<vector<int>>&>(t.edges),
                                                     const_cast<vector<int>&>(t.nums),
                                                     t.k);
            checksum += static_cast<int>(r);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}