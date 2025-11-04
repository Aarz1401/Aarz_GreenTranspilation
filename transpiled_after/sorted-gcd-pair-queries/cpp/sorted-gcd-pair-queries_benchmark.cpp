#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

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

int main() {
    // Define 10 diverse test inputs
    // 5 with int queries, 5 with long long queries

    // Using separate vectors instead of pair to avoid extra headers
    vector<vector<int>> testsIntNums;
    vector<vector<int>> testsIntQueries;

    // Case 1: Empty nums
    testsIntNums.push_back({});
    testsIntQueries.push_back({0, 1, 2, 3, 4});

    // Case 3: Repeated number small array
    testsIntNums.push_back({5, 5, 5});
    testsIntQueries.push_back({0, 1, 2});

    // Case 5: All primes
    testsIntNums.push_back({2, 3, 5, 7, 11, 13});
    testsIntQueries.push_back({0, 1, 5, 10, 14});

    // Case 7: Sequence 1..30
    {
        vector<int> seq;
        for (int i = 1; i <= 30; ++i) seq.push_back(i);
        testsIntNums.push_back(seq);
        testsIntQueries.push_back({0, 10, 50, 100, 200, 300, 400});
    }

    // Case 9: Mixed small numbers under 50
    testsIntNums.push_back({1, 12, 6, 18, 24, 36, 30, 42, 48, 20, 25, 15, 35, 14, 28, 21, 7, 27, 9, 3});
    testsIntQueries.push_back({0, 5, 10, 20, 30, 40, 50});

    vector<vector<int>> testsLLNums;
    vector<vector<long long>> testsLLQueries;

    // Case 2: Single element
    testsLLNums.push_back({10});
    testsLLQueries.push_back({0LL, 1LL, 2LL});

    // Case 4: Mixed duplicates small range
    testsLLNums.push_back({2, 4, 6, 8, 10, 12});
    testsLLQueries.push_back({0LL, 3LL, 5LL, 8LL, 10LL});

    // Case 6: Many identical values
    {
        vector<int> many7(20, 7);
        testsLLNums.push_back(many7);
        testsLLQueries.push_back({0LL, 50LL, 100LL, 150LL, 189LL});
    }

    // Case 8: Moderate high values but bounded r
    testsLLNums.push_back({12, 24, 36, 48});
    testsLLQueries.push_back({0LL, 1LL, 2LL, 3LL, 5LL});

    // Case 10: Many ones plus others
    {
        vector<int> nums10(15, 1);
        vector<int> tail = {2, 3, 4, 5, 6, 7, 8, 9, 10};
        nums10.insert(nums10.end(), tail.begin(), tail.end());
        testsLLNums.push_back(nums10);
        testsLLQueries.push_back({0LL, 20LL, 50LL, 100LL, 150LL, 200LL});
    }

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run int-query test cases
        for (size_t t = 0; t < testsIntNums.size(); ++t) {
            auto nums = testsIntNums[t];
            auto queries = testsIntQueries[t];
            auto res = sol.gcdValues(nums, queries);
            for (int v : res) {
                checksum += v + (iter & 1);
            }
        }
        // Run long long-query test cases
        for (size_t t = 0; t < testsLLNums.size(); ++t) {
            auto nums = testsLLNums[t];
            auto queriesLL = testsLLQueries[t];
            auto res = sol.gcdValues(nums, queriesLL);
            for (int v : res) {
                checksum += v + ((iter >> 1) & 1);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Print checksum and time to prevent optimization and report benchmark result
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ms): " << elapsed << "\n";
    return 0;
}