#include <vector>
#include <algorithm>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
private:
    vector<int> gcdValuesImpl(const vector<int>& nums, const vector<long long>& queries) {
        if (nums.empty()) return vector<int>(queries.size(), 0);
        int r = *max_element(nums.begin(), nums.end());
        vector<long long> freq(r + 1, 0);
        for (int x : nums) {
            ++freq[x];
        }
        vector<long long> cnt2(r + 1, 0);
        for (int g = r; g >= 1; --g) {
            long long c = 0;
            for (int ng = g; ng <= r; ng += g) {
                c += freq[ng];
            }
            long long s = 0;
            for (int ng = g + g; ng <= r; ng += g) {
                s += cnt2[ng];
            }
            cnt2[g] = c * (c - 1) / 2 - s;
        }
        vector<long long> prefix(r + 2, 0);
        for (int i = 0; i <= r; ++i) {
            prefix[i + 1] = prefix[i] + cnt2[i];
        }
        vector<int> result;
        result.reserve(queries.size());
        for (long long q : queries) {
            auto it = upper_bound(prefix.begin(), prefix.end(), q);
            int idx = static_cast<int>(it - prefix.begin()) - 1;
            result.push_back(idx);
        }
        return result;
    }
public:
    vector<int> gcdValues(vector<int>& nums, vector<int>& queries) {
        vector<long long> qll(queries.size());
        for (size_t i = 0; i < queries.size(); ++i) qll[i] = static_cast<long long>(queries[i]);
        return gcdValuesImpl(nums, qll);
    }
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        return gcdValuesImpl(nums, queries);
    }
};

struct TestCase {
    vector<int> nums;
    vector<long long> queries;
};

int main() {
    vector<TestCase> tests;

    // Test 1
    tests.push_back(TestCase{
        {1, 2},
        {0}
    });

    // Test 2
    tests.push_back(TestCase{
        {2, 4, 6},
        {0, 1, 2}
    });

    // Test 3
    tests.push_back(TestCase{
        {2, 3, 5, 7},
        {0, 3, 5}
    });

    // Test 4
    tests.push_back(TestCase{
        {3, 6, 9, 12},
        {0, 2, 5}
    });

    // Test 5
    tests.push_back(TestCase{
        {1, 2, 3, 4, 5},
        {0, 4, 9}
    });

    // Test 6
    tests.push_back(TestCase{
        {10, 10, 5, 15, 20},
        {0, 5, 9}
    });

    // Test 7
    tests.push_back(TestCase{
        {12, 18, 24, 30, 36},
        {0, 6, 9}
    });

    // Test 8
    tests.push_back(TestCase{
        {8, 16, 32, 3, 6},
        {0, 1, 9}
    });

    // Test 9
    tests.push_back(TestCase{
        {14, 21, 28, 35, 42, 49},
        {0, 7, 14}
    });

    // Test 10
    tests.push_back(TestCase{
        {4, 6, 9, 10, 15, 25},
        {0, 5, 14}
    });

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            vector<int> out = sol.gcdValues(tc.nums, tc.queries);
            DoNotOptimize(out);
            //for (int v : out) checksum += v;
        }
        //sink = checksum;
    }

    return 0;
}