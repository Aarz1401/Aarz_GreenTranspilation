#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <unordered_map>
#include <unordered_set>

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