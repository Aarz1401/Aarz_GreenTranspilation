#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Time:  precompute: O(9 * 2^9 + 16 * p + p log p), p = len(PALINDROMES)
//        runtime:    O(log p)
// Space: O(p)

// precompute, bitmasks, sort, binary search
static const int MAX_LEN = 16;

static bool build_half_from_mask(int mask, vector<char>& left, char& mid) {
    left.clear();
    mid = 0;
    for (int i = 0; i < 9; ++i) {
        if ((mask & (1 << i)) == 0) continue;
        int d = i + 1;
        if (d % 2 == 1) {
            if (mid != 0) {
                return false;  // more than one odd digit count not allowed
            }
            mid = char('0' + d);
        }
        int cnt = d / 2;
        for (int k = 0; k < cnt; ++k) {
            left.emplace_back(char('0' + d));
        }
    }
    return true;
}

static vector<long long> precompute() {
    vector<long long> result;
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<char> left;
        char mid = 0;
        if (!build_half_from_mask(mask, left, mid)) continue;

        // left is initially in sorted (non-decreasing) order by construction
        do {
            string s(left.begin(), left.end());
            string rs = s;
            reverse(rs.begin(), rs.end());
            string p = s;
            if (mid != 0) p.push_back(mid);
            p += rs;
            if ((int)p.size() > MAX_LEN) break;
            long long val = stoll(p);
            result.emplace_back(val);
        } while (next_permutation(left.begin(), left.end()));
    }
    sort(result.begin(), result.end());
    return result;
}

static const vector<long long> PALINDROMES = precompute();

class Solution {
public:
    long long specialPalindrome(long long n) {
        return *upper_bound(PALINDROMES.begin(), PALINDROMES.end(), n);
    }
};

int main() {
    vector<long long> tests = {
        0LL,
        1LL,
        21LL,
        333LL,
        4444LL,
        123456LL,
        2222222LL,
        9999999999LL,
        7000000000000000LL,
        8888666226668887LL
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (long long n : tests) {
            long long res = sol.specialPalindrome(n);
            checksum ^= static_cast<int>(res);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}