int main() {
    std::vector<std::vector<std::vector<int>>> tests = {
        // 1) 1x1 healthy
        {{0}},
        // 2) 1x1 infected
        {{1}},
        // 3) 2x2 single infection
        {
            {1,0},
            {0,0}
        },
        // 4) 3x3 all infected
        {
            {1,1,1},
            {1,1,1},
            {1,1,1}
        },
        // 5) 3x4 scattered infections
        {
            {1,0,0,1},
            {0,0,0,0},
            {1,0,1,0}
        },
        // 6) 5x5 ring with center infection
        {
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,1,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}
        },
        // 7) 5x5 mixed pattern
        {
            {0,1,0,0,1},
            {1,1,0,1,0},
            {0,0,1,0,0},
            {1,0,0,1,1},
            {0,1,0,0,0}
        },
        // 8) 4x7 varied layout
        {
            {0,0,1,0,0,1,0},
            {1,0,1,0,0,0,0},
            {0,0,0,1,1,0,1},
            {1,1,0,0,0,0,0}
        },
        // 9) 8x8 moderate density
        {
            {0,1,0,0,1,0,0,1},
            {1,0,1,0,0,1,0,0},
            {0,0,0,1,0,0,1,0},
            {1,0,0,0,1,0,0,1},
            {0,1,0,0,0,1,0,0},
            {0,0,1,0,0,0,1,0},
            {1,0,0,1,0,0,0,1},
            {0,0,1,0,1,0,0,0}
        },
        // 10) 6x6 checkerboard starting with infected
        {
            {1,0,1,0,1,0},
            {0,1,0,1,0,1},
            {1,0,1,0,1,0},
            {0,1,0,1,0,1},
            {1,0,1,0,1,0},
            {0,1,0,1,0,1}
        }
    };

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            std::vector<std::vector<int>> grid = t;
            Solution s;
            int res = s.containVirus(grid);
            checksum += res;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}