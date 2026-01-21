#include <vector>
#include <unordered_map>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int subsequencesWithMiddleMode(vector<int>& nums) {
        const long long MOD = 1000000007LL;
        int n = nums.size();
        unordered_map<int, long long> left, right;
        left.reserve(n * 2);
        right.reserve(n * 2);
        for (int x : nums) {
            right[x] += 1;
        }

        auto C2 = [](long long x) -> __int128 {
            return (__int128)x * (x - 1) / 2;
        };

        long long left_x_sq = 0;             // sum(left[x]^2 for x != v)
        long long right_x_sq = 0;            // sum(right[x]^2 for x != v)
        long long left_x_right_x = 0;        // sum(left[x]*right[x] for x != v)
        long long left_x_sq_right_x = 0;     // sum(left[x]^2*right[x] for x != v)
        long long left_x_right_x_sq = 0;     // sum(left[x]*right[x]^2 for x != v)

        for (const auto& kv : right) {
            long long c = kv.second;
            right_x_sq += c * c;
        }

        __int128 result = 0;

        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            long long lv = left[v];
            long long rv_before = right[v];

            left_x_sq -= lv * lv;
            right_x_sq -= rv_before * rv_before;
            left_x_right_x -= lv * rv_before;
            left_x_sq_right_x -= lv * lv * rv_before;
            left_x_right_x_sq -= lv * rv_before * rv_before;

            right[v] = rv_before - 1;
            long long rv = right[v];

            long long l = i;
            long long r = n - (i + 1);

            // all possibles
            result += C2(l) * C2(r);

            // only mid is a
            long long l_minus_lv = l - lv;
            long long r_minus_rv = r - rv;
            result -= C2(l_minus_lv) * C2(r_minus_rv);

            // bb/a/ac
            {
                __int128 t1 = (__int128)(left_x_sq - l_minus_lv) * (r_minus_rv) - (__int128)(left_x_sq_right_x - left_x_right_x);
                result -= t1 * rv / 2;
            }
            // ac/a/bb
            {
                __int128 t2 = (__int128)(right_x_sq - r_minus_rv) * (l_minus_lv) - (__int128)(left_x_right_x_sq - left_x_right_x);
                result -= t2 * lv / 2;
            }
            // ab/a/bc
            result -= (__int128)lv * left_x_right_x * r_minus_rv - (__int128)lv * left_x_right_x_sq;
            // bc/a/ab
            result -= (__int128)rv * left_x_right_x * l_minus_lv - (__int128)rv * left_x_sq_right_x;
            // bb/a/ab
            result -= (__int128)rv * (left_x_sq_right_x - left_x_right_x) / 2;
            // ab/a/bb
            result -= (__int128)lv * (left_x_right_x_sq - left_x_right_x) / 2;

            left[v] = lv + 1;
            long long lv_new = lv + 1;
            long long rv_now = rv;

            left_x_sq += lv_new * lv_new;
            right_x_sq += rv_now * rv_now;
            left_x_right_x += lv_new * rv_now;
            left_x_sq_right_x += lv_new * lv_new * rv_now;
            left_x_right_x_sq += lv_new * rv_now * rv_now;
        }

        long long ans = (long long)((result % MOD + MOD) % MOD);
        return (int)ans;
    }
};

volatile int sink = 0;

int main() {
    vector<vector<int>> tests;
    tests.reserve(10);
    tests.push_back({1, 2, 3});
    tests.push_back({5});
    tests.push_back({2, 2, 2});
    tests.push_back({1, 2, 1, 2, 3, 3});
    {
        vector<int> t5;
        t5.reserve(50);
        for (int i = 0; i < 50; ++i) t5.push_back(i % 2);
        tests.push_back(t5);
    }
    tests.push_back({0, 0, 0, 1, 1, 2, 2, 2});
    tests.push_back({5, 3, 5, 2, 5, 2, 3, 4, 5, 6, 7, 8, 5, 9});
    {
        vector<int> t8;
        t8.reserve(20);
        for (int i = 1; i <= 20; ++i) t8.push_back(i);
        tests.push_back(t8);
    }
    {
        vector<int> t9;
        t9.reserve(20);
        for (int i = 1; i <= 10; ++i) { t9.push_back(i); t9.push_back(i); }
        tests.push_back(t9);
    }
    {
        vector<int> t10;
        t10.reserve(45);
        for (int i = 0; i < 30; ++i) t10.push_back(0);
        for (int i = 0; i < 10; ++i) t10.push_back(1);
        for (int i = 0; i < 5; ++i) t10.push_back(2);
        tests.push_back(t10);
    }

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            int r = sol.subsequencesWithMiddleMode(tests[i]);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}