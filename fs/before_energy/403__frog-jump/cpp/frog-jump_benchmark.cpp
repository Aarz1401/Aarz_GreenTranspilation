#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

class Solution {
public:
    bool canCross(std::vector<int>& stones) {
        if (stones.size() >= 2 && stones[1] != 1) {
            return false;
        }

        std::unordered_map<int, std::unordered_set<int>> last_jump_units;
        last_jump_units.reserve(stones.size() * 2);
        for (int s : stones) {
            last_jump_units.emplace(s, std::unordered_set<int>{});
        }

        if (stones.size() >= 2) {
            last_jump_units[1].insert(1);
        } else {
            return true;
        }

        for (size_t i = 0; i + 1 < stones.size(); ++i) {
            int s = stones[i];
            const auto& jumps = last_jump_units[s];
            if (jumps.empty()) continue;
            for (int j : jumps) {
                for (int k = j - 1; k <= j + 1; ++k) {
                    if (k > 0) {
                        int next = s + k;
                        auto it = last_jump_units.find(next);
                        if (it != last_jump_units.end()) {
                            it->second.insert(k);
                        }
                    }
                }
            }
        }
        return !last_jump_units[stones.back()].empty();
    }
};

int main() {
    std::vector<std::vector<int>> tests = {
        {0},
        {0, 1},
        {0, 2},
        {0, 1, 3, 5, 6, 8, 12, 17},
        {0, 1, 2, 3, 4, 8, 9, 11},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {0, 1, 3, 4, 5, 7, 9, 10, 12},
        {0, 1, 3, 6, 10, 13, 14},
        {0, 1, 4, 5, 9, 10, 13, 17},
        {0, 1, 2, 4, 7, 11, 16, 22, 29, 37}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.canCross(tests[i]);
            checksum += res ? (static_cast<long long>(tests[i].size()) + iter + static_cast<long long>(i)) 
                            : static_cast<long long>(i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed << "\n";
    return 0;
}